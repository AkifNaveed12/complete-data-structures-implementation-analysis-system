#ifndef QUEUE_H
#define QUEUE_H

// ============================================================
//  CDSIAS — Queue Module Header
//  src/core/stack_queue/queue.h
//
//  Contains: SimpleQueue, CircularQueue, PriorityQueue, Deque
//  contracts.md §3.3, §5 (naming conventions)
// ============================================================

// -------------------------------------------------------
// SIMPLE QUEUE (Array-based)
// -------------------------------------------------------
class SimpleQueue {
private:
    int* arr;
    int  capacity;
    int  front;
    int  rear;

public:
    SimpleQueue(int cap);
    ~SimpleQueue();

    void enqueue(int value);
    void dequeue();
    void peek();
    void display();
};

// -------------------------------------------------------
// CIRCULAR QUEUE (Array-based)
// -------------------------------------------------------
class CircularQueue {
private:
    int* arr;
    int  capacity;
    int  front;
    int  rear;
    int  size;

public:
    CircularQueue(int cap);
    ~CircularQueue();

    void enqueue(int value);
    void dequeue();
    void peek();
    void display();
};

// -------------------------------------------------------
// PRIORITY QUEUE (Linked-List based)
// -------------------------------------------------------

struct PNode {
    int    data;
    int    priority; // higher number = higher priority, or lower number = higher priority? Let's assume higher number = higher priority.
    PNode* next;
    PNode(int val, int prio);
};

class PriorityQueue {
private:
    PNode* frontNode;
    int    size;

public:
    PriorityQueue();
    ~PriorityQueue();

    void enqueue(int value, int priority);
    void dequeue();
    void peek();
    void display();
};

#endif
