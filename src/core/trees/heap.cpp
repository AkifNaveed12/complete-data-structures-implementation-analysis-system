// ============================================================
//  CDSIAS — Heap Implementation
//  src/core/trees/heap.cpp
// ============================================================

#include <iostream>
#include <string>
#include "heap.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Internal helper: Print Array with Highlights
// --------------------------------------------------------
static void printHeapArray(int* array, int size, int activeIdx1 = -1, int activeIdx2 = -1) {
    if (size == 0) {
        cout << "[ empty ]\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        if (i == activeIdx1 || i == activeIdx2) {
            cout << "[ " << highlight(array[i]) << " ] ";
        } else {
            cout << "[ " << array[i] << " ] ";
        }
    }
    cout << "\n";
}

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
Heap::Heap(int cap, bool minHeap) {
    capacity = cap;
    size = 0;
    isMinHeap = minHeap;
    array = new int[capacity];
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
Heap::~Heap() {
    delete[] array;
}

// --------------------------------------------------------
// Display
// --------------------------------------------------------
void Heap::display() {
    printHeapArray(array, size);
}

// --------------------------------------------------------
// Swap
// --------------------------------------------------------
void Heap::swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

// --------------------------------------------------------
// Heapify Up (used in Insert)
// --------------------------------------------------------
void Heap::heapifyUp(int i, int& steps, int& comparisons) {
    while (i != 0) {
        comparisons++;
        int p = parent(i);
        bool shouldSwap = false;
        
        if (isMinHeap && array[i] < array[p]) {
            shouldSwap = true;
        } else if (!isMinHeap && array[i] > array[p]) {
            shouldSwap = true;
        }

        if (shouldSwap) {
            printStep(steps++, "Comparing child " + to_string(array[i]) + " with parent " + to_string(array[p]) + " -> Swapping");
            printHeapArray(array, size, i, p);
            sleep_ms(300);
            
            swap(array[i], array[p]);
            i = p;
        } else {
            printStep(steps++, "Heap property satisfied.");
            break;
        }
    }
}

// --------------------------------------------------------
// Heapify Down (used in Extract)
// --------------------------------------------------------
void Heap::heapifyDown(int i, int& steps, int& comparisons) {
    while (true) {
        int l = left(i);
        int r = right(i);
        int target = i;

        comparisons++;
        if (l < size) {
            if (isMinHeap && array[l] < array[target]) target = l;
            if (!isMinHeap && array[l] > array[target]) target = l;
        }

        comparisons++;
        if (r < size) {
            if (isMinHeap && array[r] < array[target]) target = r;
            if (!isMinHeap && array[r] > array[target]) target = r;
        }

        if (target != i) {
            printStep(steps++, "Swapping parent " + to_string(array[i]) + " with target child " + to_string(array[target]));
            printHeapArray(array, size, i, target);
            sleep_ms(300);
            
            swap(array[i], array[target]);
            i = target;
        } else {
            printStep(steps++, "Heap property satisfied.");
            break;
        }
    }
}

// --------------------------------------------------------
// Insert
// --------------------------------------------------------
void Heap::insert(int value) {
    string type = isMinHeap ? "MinHeap" : "MaxHeap";
    printHeader(type, "Insert: " + to_string(value));

    if (size == capacity) {
        printError("Heap Overflow");
        Performance::log(type, "Insert", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printHeapArray(array, size);
    sleep_ms(300);

    int steps = 2;
    int comparisons = 0;

    array[size] = value;
    int i = size;
    size++;

    printStep(steps++, "Inserting at end of array");
    printHeapArray(array, size, i);
    sleep_ms(300);

    printStep(steps++, "Heapifying up...");
    heapifyUp(i, steps, comparisons);

    printResult("AFTER: " + to_string(value) + " inserted");
    printHeapArray(array, size);

    Performance::log(type, "Insert", steps, comparisons);
}

// --------------------------------------------------------
// Extract
// --------------------------------------------------------
void Heap::extract() {
    string type = isMinHeap ? "MinHeap" : "MaxHeap";
    printHeader(type, "Extract Root");

    if (size <= 0) {
        printError("Structure is empty");
        Performance::log(type, "Extract", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printHeapArray(array, size);
    sleep_ms(300);

    int steps = 2;
    int comparisons = 0;

    int rootVal = array[0];
    
    if (size == 1) {
        size--;
        printStep(steps++, "Extracting only element: " + to_string(rootVal));
    } else {
        array[0] = array[size - 1];
        size--;
        
        printStep(steps++, "Replacing root with last element " + to_string(array[0]));
        printHeapArray(array, size, 0);
        sleep_ms(300);

        printStep(steps++, "Heapifying down...");
        heapifyDown(0, steps, comparisons);
    }

    printResult("AFTER: " + to_string(rootVal) + " extracted");
    printHeapArray(array, size);

    Performance::log(type, "Extract", steps, comparisons);
}
