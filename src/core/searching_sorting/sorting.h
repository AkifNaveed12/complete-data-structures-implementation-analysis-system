#ifndef SORTING_H
#define SORTING_H

#include "../../analysis/visual.h"
#include "../../analysis/performance.h"
#include <string>

class Sorting {
private:
    static void merge(int arr[], int left, int mid, int right, int& steps, int& comps);
    static void mergeSortRecursive(int arr[], int left, int right, int& steps, int& comps);
    static int partition(int arr[], int low, int high, int& steps, int& comps);
    static void quickSortRecursive(int arr[], int low, int high, int& steps, int& comps);
    static void displayArray(int arr[], int n, int active1 = -1, int active2 = -1);

public:
    static void bubbleSort(int arr[], int n);
    static void selectionSort(int arr[], int n);
    static void insertionSort(int arr[], int n);
    static void mergeSort(int arr[], int n);
    static void quickSort(int arr[], int n);
};

#endif
