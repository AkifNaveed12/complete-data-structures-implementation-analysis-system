#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// ============================================================
//  CDSIAS — Linked List Module Header
//  src/core/linear/linked_list.h
//
//  Contains: SinglyLinkedList, DoublyLinkedList, CircularLinkedList
//  contracts.md §3.3, §5 (naming conventions)
// ============================================================

// -------------------------------------------------------
// SINGLY LINKED LIST
// -------------------------------------------------------

struct Node {
    int   data;
    Node* next;
    Node(int val);
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList();

    void insertAtStart(int value);
    void insertAtEnd(int value);
    void deleteValue(int value);
    void search(int value);
    void display();
    int  getSnapshot(int* out, int maxSize) const; // GUI helper
};

// -------------------------------------------------------
// DOUBLY LINKED LIST
// contracts.md §5: class DoublyLinkedList, struct DNode
// -------------------------------------------------------

struct DNode {
    int    data;
    DNode* prev;
    DNode* next;
    DNode(int val);
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertStart(int value);
    void insertEnd(int value);
    void deleteByValue(int value);
    bool search(int value);
    void display();
    int  getSnapshot(int* out, int maxSize) const; // GUI helper
};
// contracts.md §5: class CircularLinkedList
// -------------------------------------------------------

struct CNode {
    int    data;
    CNode* next;
    CNode(int val);
};

class CircularLinkedList {
private:
    CNode* head;
    int    size;
public:
    CircularLinkedList();
    ~CircularLinkedList();

    void insertStart(int value);
    void insertEnd(int value);
    void deleteByValue(int value);
    bool search(int value);
    void display();
    int  getSnapshot(int* out, int maxSize) const; // GUI helper
};

#endif