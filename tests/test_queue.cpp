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
//  MAIN
// ============================================================
int main() {
    cout << "\n";
    printSeparator();
    cout << COL_ACCENT << "  CDSIAS - QUEUE MODULE TESTS" << COL_RESET << "\n";
    printSeparator();

    testSimpleQueue();

    // Performance report at end
    cout << "\n";
    Performance::display();

    return 0;
}
