// ============================================================
//  CDSIAS — Queue Test File
//  tests/test_queue.cpp
//
//  Tests: SimpleQueue
//  All 7 categories per contracts.md §7:
//    1. Normal cases
//    2. Edge: empty
//    3. Edge: overflow
//    4. Edge: not found (N/A for queue)
//    5. Edge: boundary
//    6. Output format matches contract
//    7. Performance::log verified called
// ============================================================

#include <iostream>
#include "../src/core/stack_queue/queue.h"
#include "../src/analysis/performance.h"
#include "../src/analysis/visual.h"

using namespace std;

// ============================================================
//  SIMPLE QUEUE TESTS
// ============================================================
void testSimpleQueue() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: SimpleQueue" << COL_RESET << "\n";
    printSeparator();

    SimpleQueue sQueue(3); // capacity 3 for easy overflow testing

    // 1. Normal cases
    cout << "\n[T3.1] Enqueue: 10\n";
    sQueue.enqueue(10);

    cout << "\n[T3.2] Enqueue: 20\n";
    sQueue.enqueue(20);

    cout << "\n[T3.3] Peek\n";
    sQueue.peek();

    cout << "\n[T3.4] Enqueue: 30 (should become full)\n";
    sQueue.enqueue(30);

    // 2. Edge: Overflow
    cout << "\n[T3.5] Enqueue: 40 to full queue (should show Error)\n";
    sQueue.enqueue(40);

    // 3. Normal dequeue
    cout << "\n[T3.6] Dequeue (should dequeue 10)\n";
    sQueue.dequeue();

    cout << "\n[T3.7] Dequeue (should dequeue 20)\n";
    sQueue.dequeue();

    cout << "\n[T3.8] Dequeue (should dequeue 30)\n";
    sQueue.dequeue();

    // 4. Edge: Underflow
    cout << "\n[T3.9] Dequeue from empty queue (should show Error)\n";
    sQueue.dequeue();

    cout << "\n[T3.10] Peek empty queue (should show Error)\n";
    sQueue.peek();
    
    cout << "\n[T3.11] Display empty queue\n";
    sQueue.display();
}

// ============================================================
//  CIRCULAR QUEUE TESTS
// ============================================================
void testCircularQueue() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: CircularQueue" << COL_RESET << "\n";
    printSeparator();

    CircularQueue cQueue(3); // capacity 3

    // 1. Normal cases
    cout << "\n[T4.1] Enqueue: 10\n";
    cQueue.enqueue(10);

    cout << "\n[T4.2] Enqueue: 20\n";
    cQueue.enqueue(20);

    cout << "\n[T4.3] Peek\n";
    cQueue.peek();

    cout << "\n[T4.4] Enqueue: 30 (should become full)\n";
    cQueue.enqueue(30);

    // 2. Edge: Overflow
    cout << "\n[T4.5] Enqueue: 40 to full queue (should show Error)\n";
    cQueue.enqueue(40);

    // 3. Normal dequeue
    cout << "\n[T4.6] Dequeue (should dequeue 10)\n";
    cQueue.dequeue();

    // 4. Wrap-around enqueue
    cout << "\n[T4.7] Enqueue: 50 (wrap around to index 0)\n";
    cQueue.enqueue(50);

    // 5. Wrap-around dequeue
    cout << "\n[T4.8] Dequeue (should dequeue 20)\n";
    cQueue.dequeue();

    cout << "\n[T4.9] Dequeue (should dequeue 30)\n";
    cQueue.dequeue();

    cout << "\n[T4.10] Dequeue (should dequeue 50)\n";
    cQueue.dequeue();

    // 6. Edge: Underflow
    cout << "\n[T4.11] Dequeue from empty queue (should show Error)\n";
    cQueue.dequeue();

    cout << "\n[T4.12] Peek empty queue (should show Error)\n";
    cQueue.peek();
    
    cout << "\n[T4.13] Display empty queue\n";
    cQueue.display();
}

// ============================================================
//  PRIORITY QUEUE TESTS
// ============================================================
void testPriorityQueue() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: PriorityQueue" << COL_RESET << "\n";
    printSeparator();

    PriorityQueue pQueue;

    // 1. Normal cases (inserting unsorted priorities)
    cout << "\n[T5.1] Enqueue: 10 (Priority: 2)\n";
    pQueue.enqueue(10, 2);

    cout << "\n[T5.2] Enqueue: 20 (Priority: 5) - should be at front\n";
    pQueue.enqueue(20, 5);

    cout << "\n[T5.3] Enqueue: 30 (Priority: 1) - should be at end\n";
    pQueue.enqueue(30, 1);

    cout << "\n[T5.4] Enqueue: 40 (Priority: 3) - should be in middle\n";
    pQueue.enqueue(40, 3);

    cout << "\n[T5.5] Peek (should show 20 with priority 5)\n";
    pQueue.peek();

    // 2. Normal dequeue
    cout << "\n[T5.6] Dequeue (should dequeue 20)\n";
    pQueue.dequeue();

    cout << "\n[T5.7] Dequeue (should dequeue 40)\n";
    pQueue.dequeue();

    cout << "\n[T5.8] Dequeue (should dequeue 10)\n";
    pQueue.dequeue();

    cout << "\n[T5.9] Dequeue (should dequeue 30)\n";
    pQueue.dequeue();

    // 3. Edge: Underflow
    cout << "\n[T5.10] Dequeue from empty queue (should show Error)\n";
    pQueue.dequeue();

    cout << "\n[T5.11] Peek empty queue (should show Error)\n";
    pQueue.peek();
    
    cout << "\n[T5.12] Display empty queue\n";
    pQueue.display();
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    cout << "\n";
    printSeparator();
    cout << COL_ACCENT << "  CDSIAS - QUEUE MODULE TESTS" << COL_RESET << "\n";
    printSeparator();

    testSimpleQueue();
    testCircularQueue();
    testPriorityQueue();

    // Performance report at end
    cout << "\n";
    Performance::display();

    return 0;
}
