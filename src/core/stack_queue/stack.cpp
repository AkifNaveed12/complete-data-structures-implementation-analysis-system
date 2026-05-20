// ============================================================
//  CDSIAS â€” Stack Module
//  src/core/stack_queue/stack.cpp
//
//  All output goes through visual.h ONLY.
//  Performance::log() called after every operation.
//  Follows BEFORE -> STEP N -> AFTER phase contract.
// ============================================================

#include <iostream>
#include <string>
#include "stack.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

int g_sqOperationCount = 0;

// --------------------------------------------------------
// Internal helper: print full stack state (Vertical)
// Format:
// [ TOP ]
//   (30)
//    20
//    10
// --------------------------------------------------------
static void printStaticStackState(int arr[], int top, int activeIndex = -1) {
    if (top == -1) {
        cout << "[ empty ]\n";
        return;
    }

    cout << "[ TOP ]\n";
    for (int i = top; i >= 0; i--) {
        if (i == activeIndex) {
            cout << "  " << highlight(arr[i]) << "\n";
        } else {
            cout << "   " << arr[i] << "\n";
        }
    }
}

// ============================================================
// STATIC STACK IMPLEMENTATION
// ============================================================

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
StaticStack::StaticStack(int cap) {
    capacity = cap;
    arr = new int[capacity];
    top = -1;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
StaticStack::~StaticStack() {
    delete[] arr;
}

// --------------------------------------------------------
// display â€” show full current state
// --------------------------------------------------------
void StaticStack::display() {
    if (top == -1) {
        printError("Structure is empty");
        return;
    }
    printStaticStackState(arr, top);
}

// --------------------------------------------------------
// push â€” O(1)
// --------------------------------------------------------
void StaticStack::push(int value) {
    printHeader("Stack", "Push: " + to_string(value));

    if (top >= capacity - 1) {
        printError("Structure is full (capacity: " + to_string(capacity) + ")");
        Performance::log("Stack", "Push", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printStaticStackState(arr, top);
    sleep_ms(500);

    top++;
    arr[top] = value;

    printStep(2, "Pushing " + highlight(value) + " to top");
    printStaticStackState(arr, top, top);
    sleep_ms(300);

    g_sqOperationCount++;
    printResult("AFTER: " + to_string(value) + " pushed onto stack\nOperation Count: " + to_string(g_sqOperationCount));
    printStaticStackState(arr, top);

    Performance::log("Stack", "Push", 1, 0);
}

// --------------------------------------------------------
// pop â€” O(1)
// --------------------------------------------------------
void StaticStack::pop() {
    printHeader("Stack", "Pop");

    if (top == -1) {
        printError("Structure is empty");
        Performance::log("Stack", "Pop", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printStaticStackState(arr, top);
    sleep_ms(500);

    int poppedValue = arr[top];

    printStep(2, "Popping " + highlight(poppedValue) + " from top");
    printStaticStackState(arr, top, top);
    sleep_ms(500);

    top--;

    g_sqOperationCount++;
    printResult("AFTER: " + to_string(poppedValue) + " popped from stack\nOperation Count: " + to_string(g_sqOperationCount));
    printStaticStackState(arr, top);

    Performance::log("Stack", "Pop", 1, 0);
}

// --------------------------------------------------------
// peek â€” O(1)
// --------------------------------------------------------
void StaticStack::peek() {
    printHeader("Stack", "Peek");

    if (top == -1) {
        printError("Structure is empty");
        Performance::log("Stack", "Peek", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printStaticStackState(arr, top);
    sleep_ms(500);

    printStep(2, "Peeking at top element");
    printStaticStackState(arr, top, top);
    sleep_ms(300);

    printResult("Top element is " + to_string(arr[top]));
    Performance::log("Stack", "Peek", 1, 0);
}

// ============================================================
// DYNAMIC STACK IMPLEMENTATION
// ============================================================

// --------------------------------------------------------
// Internal helper: print full dynamic stack state
// --------------------------------------------------------
static void printDynamicStackState(SNode* topNode, SNode* activeNode = nullptr) {
    if (topNode == nullptr) {
        cout << "[ empty ]\n";
        return;
    }

    cout << "[ TOP ]\n";
    SNode* cur = topNode;
    while (cur != nullptr) {
        if (cur == activeNode) {
            cout << "  " << highlight(cur->data) << "\n";
        } else {
            cout << "   " << cur->data << "\n";
        }
        cur = cur->next;
    }
}

// --------------------------------------------------------
// SNode Constructor
// --------------------------------------------------------
SNode::SNode(int val) {
    data = val;
    next = nullptr;
}

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
DynamicStack::DynamicStack() {
    topNode = nullptr;
    size = 0;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
DynamicStack::~DynamicStack() {
    SNode* cur = topNode;
    while (cur != nullptr) {
        SNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}

// --------------------------------------------------------
// display
// --------------------------------------------------------
void DynamicStack::display() {
    if (topNode == nullptr) {
        printError("Structure is empty");
        return;
    }
    printDynamicStackState(topNode);
}

// --------------------------------------------------------
// push â€” O(1)
// --------------------------------------------------------
void DynamicStack::push(int value) {
    printHeader("DynamicStack", "Push: " + to_string(value));

    printStep(1, "BEFORE:");
    printDynamicStackState(topNode);
    sleep_ms(500);

    SNode* newNode = new SNode(value);
    printStep(2, "Creating new node " + highlight(value));
    sleep_ms(300);

    newNode->next = topNode;
    topNode = newNode;
    size++;

    printStep(3, "Pushing " + highlight(value) + " to top");
    printDynamicStackState(topNode, topNode);
    sleep_ms(300);

    g_sqOperationCount++;
    printResult("AFTER: " + to_string(value) + " pushed onto stack\nOperation Count: " + to_string(g_sqOperationCount));
    printDynamicStackState(topNode);

    Performance::log("Stack", "Push", 1, 0);
}

// --------------------------------------------------------
// pop â€” O(1)
// --------------------------------------------------------
void DynamicStack::pop() {
    printHeader("DynamicStack", "Pop");

    if (topNode == nullptr) {
        printError("Structure is empty");
        Performance::log("Stack", "Pop", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printDynamicStackState(topNode);
    sleep_ms(500);

    int poppedValue = topNode->data;

    printStep(2, "Popping " + highlight(poppedValue) + " from top");
    printDynamicStackState(topNode, topNode);
    sleep_ms(500);

    SNode* delNode = topNode;
    topNode = topNode->next;
    delete delNode;
    size--;

    g_sqOperationCount++;
    printResult("AFTER: " + to_string(poppedValue) + " popped from stack\nOperation Count: " + to_string(g_sqOperationCount));
    printDynamicStackState(topNode);

    Performance::log("Stack", "Pop", 1, 0);
}

// --------------------------------------------------------
// peek â€” O(1)
// --------------------------------------------------------
void DynamicStack::peek() {
    printHeader("DynamicStack", "Peek");

    if (topNode == nullptr) {
        printError("Structure is empty");
        Performance::log("Stack", "Peek", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printDynamicStackState(topNode);
    sleep_ms(500);

    printStep(2, "Peeking at top element");
    printDynamicStackState(topNode, topNode);
    sleep_ms(300);

    printResult("Top element is " + to_string(topNode->data));
    Performance::log("Stack", "Peek", 1, 0);
}




// ============================================================
// GUI Helper: getSnapshot -- fills int[] top-to-bottom
// ============================================================
int StaticStack::getSnapshot(int* out, int maxSize) const {
    int count = 0;
    for (int i = top; i >= 0 && count < maxSize; i--)
        out[count++] = arr[i];
    return count;
}

int DynamicStack::getSnapshot(int* out, int maxSize) const {
    int count = 0;
    SNode* cur = topNode;
    while (cur && count < maxSize) { out[count++] = cur->data; cur = cur->next; }
    return count;
}
