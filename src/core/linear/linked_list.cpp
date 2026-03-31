#include <iostream>
#include "linked_list.h"
#include "../../analysis/performance.h"
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
    Node* n1 = new Node(10);
    Node* n2 = new Node(20);
    Node* n3 = new Node(30);

    head = n1;
    n1->next = n2;
    n2->next = n3;
}

// Insert at start
void LinkedList::insertAtStart(int value) {
    Node* newNode = new Node(value);

    newNode->next = head;
    head = newNode;

    cout << "[SUCCESS] Inserted at start.\n";
    Performance::log("LinkedList Insert", 1);
}

// Insert at end
void LinkedList::insertAtEnd(int value) {
    Node* newNode = new Node(value);

    int steps = 0;

    if (head == nullptr) {
        head = newNode;
        Performance::log("LinkedList Insert", 1);
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr) {
        temp = temp->next;
        steps++;
    }

    temp->next = newNode;

    cout << "[SUCCESS] Inserted at end.\n";
    Performance::log("LinkedList Insert", steps + 1);
}

// Delete by value
void LinkedList::deleteValue(int value) {
    if (head == nullptr) {
        cout << "[ERROR] List is empty!\n";
        Performance::log("LinkedList Delete", 1);
        return;
    }

    int steps = 0;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;

        cout << "[SUCCESS] Deleted.\n";
        Performance::log("LinkedList Delete", 1);
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
        steps++;
    }

    if (temp->next == nullptr) {
        cout << "[NOT FOUND]\n";
        Performance::log("LinkedList Delete", steps);
        return;
    }

    Node* delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;

    cout << "[SUCCESS] Deleted.\n";
    Performance::log("LinkedList Delete", steps + 1);
}

// Search
void LinkedList::search(int value) {
    Node* temp = head;
    int pos = 0;

    while (temp != nullptr) {
        if (temp->data == value) {
            cout << "[FOUND] At position: " << pos << endl;
            Performance::log("LinkedList Search", pos + 1);
            return;
        }
        temp = temp->next;
        pos++;
    }

    cout << "[NOT FOUND]\n";
    Performance::log("LinkedList Search", pos + 1);
}

// Display
void LinkedList::display() {
    if (head == nullptr) {
        cout << "[EMPTY]\n";
        Performance::log("LinkedList Display", 1);
        return;
    }

    Node* temp = head;
    int steps = 0;


    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
        steps++;
    }
    cout << "]\n";
    Performance::log("LinkedList Display", steps);
}