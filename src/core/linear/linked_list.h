#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Node {
public:
    int data;
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
};

#endif