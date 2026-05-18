#include "../src/core/searching_sorting/sorting.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Testing Sorting Module ===\n";
    
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    Sorting::bubbleSort(arr1, 7);
    
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    Sorting::selectionSort(arr2, 7);
    
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    Sorting::insertionSort(arr3, 7);
    
    int arr4[] = {64, 34, 25, 12, 22, 11, 90};
    Sorting::mergeSort(arr4, 7);
    
    int arr5[] = {64, 34, 25, 12, 22, 11, 90};
    Sorting::quickSort(arr5, 7);
    
    Performance::display();
    return 0;
}
