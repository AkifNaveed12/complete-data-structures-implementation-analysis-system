#include <iostream>
#include <cassert>
#include "../src/core/stack_queue/stack.h"
#include "../src/core/stack_queue/queue.h"

extern int g_sqOperationCount;

int main() {
    std::cout << "========================================================\n";
    std::cout << " CDSIAS Operation Count Test (Traps 1, 2, 3, 4)\n";
    std::cout << "========================================================\n\n";

    g_sqOperationCount = 0;

    std::cout << "[INFO] Starting 500 pushes to DynamicStack...\n";
    DynamicStack stack;
    for (int i = 1; i <= 500; i++) {
        stack.push(i);
    }
    
    std::cout << "\n[INFO] Starting 300 pops from DynamicStack...\n";
    for (int i = 1; i <= 300; i++) {
        stack.pop();
    }

    std::cout << "\n[INFO] Starting 200 enqueues to SimpleQueue...\n";
    SimpleQueue queue(250);
    for (int i = 1; i <= 200; i++) {
        queue.enqueue(i);
    }

    std::cout << "\n========================================================\n";
    std::cout << " Expected Operation Count : 1000\n";
    std::cout << " Actual Operation Count   : " << g_sqOperationCount << "\n";
    std::cout << "========================================================\n\n";
    
    if (g_sqOperationCount != 1000) {
        std::cerr << "[ERROR] Trap 1 & 2 FAILED. Expected 1000 but got " << g_sqOperationCount << ".\n";
        return 1;
    }
    
    std::cout << "[INFO] Trap 1 & 2 PASSED.\n\n";

    std::cout << "[INFO] Testing Trap 3 (No increment on peek, display, or invalid ops)...\n";
    
    int oldCount = g_sqOperationCount;
    
    std::cout << "  -> Calling peek()...\n";
    stack.peek();
    queue.peek();
    
    std::cout << "  -> Calling display()...\n";
    stack.display();
    queue.display();
    
    std::cout << "  -> Triggering overflow/underflow (invalid ops)...\n";
    StaticStack emptyStack(5);
    emptyStack.pop(); // underflow
    
    for (int i=0; i<6; i++) {
        emptyStack.push(i); // last one is overflow
    }
    
    // We did 5 successful pushes, so count should increase by 5.
    int expectedFinalCount = oldCount + 5;
    
    std::cout << "\n========================================================\n";
    std::cout << " Expected Final Count : " << expectedFinalCount << "\n";
    std::cout << " Actual Final Count   : " << g_sqOperationCount << "\n";
    std::cout << "========================================================\n\n";

    if (g_sqOperationCount != expectedFinalCount) {
        std::cerr << "[ERROR] Trap 3 FAILED.\n";
        return 1;
    }
    
    std::cout << "[INFO] Trap 3 PASSED. Invalid operations and read-only operations correctly ignored.\n";
    std::cout << "[INFO] Trap 4 (GUI Visuals) is verified visually in the UI.\n";
    std::cout << "\nALL TRAPS PASSED EXCELLENTLY!\n";

    return 0;
}
