#include <iostream>
#include "array.h"

using namespace std;

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

    arr[size++] = value;

    cout << "[SUCCESS] Inserted at end.\n";
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

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
        shifts++;
    }

    arr[index] = value;
    size++;

    cout << "After : ";
    display();

    cout << "[INFO] Shifts performed: " << shifts << endl;
    cout << "[INFO] Time Complexity: O(n)\n";
}

// Delete
void Array::deleteAt(int index) {
    if (size == 0) {
        cout << "[ERROR] Array is empty!\n";
        return;
    }

    if (index < 0 || index >= size) {
        cout << "[ERROR] Invalid index!\n";
        return;
    }

    cout << "\nBefore: ";
    display();

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;

    cout << "After : ";
    display();

    cout << "[INFO] Time Complexity: O(n)\n";
}

// Search
int Array::search(int value) {
    int comparisons = 0;

    for (int i = 0; i < size; i++) {
        comparisons++;
        if (arr[i] == value) {
            cout << "[FOUND] At index: " << i << endl;
            cout << "[INFO] Comparisons: " << comparisons << endl;
            return i;
        }
    }

    cout << "[NOT FOUND]\n";
    cout << "[INFO] Comparisons: " << comparisons << endl;
    return -1;
}

// Display
void Array::display() {
    if (size == 0) {
        cout << "[EMPTY]\n";
        return;
    }

    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]\n";
}

// Get size
int Array::getSize() {
    return size;
}