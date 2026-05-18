#include "searching.h"

using namespace std;

int Searching::linearSearch(int arr[], int n, int key) {
    printHeader("Searching", "Linear Search");
    printStep(1, "BEFORE: Starting linear search for " + highlight(key));
    
    int steps = 0;
    int comps = 0;
    
    for (int i = 0; i < n; i++) {
        notifyArrayState(arr, n, i);
        printStep(steps + 2, "Checking index " + to_string(i) + " value: " + highlight(arr[i]));
        sleep_ms(300);
        steps++;
        comps++;
        
        if (arr[i] == key) {
            printResult("AFTER: Value " + highlight(key) + " found at index " + to_string(i));
            Performance::log("Searching", "LinearSearch", steps, comps);
            return i;
        }
    }
    
    printResult("AFTER: Value " + highlight(key) + " not found");
    Performance::log("Searching", "LinearSearch", steps, comps);
    return -1;
}

int Searching::binarySearch(int arr[], int n, int key) {
    printHeader("Searching", "Binary Search");
    printStep(1, "BEFORE: Starting binary search for " + highlight(key));
    
    int left = 0, right = n - 1;
    int steps = 0;
    int comps = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        steps++;
        comps++;
        
        notifyArrayState(arr, n, mid);
        printStep(steps + 1, "[left=" + to_string(left) + "] [mid=" + to_string(mid) + "(" + highlight(arr[mid]) + ")] [right=" + to_string(right) + "]");
        sleep_ms(300);
        
        if (arr[mid] == key) {
            printResult("AFTER: Value " + highlight(key) + " found at index " + to_string(mid));
            Performance::log("Searching", "BinarySearch", steps, comps);
            return mid;
        }
        
        comps++;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    printResult("AFTER: Value " + highlight(key) + " not found");
    Performance::log("Searching", "BinarySearch", steps, comps);
    return -1;
}
