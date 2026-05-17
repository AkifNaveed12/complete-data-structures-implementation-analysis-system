#ifndef HEAP_H
#define HEAP_H

// ============================================================
//  CDSIAS — Heap Header (Min/Max)
//  src/core/trees/heap.h
// ============================================================

class Heap {
private:
    int* array;
    int capacity;
    int size;
    bool isMinHeap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void heapifyUp(int i, int& steps, int& comparisons);
    void heapifyDown(int i, int& steps, int& comparisons);
    
    void swap(int& x, int& y);

public:
    Heap(int cap, bool minHeap = true);
    ~Heap();

    void insert(int value);
    void extract();
    void display();
};

#endif
