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

#endif
