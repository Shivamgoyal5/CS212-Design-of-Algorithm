import time
import numpy as np
from copy import deepcopy
import sys
import matplotlib.pyplot as plt
import json

sys.setrecursionlimit(100000)

def get_test_set(length: int):
    np.random.RandomState(1)
    # [random, sorted, reverse-sorted, many_duplicates]
    _random: list[int] = list(np.random.randint(low=0, high=1e7, size=(length, )))  # randomly selecting `length` number of integers between 0 and 10**7
    _sorted: list[int] = sorted(_random)  # sort the values
    _reverse: list[int] = _sorted[::-1]  # reverse the sorted array
    # selecting a specific (length/3) number of elements and tiling the list 5 times then shuffling and extracting the first `length` number of elements
    _duplicates: list[int] = _random[:int(length//3)]*5
    np.random.shuffle(_duplicates)
    _duplicates = _duplicates[:length]
    return _random, _sorted, _reverse, _duplicates

def write_to_file(length: int):
    _test_sets = get_test_set(length)
    with open(f'inputfile_{length}.json', 'w') as file:
        json.dump(dict(zip(['random', 'sorted', 'reverse', 'duplicates'], [','.join(map(str, _set)) for _set in _test_sets])), file)

def get_from_file(length: int):
    stuff = dict()
    with open(f'inputfile_{length}.json', 'r') as file:
        stuff = json.load(file)
    return {k: list(map(int, v.split(','))) for (k,v) in stuff.items()}

def complete_analysis(func, test_len: int = 1000):
    _test_case_set: dict[str: list[int]] = get_from_file(test_len) # dict to store arrays
    _time_taken: dict[str: float] = dict(zip(_test_case_set.keys(), [0.]*4)) # dict to store benchmark times

    for _type, _case in _test_case_set.items():
        _copied_case = deepcopy(_case)
        _t1 = _t2 = 0
        _t1: float = time.perf_counter()  # begin time count
        func(_copied_case)
        _t2: float = time.perf_counter()  # end time count
        _time_taken[_type] = round(_t2-_t1, 6)
        
    print(f'''
Sorting Technique: {func.__name__}
Number of Elements: {test_len}
Cases:
    1. Random Order: \t\t{_time_taken['random']} s
    2. Sorted Order: \t\t{_time_taken['sorted']} s
    3. Reverse Sorted Order: \t{_time_taken['reverse']} s
    4. With many duplicates: \t{_time_taken['duplicates']} s
        ''')
    return _time_taken            

def insertion_sort(array: list[int]):
    n: int = len(array)  # number of elements in the array
    for i  in range(1, n):   # since 1st element is already sorted
        key: int = array[i]
        j: int = i-1

        while(array[j] > key and j >= 0):
            array[j+1] = array[j]
            j = j-1

        array[j+1] = key
    
def merge_sort(array: list[int], begin:int=0, end:int|None=None):
    if end is None:
        end=len(array)
        
    if end - begin <= 1:
        return
    else:
        mid: int = int(begin + (end-begin)//2)
        merge_sort(array, begin, mid)
        merge_sort(array, mid, end)
        merge(array, begin, mid, end)

def merge(array, begin, mid, end):
    _temp: list[int] = [-1]*(end-begin)
    i: int = begin
    j: int = mid
    k: int = 0

    while i < mid and j < end:
        if array[i] > array[j]:
            _temp[k] = array[j]
            j += 1
            k += 1
        else:
            _temp[k] = array[i]
            i += 1
            k += 1
    
    while i < mid:
        _temp[k] = array[i]
        k += 1
        i += 1
    
    while j < end:
        _temp[k] = array[j]
        j += 1
        k += 1
    
    for i in range(begin, end):
        array[i] = _temp[i-begin]

def quick_sort(array, begin=0, end=None):
    if end is None:
        end = len(array)

    if end-begin <= 1:
        return
    
    pi = partition(array, begin, end)
    quick_sort(array, begin, pi)
    quick_sort(array, pi+1, end)

def random_quick_sort(array, begin=0, end=None):
    if end is None:
        end = len(array)

    if end-begin <= 1:
        return
    
    pi = partition(array, begin, end, random=True)
    random_quick_sort(array, begin, pi)
    random_quick_sort(array, pi+1, end)

def partition(array, begin, end, random=False):
    
    # Using Median of Three Heuristic:
    # pivot, pivot_idx = sorted([(array[i], i) for i in [begin, begin + int((end-begin)//2), end-1]], key=lambda x: x[0])[1]
    # array[end-1], array[pivot_idx] = pivot, array[end-1]

    # Using end element as pivot
    if not random:
        pivot = array[end-1]
    else:
        # pivot, pivot_idx = sorted([(array[i], i) for i in [begin, begin + int((end-begin)//2), end-1]], key=lambda x: x[0])[1]
        pivot_idx = np.random.randint(begin, end)
        pivot = array[pivot_idx]
        array[end-1], array[pivot_idx] = pivot, array[end-1]

    i = begin
    for j in range(begin, end-1):
        if array[j] < pivot:
            # print(f'swapping {array[i]} with {array[j]}')
            array[i], array[j] = array[j], array[i]
            i += 1

    array[i], array[end-1] = array[end-1], array[i]
    return i

if __name__ == '__main__':
    dataset = dict()
    for func in [insertion_sort, merge_sort, quick_sort, random_quick_sort]:
        dataset[func.__name__] = dict()
        for i in [100, 1000, 10000]:
            dataset[func.__name__][i] = complete_analysis(func, test_len=i)

    # some cool plots
    fig, ax = plt.subplots(4, 3, figsize=(15, 15))
    for i, (func, data) in enumerate(dataset.items()):
        for j, (n, times) in enumerate(data.items()):
            ax[i, j].bar(times.keys(), times.values(), color=['red', 'green', 'blue', 'orange'])
            ax[i, j].set_title(f'{func} with n={n}')
            ax[i, j].set_ylabel('Time Taken in seconds')
    plt.tight_layout()
    plt.show()
    
    # compare performance of all algo for elements
    fig, ax = plt.subplots(1, 3, figsize=(10, 5))
    for func, data in dataset.items():
        for i in [2,3,4]:
            ax[i-2].plot(data[10**i].keys(), data[10**i].values(), label=func)
            ax[i-2].set_title(f'Performance of Sorting Algorithms for {10**i} elements')
            ax[i-2].set_xlabel('Cases')
            ax[i-2].set_ylabel('Time Taken in seconds')
            ax[i-2].legend()
    plt.show()