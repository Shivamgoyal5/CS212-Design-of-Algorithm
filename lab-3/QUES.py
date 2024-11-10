import numpy as np

def median_of_medians(array):
    # hardcoded for 5 elements
    if len(array) <= 5:
        return sorted(array, key=lambda x: x[0])[len(array)//2]

    medians = [sorted(array[i: i+5], key=lambda x: x[0])[2] for i in range(0, len(array)-len(array)%5, 5)]
    medians += [sorted(array[len(array)-len(array)%5-1:], key=lambda x: x[0])[len(array)%5//2]]

    return median_of_medians(medians)


def min_max(array):
    min = float('inf')
    max = float('-inf')
    for i in array:
        if i < min:
            min = i
        if i > max:
            max = i
    return min, max


def quickselect(arr, k, left=0, right=None, mom=False):
    if right is None:
        right = len(arr) - 1

    # print(f'arr: {arr}, k: {k}, left: {left}, right: {right}')

    if left == right:  # If the list contains only one element
        return arr[left]

    # Choose a random pivot_index between left and right
    pivot_index = partition(arr, left, right+1, mom=mom)
    # print(pivot_index)
    # print(f'pivot_index: {pivot_index}, pivot: {arr[pivot_index]}')

    # The pivot is in its final sorted position
    if k == pivot_index:
        return arr[k]
    elif k < pivot_index:
        return quickselect(arr, k, left, pivot_index - 1, mom=mom)
    else:
        return quickselect(arr, k, pivot_index + 1, right, mom=mom)


def partition(array, begin, end, random=False, mom=False):
    
    # Using Median of Three Heuristic:
    # pivot, pivot_idx = sorted([(array[i], i) for i in [begin, begin + int((end-begin)//2), end-1]], key=lambda x: x[0])[1]
    # array[end-1], array[pivot_idx] = pivot, array[end-1]

    # Using end element as pivot
    if not random:
        if not mom:
            pivot = array[end-1]
        else:
            _temp = list(array)[begin:end]
            _temp = list(zip(_temp, range(len(_temp))))

            pivot, pivot_idx = median_of_medians(_temp)
            array[end-1], array[pivot_idx+begin] = pivot, array[end-1]
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
    # define arrays and call functions as required
    # array = np.arange(1, 100)[:51]
    # np.random.shuffle(array)
    # print(array)

    # temp = list(zip(array, range(len(array))))

    # print("Using Median of Medians: ", median_of_medians(temp)[0])

    # print("True Median: ", quickselect(array, len(array)//2, mom=True))

    array = [10, 10, 10, 0, 0.1]
    k=3
    print(f'{k}th smallest: ', quickselect(array, k=k))
    print(min_max(array=array))