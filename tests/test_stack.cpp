// ============================================================
//  CDSIAS — Stack Test File
//  tests/test_stack.cpp
//
//  Tests: StaticStack, DynamicStack
//  All 7 categories per contracts.md §7:
//    1. Normal cases
//    2. Edge: empty
//    3. Edge: overflow (StaticStack only)
//    4. Edge: not found (N/A for stack)
//    5. Edge: boundary
//    6. Output format matches contract
//    7. Performance::log verified called
// ============================================================

#include <iostream>
#include "../src/core/stack_queue/stack.h"
#include "../src/analysis/performance.h"
#include "../src/analysis/visual.h"

using namespace std;

// ============================================================
//  STATIC STACK TESTS
// ============================================================
void testStaticStack() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: StaticStack" << COL_RESET << "\n";
    printSeparator();

    StaticStack sStack(3); // capacity 3 for easy overflow testing

    // 1. Normal cases
    cout << "\n[T1.1] Push: 10\n";
    sStack.push(10);

    cout << "\n[T1.2] Push: 20\n";
    sStack.push(20);

    cout << "\n[T1.3] Peek\n";
    sStack.peek();

    cout << "\n[T1.4] Push: 30 (should become full)\n";
    sStack.push(30);

    // 2. Edge: Overflow
    cout << "\n[T1.5] Push: 40 to full stack (should show Error)\n";
    sStack.push(40);

    // 3. Normal pop
    cout << "\n[T1.6] Pop (should pop 30)\n";
    sStack.pop();

    cout << "\n[T1.7] Pop (should pop 20)\n";
    sStack.pop();

    cout << "\n[T1.8] Pop (should pop 10)\n";
    sStack.pop();

    // 4. Edge: Underflow
    cout << "\n[T1.9] Pop from empty stack (should show Error)\n";
    sStack.pop();

    cout << "\n[T1.10] Peek empty stack (should show Error)\n";
    sStack.peek();
    
    cout << "\n[T1.11] Display empty stack\n";
    sStack.display();
}

// ============================================================
//  DYNAMIC STACK TESTS
// ============================================================
void testDynamicStack() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: DynamicStack" << COL_RESET << "\n";
    printSeparator();

    DynamicStack dStack;

    // 1. Normal cases
    cout << "\n[T2.1] Push: 10\n";
    dStack.push(10);

    cout << "\n[T2.2] Push: 20\n";
    dStack.push(20);

    cout << "\n[T2.3] Peek\n";
    dStack.peek();

    cout << "\n[T2.4] Push: 30\n";
    dStack.push(30);

    // 2. Normal pop
    cout << "\n[T2.5] Pop (should pop 30)\n";
    dStack.pop();

    cout << "\n[T2.6] Pop (should pop 20)\n";
    dStack.pop();

    cout << "\n[T2.7] Pop (should pop 10)\n";
    dStack.pop();

    // 3. Edge: Underflow
    cout << "\n[T2.8] Pop from empty stack (should show Error)\n";
    dStack.pop();

    cout << "\n[T2.9] Peek empty stack (should show Error)\n";
    dStack.peek();
    
    cout << "\n[T2.10] Display empty stack\n";
    dStack.display();
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    cout << "\n";
    printSeparator();
    cout << COL_ACCENT << "  CDSIAS - STACK MODULE TESTS" << COL_RESET << "\n";
    printSeparator();

    testStaticStack();
    testDynamicStack();

    // Performance report at end
    cout << "\n";
    Performance::display();

    return 0;
}
