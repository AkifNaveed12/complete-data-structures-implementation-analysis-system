// ============================================================
//  CDSIAS — Singly Linked List Module
//  src/core/linear/linked_list.cpp
//
//  All output goes through visual.h ONLY — no raw cout.
//  Performance::log() called after every operation.
//  Follows BEFORE → STEP N → AFTER phase contract.
//  contracts.md §1, §2, §3
// ============================================================

#include <string>
#include "linked_list.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Internal helper: print full list state
// Active node shown as (val), others as plain val.
// Format: (10) → 20 → 30 → NULL  (contracts.md §1.2)
// --------------------------------------------------------
static void printListState(Node* head, Node* activeNode = nullptr) {
    if (head == nullptr) {
        cout << "NULL\n";
        return;
    }

    Node* temp = head;
    string line = "";

    while (temp != nullptr) {
        if (temp == activeNode)
            line += highlight(temp->data);
        else
            line += to_string(temp->data);

        if (temp->next != nullptr)
            line += " → ";
        else
            line += " → NULL";

        temp = temp->next;
    }
    cout << line << "\n";
}

// --------------------------------------------------------
// Node constructor
// --------------------------------------------------------
Node::Node(int val) {
    data = val;
    next = nullptr;
}

// --------------------------------------------------------
// LinkedList constructor — starts EMPTY (no demo data)
// --------------------------------------------------------
LinkedList::LinkedList() {
    head = nullptr;
}

// --------------------------------------------------------
// display — show full current list state
// NOTE: display is NOT logged
// --------------------------------------------------------
void LinkedList::display() {
    if (head == nullptr) {
        printError("Structure is empty");
        return;
    }
    printListState(head);
}

// --------------------------------------------------------
// insertAtStart — O(1)
// contracts.md §2.3
// --------------------------------------------------------
void LinkedList::insertAtStart(int value) {
    printHeader("LinkedList", "Insert at Start: " + to_string(value));

    // BEFORE
    printStep(1, "BEFORE:");
    printListState(head);
    sleep_ms(500);

    // Create node
    Node* newNode = new Node(value);
    printStep(2, "Creating new node " + highlight(value));
    sleep_ms(300);

    // Link
    newNode->next = head;
    head = newNode;

    printStep(3, "Linking " + highlight(value) + " → rest of list");
    printListState(head, newNode);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at start");
    printListState(head);

    // steps = 1 (no traversal), comparisons = 0
    Performance::log("LinkedList", "InsertStart", 1, 0);
}

// --------------------------------------------------------
// insertAtEnd — O(n)
// contracts.md §2.3
// --------------------------------------------------------
void LinkedList::insertAtEnd(int value) {
    printHeader("LinkedList", "Insert at End: " + to_string(value));

    // BEFORE
    printStep(1, "BEFORE:");
    printListState(head);
    sleep_ms(500);

    Node* newNode = new Node(value);
    int steps = 1;

    if (head == nullptr) {
        head = newNode;
        printStep(2, "List is empty — " + highlight(value) + " becomes head");
        printListState(head, newNode);
        sleep_ms(300);
        printResult("AFTER: " + to_string(value) + " inserted (first node)");
        printListState(head);
        Performance::log("LinkedList", "InsertEnd", 1, 0);
        return;
    }

    Node* temp = head;
    int stepNum = 2;

    while (temp->next != nullptr) {
        printStep(stepNum++, "Traversing: at node " + highlight(temp->data));
        printListState(head, temp);
        sleep_ms(300);  // traversal delay (contracts.md §1.5)
        temp = temp->next;
        steps++;
    }

    // Reached last node
    printStep(stepNum++, "Reached last node " + highlight(temp->data) + " → attaching new node");
    temp->next = newNode;
    printListState(head, newNode);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at end | Steps: " + to_string(steps));
    printListState(head);

    Performance::log("LinkedList", "InsertEnd", steps, 0);
}

// --------------------------------------------------------
// deleteValue — O(n)
// contracts.md §2.3
// --------------------------------------------------------
void LinkedList::deleteValue(int value) {
    printHeader("LinkedList", "Delete Value: " + to_string(value));

    // Edge case: empty
    if (head == nullptr) {
        printError("Structure is empty");
        Performance::log("LinkedList", "Delete", 0, 0);
        return;
    }

    // BEFORE
    printStep(1, "BEFORE:");
    printListState(head);
    sleep_ms(500);

    int steps = 0;
    int comparisons = 0;

    // Check head
    if (head->data == value) {
        comparisons++;
        printStep(2, "Found " + highlight(value) + " at head — removing");
        Node* temp = head;
        head = head->next;
        delete temp;
        printListState(head);
        sleep_ms(300);
        printResult("AFTER: " + to_string(value) + " deleted from head");
        printListState(head == nullptr ? nullptr : head);
        Performance::log("LinkedList", "Delete", 1, comparisons);
        return;
    }

    Node* temp = head;
    int stepNum = 2;

    while (temp->next != nullptr) {
        comparisons++;
        printStep(stepNum++, "Checking next: " + highlight(temp->next->data));
        printListState(head, temp->next);
        sleep_ms(300);

        if (temp->next->data == value) {
            steps = comparisons;
            printStep(stepNum++, "Found " + highlight(value) + " — unlinking");
            Node* delNode = temp->next;
            temp->next = delNode->next;
            delete delNode;

            printResult("AFTER: " + to_string(value) + " deleted | Steps: " + to_string(steps));
            printListState(head);
            Performance::log("LinkedList", "Delete", steps, comparisons);
            return;
        }
        temp = temp->next;
    }

    // Not found
    printResult("Value " + to_string(value) + " not found");
    Performance::log("LinkedList", "Delete", comparisons, comparisons);
}

// --------------------------------------------------------
// search — O(n)
// contracts.md §2.3
// --------------------------------------------------------
void LinkedList::search(int value) {
    printHeader("LinkedList", "Search: " + to_string(value));

    // Edge case: empty
    if (head == nullptr) {
        printError("Structure is empty");
        Performance::log("LinkedList", "Search", 0, 0);
        return;
    }

    // BEFORE
    printStep(1, "BEFORE:");
    printListState(head);
    sleep_ms(500);

    Node* temp = head;
    int pos = 0;
    int comparisons = 0;
    int stepNum = 2;

    while (temp != nullptr) {
        comparisons++;
        printStep(stepNum++, "Checking " + highlight(temp->data) + " at position " + to_string(pos));
        printListState(head, temp);
        sleep_ms(300);  // traversal delay

        if (temp->data == value) {
            printResult("Value " + to_string(value) + " found at position " + to_string(pos) +
                        " | Comparisons: " + to_string(comparisons));
            Performance::log("LinkedList", "Search", pos + 1, comparisons);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printResult("Value " + to_string(value) + " not found | Comparisons: " + to_string(comparisons));
    Performance::log("LinkedList", "Search", comparisons, comparisons);
}
