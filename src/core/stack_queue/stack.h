#ifndef STACK_H
#define STACK_H

// ============================================================
//  CDSIAS — Stack Module Header
//  src/core/stack_queue/stack.h
//
//  Contains: StaticStack, DynamicStack
//  contracts.md §3.3, §5 (naming conventions)
// ============================================================

// -------------------------------------------------------
// STATIC STACK (Array-based)
// -------------------------------------------------------
class StaticStack {
private:
    int* arr;
    int  capacity;
    int  top;

public:
    StaticStack(int cap);
    ~StaticStack();

    void push(int value);
    void pop();
    void peek();
    void display();
    int  getSnapshot(int* out, int maxSize) const; // GUI: fills top-to-bottom
};

// -------------------------------------------------------
// DYNAMIC STACK (Linked-List based)
// -------------------------------------------------------

struct SNode {
    int    data;
    SNode* next;
    SNode(int val);
};

class DynamicStack {
private:
    SNode* topNode;
    int    size;

public:
    DynamicStack();
    ~DynamicStack();

    void push(int value);
    void pop();
    void peek();
    void display();
    int  getSnapshot(int* out, int maxSize) const; // GUI helper
};

#endif
