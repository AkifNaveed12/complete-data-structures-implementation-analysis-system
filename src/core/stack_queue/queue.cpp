// ============================================================
//  CDSIAS — Queue Module
//  src/core/stack_queue/queue.cpp
//
//  All output goes through visual.h ONLY.
//  Performance::log() called after every operation.
//  Follows BEFORE -> STEP N -> AFTER phase contract.
// ============================================================

#include <string>
#include <iostream>
#include "queue.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Internal helper: print full simple queue state
// Format: FRONT -> [ 10 ] [ 20 ] [ (30) ] <- REAR
// --------------------------------------------------------
static void printSimpleQueueState(int arr[], int front, int rear, int activeIndex = -1) {
    if (front == -1 || front > rear) {
        cout << "[ empty ]\n";
        return;
    }

    cout << "FRONT -> ";
    for (int i = front; i <= rear; i++) {
        if (i == activeIndex) {
            cout << "[ " << highlight(arr[i]) << " ] ";
        } else {
            cout << "[ " << arr[i] << " ] ";
        }
    }
    cout << "<- REAR\n";
}

// ============================================================
// SIMPLE QUEUE IMPLEMENTATION
// ============================================================

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
SimpleQueue::SimpleQueue(int cap) {
    capacity = cap;
    arr = new int[capacity];
    front = -1;
    rear = -1;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
SimpleQueue::~SimpleQueue() {
    delete[] arr;
}

// --------------------------------------------------------
// display — show full current state
// --------------------------------------------------------
void SimpleQueue::display() {
    if (front == -1 || front > rear) {
        printError("Structure is empty");
        return;
    }
    printSimpleQueueState(arr, front, rear);
}

// --------------------------------------------------------
// enqueue — O(1)
// --------------------------------------------------------
void SimpleQueue::enqueue(int value) {
    printHeader("SimpleQueue", "Enqueue: " + to_string(value));

    if (rear >= capacity - 1) {
        printError("Structure is full (capacity: " + to_string(capacity) + ")");
        Performance::log("Queue", "Enqueue", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printSimpleQueueState(arr, front, rear);
    sleep_ms(500);

    if (front == -1) {
        front = 0;
    }
    
    rear++;
    arr[rear] = value;

    printStep(2, "Enqueueing " + highlight(value) + " at rear");
    printSimpleQueueState(arr, front, rear, rear);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " enqueued");
    printSimpleQueueState(arr, front, rear);

    Performance::log("Queue", "Enqueue", 1, 0);
}

// --------------------------------------------------------
// dequeue — O(1)
// --------------------------------------------------------
void SimpleQueue::dequeue() {
    printHeader("SimpleQueue", "Dequeue");

    if (front == -1 || front > rear) {
        printError("Structure is empty");
        Performance::log("Queue", "Dequeue", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printSimpleQueueState(arr, front, rear);
    sleep_ms(500);

    int dequeuedValue = arr[front];

    printStep(2, "Dequeueing " + highlight(dequeuedValue) + " from front");
    printSimpleQueueState(arr, front, rear, front);
    sleep_ms(500);

    front++;
    // Reset if empty to allow reuse (standard SimpleQueue optimization in academia)
    if (front > rear) {
        front = -1;
        rear = -1;
    }

    printResult("AFTER: " + to_string(dequeuedValue) + " dequeued");
    printSimpleQueueState(arr, front, rear);

    Performance::log("Queue", "Dequeue", 1, 0);
}

// --------------------------------------------------------
// peek — O(1)
// --------------------------------------------------------
void SimpleQueue::peek() {
    printHeader("SimpleQueue", "Peek");

    if (front == -1 || front > rear) {
        printError("Structure is empty");
        Performance::log("Queue", "Peek", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printSimpleQueueState(arr, front, rear);
    sleep_ms(500);

    printStep(2, "Peeking at front element");
    printSimpleQueueState(arr, front, rear, front);
    sleep_ms(300);

    printResult("Front element is " + to_string(arr[front]));
    Performance::log("Queue", "Peek", 1, 0);
}

// ============================================================
// CIRCULAR QUEUE IMPLEMENTATION
// ============================================================

// --------------------------------------------------------
// Internal helper: print full circular queue state
// Format: 
// [ 30 ] [ 10 ] [ 20 ]
//   ^REAR       ^FRONT
// --------------------------------------------------------
static void printCircularQueueState(int arr[], int capacity, int front, int rear, int size, int activeIndex = -1) {
    if (size == 0) {
        cout << "[ empty ]\n";
        return;
    }

    // Print values
    for (int i = 0; i < capacity; i++) {
        if (i == activeIndex) {
            cout << "[ " << highlight(arr[i]) << " ] ";
        } else {
            cout << "[ " << arr[i] << " ] ";
        }
    }
    cout << "\n";

    // Print pointers
    for (int i = 0; i < capacity; i++) {
        string ptrStr = "";
        if (i == front && i == rear) {
            ptrStr = "^F/R";
        } else if (i == front) {
            ptrStr = "^FRONT";
        } else if (i == rear) {
            ptrStr = "^REAR";
        }

        if (ptrStr != "") {
            // align under the box "[ xx ] " -> approx 7 chars
            cout << "  " << ptrStr;
            int padding = 7 - 2 - ptrStr.length();
            if (padding > 0) cout << string(padding, ' ');
        } else {
            cout << "       "; // 7 spaces for empty box slot
        }
    }
    cout << "\n";
}

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
CircularQueue::CircularQueue(int cap) {
    capacity = cap;
    arr = new int[capacity];
    // Initialize array with 0s for visual clarity of empty slots
    for (int i = 0; i < capacity; i++) arr[i] = 0;
    front = -1;
    rear = -1;
    size = 0;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
CircularQueue::~CircularQueue() {
    delete[] arr;
}

// --------------------------------------------------------
// display
// --------------------------------------------------------
void CircularQueue::display() {
    if (size == 0) {
        printError("Structure is empty");
        return;
    }
    printCircularQueueState(arr, capacity, front, rear, size);
}

// --------------------------------------------------------
// enqueue — O(1)
// --------------------------------------------------------
void CircularQueue::enqueue(int value) {
    printHeader("CircularQueue", "Enqueue: " + to_string(value));

    if (size == capacity) {
        printError("Structure is full (capacity: " + to_string(capacity) + ")");
        Performance::log("CircularQueue", "Enqueue", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printCircularQueueState(arr, capacity, front, rear, size);
    sleep_ms(500);

    if (front == -1) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % capacity;
    }
    
    arr[rear] = value;
    size++;

    printStep(2, "Enqueueing " + highlight(value) + " at rear (index " + to_string(rear) + ")");
    printCircularQueueState(arr, capacity, front, rear, size, rear);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " enqueued");
    printCircularQueueState(arr, capacity, front, rear, size);

    Performance::log("CircularQueue", "Enqueue", 1, 0);
}

// --------------------------------------------------------
// dequeue — O(1)
// --------------------------------------------------------
void CircularQueue::dequeue() {
    printHeader("CircularQueue", "Dequeue");

    if (size == 0) {
        printError("Structure is empty");
        Performance::log("CircularQueue", "Dequeue", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printCircularQueueState(arr, capacity, front, rear, size);
    sleep_ms(500);

    int dequeuedValue = arr[front];
    arr[front] = 0; // Clear for visual clarity

    printStep(2, "Dequeueing " + highlight(dequeuedValue) + " from front (index " + to_string(front) + ")");
    printCircularQueueState(arr, capacity, front, rear, size, front);
    sleep_ms(500);

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % capacity;
    }
    size--;

    printResult("AFTER: " + to_string(dequeuedValue) + " dequeued");
    printCircularQueueState(arr, capacity, front, rear, size);

    Performance::log("CircularQueue", "Dequeue", 1, 0);
}

// --------------------------------------------------------
// peek — O(1)
// --------------------------------------------------------
void CircularQueue::peek() {
    printHeader("CircularQueue", "Peek");

    if (size == 0) {
        printError("Structure is empty");
        Performance::log("CircularQueue", "Peek", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printCircularQueueState(arr, capacity, front, rear, size);
    sleep_ms(500);

    printStep(2, "Peeking at front element");
    printCircularQueueState(arr, capacity, front, rear, size, front);
    sleep_ms(300);

    printResult("Front element is " + to_string(arr[front]));
    Performance::log("CircularQueue", "Peek", 1, 0);
}
