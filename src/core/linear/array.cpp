#include <iostream>
#include <thread>
#include <chrono>
#include "array.h"
#include "../../analysis/performance.h"
#include "../../analysis/visual.h"

using namespace std;

void printArrayVisual(int arr[], int size, int highlight = -1) {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        if (i == highlight)
            cout << "(" << arr[i] << ") ";
        else
            cout << arr[i] << " ";
    }
    cout << "]\n";
}

// Constructor
Array::Array(int cap) {
    capacity = cap;
    size = 0;
    arr = new int[capacity];

    // Default demo data
    int demo[] = {10, 20, 30, 40, 50};
    int demoSize = 5;

    for (int i = 0; i < demoSize; i++) {
        arr[size++] = demo[i];
    }
}

// Destructor
Array::~Array() {
    delete[] arr;
}

// Insert at end
void Array::insertEnd(int value) {
    if (size >= capacity) {
        cout << "[ERROR] Array is full!\n";
        return;
    }

    cout << "\nBefore: ";
    display();

    cout << "\nInserting at end...\n";
    sleep_ms(300);

    arr[size] = value;

    printArrayVisual(arr, size + 1, size);
    sleep_ms(400);

    size++;

    cout << "[SUCCESS] Inserted at end.\n";

    cout << "After : ";
    display();

    Performance::log("Array Insert", 1);
}

// Insert at index
void Array::insertAt(int index, int value) {
    if (index < 0 || index > size) {
        cout << "[ERROR] Invalid index!\n";
        return;
    }

    if (size >= capacity) {
        cout << "[ERROR] Array is full!\n";
        return;
    }

    cout << "\nBefore: ";
    display();

    int shifts = 0;

    cout << "\nShifting elements...\n";

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
        shifts++;

        printArrayVisual(arr, size + 1, i);
        sleep_ms(400);
    }

    cout << "\nInserting value...\n";
    sleep_ms(300);

    arr[index] = value;
    size++;

    printArrayVisual(arr, size, index);

    cout << "\nAfter : ";
    display();

    cout << "[INFO] Shifts performed: " << shifts << endl;

    Performance::log("Array Insert", shifts);
}

// Delete
void Array::deleteAt(int index) {
    if (size == 0) {
        cout << "[ERROR] Array is empty!\n";
        Performance::log("Array Delete", 1);
        return;
    }

    if (index < 0 || index >= size) {
        cout << "[ERROR] Invalid index!\n";
        Performance::log("Array Delete", 1);
        return;
    }

    cout << "\nBefore: ";
    display();

    int shifts = 0;

    cout << "\nDeleting element...\n";
    sleep_ms(300);

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
        shifts++;

        printArrayVisual(arr, size, i);
        sleep_ms(400);
    }

    size--;

    cout << "\nAfter : ";
    display();

    cout << "[INFO] Time Complexity: O(n)\n";

    Performance::log("Array Delete", shifts);
}
// Search
int Array::search(int value) {
    int comparisons = 0;

    cout << "\nSearching...\n";

    for (int i = 0; i < size; i++) {
        comparisons++;

        printArrayVisual(arr, size, i);
        sleep_ms(400);

        if (arr[i] == value) {
            cout << "[FOUND] At index: " << i << endl;
            cout << "[INFO] Comparisons: " << comparisons << endl;

            Performance::log("Array Search", comparisons);
            return i;
        }
    }

    cout << "[NOT FOUND]\n";

    Performance::log("Array Search", comparisons);
    return -1;
}
// Display
void Array::display() {
    if (size == 0) {
        cout << "[EMPTY]\n";
        Performance::log("Array Display", 1);
        return;
    }

    printArrayVisual(arr, size);
    Performance::log("Array Display", size);
}

// Get size
int Array::getSize() {
    return size;
}