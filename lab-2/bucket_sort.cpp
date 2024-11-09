#include <bits/stdc++.h>
#include <vector>
#include <chrono> 
#include <fstream>
#include <cmath> 

using namespace std;

// Insertion Sort
vector<int> insertionSort(vector<int> arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr;
}

// Bucket Sort
vector<int> bucketSort(vector<int> arr) {
    int n = arr.size();
    vector<vector<int>> b(n); 

    for (int i = 0; i < n; i++) {
        int bktindex = floor(n * arr[i]);
        b[bktindex].push_back(arr[i]);
    }

    for (int i = 0; i < n; i++) {
        b[i] = insertionSort(b[i]);
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            arr[index++] = b[i][j];
        }
    }

    return arr;
}

// Performance testing function
void testSortingPerformance(vector<int> arr, const string& caseName, int arraySize) {
    auto start = chrono::high_resolution_clock::now();
    arr = bucketSort(arr); // Measure time 
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<long double> duration = end - start;

    // Save results to a CSV file
    ofstream file("sorting_performanceq1.csv", ios::app); 
    file << caseName << "," << arraySize << "," << duration.count() << "\n";
    file.close();
}

int main() {
    srand(time(0));// Seed for random number generation

    ofstream file("sorting_performanceq1.csv");
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
            double value = (double)rand() / RAND_MAX; // Generate values between 0 and 1
            randomData.push_back(value);
            sortedData.push_back((double)i / size);  
            reverseData.push_back((double)(size - i - 1) / size); 
            duplicateData.push_back(0.5);  
        }

        // Test each case
        testSortingPerformance(randomData, "Random", size);
        testSortingPerformance(sortedData, "Sorted", size);
        testSortingPerformance(reverseData, "Reverse-Sorted", size);
        testSortingPerformance(duplicateData, "Duplicate", size);
    }

    cout << "Performance testing complete. Results written to sorting_performanceq1.csv" << endl;

    return 0;
}
