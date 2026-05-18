#include "sorting.h"

using namespace std;

void Sorting::displayArray(int arr[], int n, int active1, int active2) {
    string row = "[ ";
    for (int i = 0; i < n; i++) {
        if (i == active1 || i == active2) row += highlight(arr[i]);
        else row += to_string(arr[i]);
        if (i < n - 1) row += " | ";
    }
    row += " ]";
    printStep(0, row); // Custom step print
}

void Sorting::bubbleSort(int arr[], int n) {
    printHeader("Sorting", "Bubble Sort");
    printStep(1, "BEFORE: Unsorted array");
    displayArray(arr, n);
    
    int steps = 0;
    int comps = 0;
    
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            steps++;
            string msg = "Pass " + to_string(i+1) + " | Comparing " + highlight(arr[j]) + " vs " + highlight(arr[j+1]);
            printStep(steps + 1, msg);
            sleep_ms(200);
            
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
                printStep(steps + 1, "Swapped!");
                displayArray(arr, n, j, j+1);
            }
        }
        if (!swapped) break;
    }
    
    printResult("AFTER: Array sorted");
    displayArray(arr, n);
    Performance::log("Sorting", "BubbleSort", steps, comps);
}

void Sorting::selectionSort(int arr[], int n) {
    printHeader("Sorting", "Selection Sort");
    printStep(1, "BEFORE: Unsorted array");
    displayArray(arr, n);
    
    int steps = 0;
    int comps = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        steps++;
        printStep(steps + 1, "Pass " + to_string(i+1) + " | Minimum found: " + highlight(arr[min_idx]) + " at index " + to_string(min_idx));
        sleep_ms(200);
        
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
            printStep(steps + 1, "Swapped " + to_string(arr[min_idx]) + " with " + to_string(arr[i]));
            displayArray(arr, n, i, min_idx);
        }
    }
    
    printResult("AFTER: Array sorted");
    displayArray(arr, n);
    Performance::log("Sorting", "SelectionSort", steps, comps);
}

void Sorting::insertionSort(int arr[], int n) {
    printHeader("Sorting", "Insertion Sort");
    printStep(1, "BEFORE: Unsorted array");
    displayArray(arr, n);
    
    int steps = 0;
    int comps = 0;
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        steps++;
        printStep(steps + 1, "Inserting " + highlight(key));
        sleep_ms(200);
        
        while (j >= 0 && arr[j] > key) {
            comps++;
            arr[j + 1] = arr[j];
            j = j - 1;
            displayArray(arr, n, j+1, j+2);
        }
        if(j >= 0) comps++; // For the failed condition
        
        arr[j + 1] = key;
        displayArray(arr, n, j+1);
    }
    
    printResult("AFTER: Array sorted");
    displayArray(arr, n);
    Performance::log("Sorting", "InsertionSort", steps, comps);
}

void Sorting::merge(int arr[], int left, int mid, int right, int& steps, int& comps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[100], R[100]; // Assuming max array size is < 100 for visualization
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    printStep(steps + 2, "Merging [" + to_string(left) + ".." + to_string(mid) + "] and [" + to_string(mid+1) + ".." + to_string(right) + "]");
    sleep_ms(200);
    steps++;
    
    while (i < n1 && j < n2) {
        comps++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void Sorting::mergeSortRecursive(int arr[], int left, int right, int& steps, int& comps) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    steps++;
    
    mergeSortRecursive(arr, left, mid, steps, comps);
    mergeSortRecursive(arr, mid + 1, right, steps, comps);
    merge(arr, left, mid, right, steps, comps);
}

void Sorting::mergeSort(int arr[], int n) {
    printHeader("Sorting", "Merge Sort");
    printStep(1, "BEFORE: Unsorted array");
    displayArray(arr, n);
    
    int steps = 0;
    int comps = 0;
    
    mergeSortRecursive(arr, 0, n - 1, steps, comps);
    
    printResult("AFTER: Array sorted");
    displayArray(arr, n);
    Performance::log("Sorting", "MergeSort", steps, comps);
}

int Sorting::partition(int arr[], int low, int high, int& steps, int& comps) {
    int pivot = arr[high];
    int i = (low - 1);
    
    printStep(steps + 2, "Partitioning [" + to_string(low) + ".." + to_string(high) + "] with pivot " + highlight(pivot));
    sleep_ms(200);
    steps++;
    
    for (int j = low; j <= high - 1; j++) {
        comps++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void Sorting::quickSortRecursive(int arr[], int low, int high, int& steps, int& comps) {
    if (low < high) {
        steps++;
        int pi = partition(arr, low, high, steps, comps);
        
        quickSortRecursive(arr, low, pi - 1, steps, comps);
        quickSortRecursive(arr, pi + 1, high, steps, comps);
    }
}

void Sorting::quickSort(int arr[], int n) {
    printHeader("Sorting", "Quick Sort");
    printStep(1, "BEFORE: Unsorted array");
    displayArray(arr, n);
    
    int steps = 0;
    int comps = 0;
    
    quickSortRecursive(arr, 0, n - 1, steps, comps);
    
    printResult("AFTER: Array sorted");
    displayArray(arr, n);
    Performance::log("Sorting", "QuickSort", steps, comps);
}
