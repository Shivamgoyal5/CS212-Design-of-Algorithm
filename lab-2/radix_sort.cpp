#include <bits/stdc++.h>
#include <vector>
#include <chrono> 
#include <fstream>
#include <cmath> 

using namespace std;

// Max value
int getMax(vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

// Count sort
void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); 
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Radix Sort
void radixSort(vector<int>& arr) {
    int maxVal = getMax(arr);

    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

// Performance testing function
void testSortingPerformance(vector<int> arr, const string& caseName, int arraySize) {
    auto start = chrono::high_resolution_clock::now();
    radixSort(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<long double> duration = end - start;

    // Save results to a CSV file
    ofstream file("sorting_performanceq2.csv", ios::app); 
    file << caseName << "," << arraySize << "," << duration.count() << "\n";
    file.close();
}

int main() {
    srand(time(0));// Seed for random number generation

    ofstream file("sorting_performanceq2.csv");
    file << "Case,Array Size,Time (seconds)\n"; // CSV header
    file.close();

    vector<int> randomData, sortedData, reverseData, duplicateData;

    // Test for different array sizes
    for (int size : {100, 1000, 10000}) {
        randomData.clear();
        sortedData.clear();
        reverseData.clear();
        duplicateData.clear();

        for (int i = 0; i < size; ++i) {
            int value = rand() % 10000; // Generate values between 0 and 9999
            randomData.push_back(value);
            sortedData.push_back(i);
            reverseData.push_back(size - i - 1);
            duplicateData.push_back(42);
        }

        // Test each case with Radix Sort
        testSortingPerformance(randomData, "Random", size);
        testSortingPerformance(sortedData, "Sorted", size);
        testSortingPerformance(reverseData, "Reverse-Sorted", size);
        testSortingPerformance(duplicateData, "Duplicate", size);
    }

    cout << "Performance testing complete. Results written to sorting_performanceq2.csv" << endl;

    return 0;
}
