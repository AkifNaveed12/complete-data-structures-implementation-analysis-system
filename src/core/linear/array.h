#ifndef ARRAY_H
#define ARRAY_H

class Array {
private:
    int *arr;
    int size;
    int capacity;

public:
    Array(int cap);
    ~Array();

    void insertEnd(int value);
    void insertAt(int index, int value);
    void deleteAt(int index);
    int search(int value);
    void display();

    int getSize();
};

#endif