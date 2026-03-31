#include <iostream>
#include "linked_list.h"
using namespace std;

// Node constructor
Node::Node(int val) {
    data = val;
    next = nullptr;
}

// LinkedList constructor
LinkedList::LinkedList() {
    head = nullptr;

    // Default demo data
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
}

// Insert at start
void LinkedList::insertAtStart(int value) {
    Node* newNode = new Node(value);

    newNode->next = head;
    head = newNode;

    cout << "[SUCCESS] Inserted at start.\n";
}

// Insert at end
void LinkedList::insertAtEnd(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;

    cout << "[SUCCESS] Inserted at end.\n";
}

// Delete by value
void LinkedList::deleteValue(int value) {
    if (head == nullptr) {
        cout << "[ERROR] List is empty!\n";
        return;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;

        cout << "[SUCCESS] Deleted.\n";
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "[NOT FOUND]\n";
        return;
    }

    Node* delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;

    cout << "[SUCCESS] Deleted.\n";
}

// Search
void LinkedList::search(int value) {
    Node* temp = head;
    int pos = 0;

    while (temp != nullptr) {
        if (temp->data == value) {
            cout << "[FOUND] At position: " << pos << endl;
            return;
        }
        temp = temp->next;
        pos++;
    }

    cout << "[NOT FOUND]\n";
}

// Display
void LinkedList::display() {
    if (head == nullptr) {
        cout << "[EMPTY]\n";
        return;
    }

    Node* temp = head;

    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "]\n";
}