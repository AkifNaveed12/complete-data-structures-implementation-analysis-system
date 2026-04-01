#include <iostream>
#include <thread>
#include <chrono>
#include "linked_list.h"
#include "../../analysis/performance.h"
#include "../../analysis/visual.h"

using namespace std;

//helper functions for visual representation and delay
void printListVisual(Node* head, Node* highlight = nullptr) {
    Node* temp = head;

    cout << "[ ";
    while (temp != nullptr) {
        if (temp == highlight)
            cout << "(" << temp->data << ")";
        else
            cout << temp->data;

        if (temp->next != nullptr)
            cout << " -> ";

        temp = temp->next;
    }
    cout << " ]\n";
}
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
    cout << "\nBefore: ";
    display();

    Node* newNode = new Node(value);

    cout << "\nInserting at start...\n";
    sleep_ms(300);

    newNode->next = head;
    head = newNode;

    printListVisual(head, newNode);
    sleep_ms(400);

    cout << "[SUCCESS] Inserted at start.\n";

    cout << "After : ";
    display();

    Performance::log("LinkedList Insert", 1);
}
// Insert at end
void LinkedList::insertAtEnd(int value) {
    cout << "\nBefore: ";
    display();

    Node* newNode = new Node(value);

    int steps = 0;

    if (head == nullptr) {
        head = newNode;
        printListVisual(head, newNode);
        Performance::log("LinkedList Insert", 1);
        return;
    }

    Node* temp = head;

    cout << "\nTraversing...\n";

    while (temp->next != nullptr) {
        printListVisual(head, temp);
        sleep_ms(400);

        temp = temp->next;
        steps++;
    }

    temp->next = newNode;

    cout << "\nInserting at end...\n";
    printListVisual(head, newNode);
    sleep_ms(400);

    cout << "[SUCCESS] Inserted at end.\n";

    cout << "After : ";
    display();

    Performance::log("LinkedList Insert", steps + 1);
}

// Delete by value
void LinkedList::deleteValue(int value) {
    if (head == nullptr) {
        cout << "[ERROR] List is empty!\n";
        Performance::log("LinkedList Delete", 1);
        return;
    }

    cout << "\nBefore: ";
    display();

    int steps = 0;

    if (head->data == value) {
        cout << "\nDeleting head...\n";
        sleep_ms(300);

        Node* temp = head;
        head = head->next;
        delete temp;

        cout << "After : ";
        display();

        Performance::log("LinkedList Delete", 1);
        return;
    }

    Node* temp = head;

    cout << "\nTraversing...\n";

    while (temp->next != nullptr && temp->next->data != value) {
        printListVisual(head, temp);
        sleep_ms(400);

        temp = temp->next;
        steps++;
    }

    if (temp->next == nullptr) {
        cout << "[NOT FOUND]\n";
        Performance::log("LinkedList Delete", steps);
        return;
    }

    cout << "\nDeleting node...\n";
    sleep_ms(300);

    Node* delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;

    cout << "After : ";
    display();

    Performance::log("LinkedList Delete", steps + 1);
}

// Search
void LinkedList::search(int value) {
    Node* temp = head;
    int pos = 0;

    cout << "\nSearching...\n";

    while (temp != nullptr) {
        printListVisual(head, temp);
        sleep_ms(400);

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

    printListVisual(head);

    int steps = 0;
    Node* temp = head;
    while (temp != nullptr) {
        steps++;
        temp = temp->next;
    }

    Performance::log("LinkedList Display", steps);
}
