// ============================================================
//  CDSIAS — Array Module
//  src/core/linear/array.cpp
//
//  All output goes through visual.h ONLY — no raw cout.
//  Performance::log() called after every operation.
//  Follows BEFORE → STEP N → AFTER phase contract.
//  contracts.md §1, §2, §3
// ============================================================

#include <string>
#include "array.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Internal helper: print the full array state
// Active element shown as (val), all others as plain val.
// contracts.md §1.2, §1.4
// --------------------------------------------------------
static void printArrayState(int arr[], int size, int activeIndex = -1) {
    notifyArrayState(arr, size, activeIndex);
}

// --------------------------------------------------------
// Constructor — starts EMPTY (no demo data)
// --------------------------------------------------------
Array::Array(int cap) {
    capacity = cap;
    size     = 0;
    arr      = new int[capacity];
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
Array::~Array() {
    delete[] arr;
}

// --------------------------------------------------------
// getSize
// --------------------------------------------------------
int Array::getSize() const {
    return size;
}

int Array::getCapacity() const {
    return capacity;
}

const int* Array::getArray() const {
    return arr;
}

// --------------------------------------------------------
// display — show full current array state
// NOTE: display is NOT logged (contracts §3 — display is UI only)
// --------------------------------------------------------
void Array::display() {
    if (size == 0) {
        printError("Structure is empty");
        return;
    }
    printArrayState(arr, size);
}

// --------------------------------------------------------
// insertEnd — O(1)
// contracts.md §2.3
// --------------------------------------------------------
void Array::insertEnd(int value) {
    printHeader("Array", "Insert at End: " + to_string(value));

    // Edge case: overflow
    if (size >= capacity) {
        printError("Structure is full (capacity: " + to_string(capacity) + ")");
        Performance::log("Array", "InsertEnd", 0, 0);
        return;
    }

    // BEFORE
    printStep(1, "BEFORE:");
    if (size == 0)
        notifyArrayState(nullptr, 0);
    else
        printArrayState(arr, size);

    sleep_ms(500);

    // Insert
    arr[size] = value;
    size++;

    // AFTER
    printStep(2, "Placing " + highlight(value) + " at end (index " + to_string(size-1) + ")");
    printArrayState(arr, size, size - 1);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at index " + to_string(size - 1));
    printArrayState(arr, size);

    // Log: InsertEnd = 1 step, 0 comparisons
    Performance::log("Array", "InsertEnd", 1, 0);
}

// --------------------------------------------------------
// insertAt — O(n)
// contracts.md §2.3
// --------------------------------------------------------
void Array::insertAt(int index, int value) {
    printHeader("Array", "Insert at Index " + to_string(index) + ": " + to_string(value));

    // Edge case: invalid index
    if (index < 0 || index > size) {
        printError("Invalid index [" + to_string(index) + "], valid range [0.." + to_string(size) + "]");
        Performance::log("Array", "InsertAtIndex", 0, 0);
        return;
    }

    // Edge case: overflow
    if (size >= capacity) {
        printError("Structure is full (capacity: " + to_string(capacity) + ")");
        Performance::log("Array", "InsertAtIndex", 0, 0);
        return;
    }

    // BEFORE
    printStep(1, "BEFORE:");
    if (size == 0)
        notifyArrayState(nullptr, 0);
    else
        printArrayState(arr, size);
    sleep_ms(500);

    int stepNum = 2;
    int shifts  = 0;

    // Shift elements right one by one (animation)
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
        shifts++;

        printStep(stepNum++, "Shifting " + highlight(arr[i]) + " right to index " + to_string(i));
        printArrayState(arr, size + 1, i);
        sleep_ms(200);  // array shift delay (contracts.md §1.5)
    }

    // Place new element
    arr[index] = value;
    size++;

    printStep(stepNum++, "Placing " + highlight(value) + " at index " + to_string(index));
    printArrayState(arr, size, index);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at index " + to_string(index) +
                " | Shifts: " + to_string(shifts));
    printArrayState(arr, size);

    // Log: steps = shifts performed, comparisons = 0
    Performance::log("Array", "InsertAtIndex", shifts, 0);
}

// --------------------------------------------------------
// deleteAt — O(n)
// contracts.md §2.3
// --------------------------------------------------------
void Array::deleteAt(int index) {
    printHeader("Array", "Delete at Index " + to_string(index));

    // Edge case: empty
    if (size == 0) {
        printError("Structure is empty");
        Performance::log("Array", "DeleteAtIndex", 0, 0);
        return;
    }

    // Edge case: invalid index
    if (index < 0 || index >= size) {
        printError("Invalid index [" + to_string(index) + "], valid range [0.." + to_string(size - 1) + "]");
        Performance::log("Array", "DeleteAtIndex", 0, 0);
        return;
    }

    // BEFORE
    printStep(1, "BEFORE:");
    printArrayState(arr, size);
    sleep_ms(500);

    int deletedVal = arr[index];
    int stepNum    = 2;
    int shifts     = 0;

    // Highlight element being deleted
    printStep(stepNum++, "Marking " + highlight(deletedVal) + " at index " + to_string(index) + " for deletion");
    printArrayState(arr, size, index);
    sleep_ms(500);

    // Shift elements left one by one
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
        shifts++;

        printStep(stepNum++, "Shifting " + highlight(arr[i]) + " left to index " + to_string(i));
        printArrayState(arr, size, i);
        sleep_ms(200);  // array shift delay (contracts.md §1.5)
    }

    size--;

    printResult("AFTER: " + to_string(deletedVal) + " deleted | Shifts: " + to_string(shifts));
    if (size == 0)
        notifyArrayState(nullptr, 0);
    else
        printArrayState(arr, size);

    // Log: steps = shifts performed
    Performance::log("Array", "DeleteAtIndex", shifts, 0);
}

// --------------------------------------------------------
// search — O(n) linear search
// contracts.md §2.3
// --------------------------------------------------------
int Array::search(int value) {
    printHeader("Array", "Search: " + to_string(value));

    // Edge case: empty
    if (size == 0) {
        printError("Structure is empty");
        Performance::log("Array", "Search", 0, 0);
        return -1;
    }

    // BEFORE
    printStep(1, "BEFORE:");
    printArrayState(arr, size);
    sleep_ms(500);

    int comparisons = 0;

    for (int i = 0; i < size; i++) {
        comparisons++;
        printStep(i + 2, "Checking " + highlight(arr[i]) + " at index " + to_string(i));
        printArrayState(arr, size, i);
        sleep_ms(300);  // traversal delay (contracts.md §1.5)

        if (arr[i] == value) {
            printResult("Value " + to_string(value) + " found at index " + to_string(i) +
                        " | Comparisons: " + to_string(comparisons));
            Performance::log("Array", "Search", comparisons, comparisons);
            return i;
        }
    }

    printResult("Value " + to_string(value) + " not found | Comparisons: " + to_string(comparisons));
    Performance::log("Array", "Search", comparisons, comparisons);
    return -1;
}