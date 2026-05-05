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


// ============================================================
//  DOUBLY LINKED LIST — M1-T1 through M1-T3
//  Format: NULL ← (val) ↔ val ↔ val → NULL
//  contracts.md §1, §2.3
// ============================================================

// --------------------------------------------------------
// DNode constructor
// --------------------------------------------------------
DNode::DNode(int val) {
    data = val;
    prev = nullptr;
    next = nullptr;
}

// --------------------------------------------------------
// DoublyLinkedList constructor
// --------------------------------------------------------
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// --------------------------------------------------------
// DoublyLinkedList destructor — free all nodes
// --------------------------------------------------------
DoublyLinkedList::~DoublyLinkedList() {
    DNode* cur = head;
    while (cur != nullptr) {
        DNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}

// --------------------------------------------------------
// Internal helper: print full doubly list state
// Format: NULL ← (val) ↔ val ↔ val → NULL
// --------------------------------------------------------
static void printDListState(DNode* head, DNode* activeNode = nullptr) {
    if (head == nullptr) {
        cout << "NULL\n";
        return;
    }

    string line = "NULL ← ";
    DNode* temp = head;

    while (temp != nullptr) {
        if (temp == activeNode)
            line += highlight(temp->data);
        else
            line += to_string(temp->data);

        if (temp->next != nullptr)
            line += " ↔ ";
        else
            line += " → NULL";

        temp = temp->next;
    }
    cout << line << "\n";
}

// --------------------------------------------------------
// DoublyLinkedList::display
// --------------------------------------------------------
void DoublyLinkedList::display() {
    if (head == nullptr) {
        printError("Structure is empty");
        return;
    }
    printDListState(head);
}

// --------------------------------------------------------
// DoublyLinkedList::insertStart — O(1)
// --------------------------------------------------------
void DoublyLinkedList::insertStart(int value) {
    printHeader("DoublyLL", "Insert at Start: " + to_string(value));

    printStep(1, "BEFORE:");
    printDListState(head);
    sleep_ms(500);

    DNode* newNode = new DNode(value);
    printStep(2, "Creating new node " + highlight(value));
    sleep_ms(300);

    if (head == nullptr) {
        head = tail = newNode;
        printStep(3, "List was empty — " + highlight(value) + " is head and tail");
    } else {
        newNode->next = head;
        head->prev    = newNode;
        head          = newNode;
        printStep(3, "Linking " + highlight(value) + " ↔ " + to_string(head->next->data));
    }

    printDListState(head, newNode);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at start");
    printDListState(head);

    Performance::log("DoublyLL", "InsertStart", 1, 0);
}

// --------------------------------------------------------
// DoublyLinkedList::insertEnd — O(n)
// --------------------------------------------------------
void DoublyLinkedList::insertEnd(int value) {
    printHeader("DoublyLL", "Insert at End: " + to_string(value));

    printStep(1, "BEFORE:");
    printDListState(head);
    sleep_ms(500);

    DNode* newNode = new DNode(value);
    int steps = 1;

    if (head == nullptr) {
        head = tail = newNode;
        printStep(2, "List was empty — " + highlight(value) + " is head and tail");
        printDListState(head, newNode);
        sleep_ms(300);
        printResult("AFTER: " + to_string(value) + " inserted (first node)");
        printDListState(head);
        Performance::log("DoublyLL", "InsertEnd", 1, 0);
        return;
    }

    DNode* temp = head;
    int stepNum = 2;
    while (temp->next != nullptr) {
        printStep(stepNum++, "Traversing: at " + highlight(temp->data));
        printDListState(head, temp);
        sleep_ms(300);
        temp = temp->next;
        steps++;
    }

    temp->next    = newNode;
    newNode->prev = temp;
    tail          = newNode;

    printStep(stepNum++, "Attaching " + highlight(value) + " after " + to_string(temp->data));
    printDListState(head, newNode);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at end | Steps: " + to_string(steps));
    printDListState(head);

    Performance::log("DoublyLL", "InsertEnd", steps, 0);
}

// --------------------------------------------------------
// DoublyLinkedList::deleteByValue — O(n)
// --------------------------------------------------------
void DoublyLinkedList::deleteByValue(int value) {
    printHeader("DoublyLL", "Delete Value: " + to_string(value));

    if (head == nullptr) {
        printError("Structure is empty");
        Performance::log("DoublyLL", "Delete", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printDListState(head);
    sleep_ms(500);

    DNode* cur = head;
    int comparisons = 0;
    int stepNum = 2;

    while (cur != nullptr) {
        comparisons++;
        printStep(stepNum++, "Checking " + highlight(cur->data));
        printDListState(head, cur);
        sleep_ms(300);

        if (cur->data == value) {
            if (cur->prev) cur->prev->next = cur->next;
            else           head = cur->next;       // deleting head

            if (cur->next) cur->next->prev = cur->prev;
            else           tail = cur->prev;       // deleting tail

            delete cur;

            printResult("AFTER: " + to_string(value) + " deleted | Comparisons: " + to_string(comparisons));
            printDListState(head);
            Performance::log("DoublyLL", "Delete", comparisons, comparisons);
            return;
        }
        cur = cur->next;
    }

    printResult("Value " + to_string(value) + " not found | Comparisons: " + to_string(comparisons));
    Performance::log("DoublyLL", "Delete", comparisons, comparisons);
}

// --------------------------------------------------------
// DoublyLinkedList::search — O(n)
// --------------------------------------------------------
bool DoublyLinkedList::search(int value) {
    printHeader("DoublyLL", "Search: " + to_string(value));

    if (head == nullptr) {
        printError("Structure is empty");
        Performance::log("DoublyLL", "Search", 0, 0);
        return false;
    }

    printStep(1, "BEFORE:");
    printDListState(head);
    sleep_ms(500);

    DNode* cur = head;
    int pos = 0;
    int comparisons = 0;
    int stepNum = 2;

    while (cur != nullptr) {
        comparisons++;
        printStep(stepNum++, "Checking " + highlight(cur->data) + " at position " + to_string(pos));
        printDListState(head, cur);
        sleep_ms(300);

        if (cur->data == value) {
            printResult("Value " + to_string(value) + " found at position " + to_string(pos) +
                        " | Comparisons: " + to_string(comparisons));
            Performance::log("DoublyLL", "Search", pos + 1, comparisons);
            return true;
        }
        cur = cur->next;
        pos++;
    }

    printResult("Value " + to_string(value) + " not found | Comparisons: " + to_string(comparisons));
    Performance::log("DoublyLL", "Search", comparisons, comparisons);
    return false;
}


// ============================================================
//  CIRCULAR LINKED LIST — M1-T6
//  Format: (10) → 20 → 30 → [HEAD]
//  contracts.md §1, §2.3
// ============================================================

// --------------------------------------------------------
// CNode constructor
// --------------------------------------------------------
CNode::CNode(int val) {
    data = val;
    next = nullptr;
}

// --------------------------------------------------------
// CircularLinkedList constructor
// --------------------------------------------------------
CircularLinkedList::CircularLinkedList() {
    head = nullptr;
    size = 0;
}

// --------------------------------------------------------
// CircularLinkedList destructor
// --------------------------------------------------------
CircularLinkedList::~CircularLinkedList() {
    if (head == nullptr) return;
    CNode* cur = head;
    do {
        CNode* nxt = cur->next;
        delete cur;
        cur = nxt;
    } while (cur != head);
}

// --------------------------------------------------------
// Internal helper: print full circular list state
// Format: 10 → 20 → (30) → [HEAD]
// --------------------------------------------------------
static void printCListState(CNode* head, int size, CNode* activeNode = nullptr) {
    if (head == nullptr || size == 0) {
        cout << "[ empty ]\n";
        return;
    }

    string line = "";
    CNode* cur = head;
    for (int i = 0; i < size; i++) {
        if (cur == activeNode)
            line += highlight(cur->data);
        else
            line += to_string(cur->data);

        line += " → ";
        cur = cur->next;
    }
    line += "[HEAD]";
    cout << line << "\n";
}

// --------------------------------------------------------
// CircularLinkedList::display
// --------------------------------------------------------
void CircularLinkedList::display() {
    if (head == nullptr) {
        printError("Structure is empty");
        return;
    }
    printCListState(head, size);
}

// --------------------------------------------------------
// CircularLinkedList::insertStart — O(1)
// --------------------------------------------------------
void CircularLinkedList::insertStart(int value) {
    printHeader("CircularLL", "Insert at Start: " + to_string(value));

    printStep(1, "BEFORE:");
    printCListState(head, size);
    sleep_ms(500);

    CNode* newNode = new CNode(value);

    if (head == nullptr) {
        head = newNode;
        newNode->next = head;  // circular
        printStep(2, "List was empty — " + highlight(value) + " points to itself");
    } else {
        // Find tail (last node pointing to head)
        CNode* tail = head;
        for (int i = 0; i < size - 1; i++) tail = tail->next;

        newNode->next = head;
        tail->next    = newNode;
        head          = newNode;

        printStep(2, "Inserted " + highlight(value) + " as new head, tail → new head");
    }

    size++;
    printCListState(head, size, newNode);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at start");
    printCListState(head, size);

    Performance::log("CircularLL", "InsertStart", 1, 0);
}

// --------------------------------------------------------
// CircularLinkedList::insertEnd — O(n)
// --------------------------------------------------------
void CircularLinkedList::insertEnd(int value) {
    printHeader("CircularLL", "Insert at End: " + to_string(value));

    printStep(1, "BEFORE:");
    printCListState(head, size);
    sleep_ms(500);

    CNode* newNode = new CNode(value);
    int steps = 1;

    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        printStep(2, "List was empty — " + highlight(value) + " is head, points to itself");
        size++;
        printCListState(head, size, newNode);
        sleep_ms(300);
        printResult("AFTER: " + to_string(value) + " inserted (first node)");
        printCListState(head, size);
        Performance::log("CircularLL", "InsertEnd", 1, 0);
        return;
    }

    CNode* tail = head;
    int stepNum = 2;
    while (tail->next != head) {
        printStep(stepNum++, "Traversing: at " + highlight(tail->data));
        printCListState(head, size, tail);
        sleep_ms(300);
        tail = tail->next;
        steps++;
    }

    tail->next    = newNode;
    newNode->next = head;
    size++;

    printStep(stepNum++, "Attaching " + highlight(value) + " after " + to_string(tail->data) + " → [HEAD]");
    printCListState(head, size, newNode);
    sleep_ms(300);

    printResult("AFTER: " + to_string(value) + " inserted at end | Steps: " + to_string(steps));
    printCListState(head, size);

    Performance::log("CircularLL", "InsertEnd", steps, 0);
}

// --------------------------------------------------------
// CircularLinkedList::deleteByValue — O(n)
// --------------------------------------------------------
void CircularLinkedList::deleteByValue(int value) {
    printHeader("CircularLL", "Delete Value: " + to_string(value));

    if (head == nullptr) {
        printError("Structure is empty");
        Performance::log("CircularLL", "Delete", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printCListState(head, size);
    sleep_ms(500);

    int comparisons = 0;
    int stepNum = 2;

    // Find tail for re-linking
    CNode* tail = head;
    for (int i = 0; i < size - 1; i++) tail = tail->next;

    // Delete head case
    if (head->data == value) {
        comparisons++;
        printStep(stepNum++, "Found " + highlight(value) + " at head — removing");
        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            CNode* old = head;
            head = head->next;
            tail->next = head;
            delete old;
        }
        size--;
        printResult("AFTER: " + to_string(value) + " deleted | Comparisons: " + to_string(comparisons));
        printCListState(head, size);
        Performance::log("CircularLL", "Delete", comparisons, comparisons);
        return;
    }

    CNode* prev = head;
    CNode* cur  = head->next;

    for (int i = 1; i < size; i++) {
        comparisons++;
        printStep(stepNum++, "Checking " + highlight(cur->data));
        printCListState(head, size, cur);
        sleep_ms(300);

        if (cur->data == value) {
            prev->next = cur->next;
            if (cur == tail) tail = prev;
            delete cur;
            size--;
            printResult("AFTER: " + to_string(value) + " deleted | Comparisons: " + to_string(comparisons));
            printCListState(head, size);
            Performance::log("CircularLL", "Delete", comparisons, comparisons);
            return;
        }
        prev = cur;
        cur  = cur->next;
    }

    printResult("Value " + to_string(value) + " not found | Comparisons: " + to_string(comparisons));
    Performance::log("CircularLL", "Delete", comparisons, comparisons);
}

// --------------------------------------------------------
// CircularLinkedList::search — O(n)
// --------------------------------------------------------
bool CircularLinkedList::search(int value) {
    printHeader("CircularLL", "Search: " + to_string(value));

    if (head == nullptr) {
        printError("Structure is empty");
        Performance::log("CircularLL", "Search", 0, 0);
        return false;
    }

    printStep(1, "BEFORE:");
    printCListState(head, size);
    sleep_ms(500);

    CNode* cur = head;
    int comparisons = 0;
    int stepNum = 2;

    for (int i = 0; i < size; i++) {
        comparisons++;
        printStep(stepNum++, "Checking " + highlight(cur->data) + " at position " + to_string(i));
        printCListState(head, size, cur);
        sleep_ms(300);

        if (cur->data == value) {
            printResult("Value " + to_string(value) + " found at position " + to_string(i) +
                        " | Comparisons: " + to_string(comparisons));
            Performance::log("CircularLL", "Search", i + 1, comparisons);
            return true;
        }
        cur = cur->next;
    }

    printResult("Value " + to_string(value) + " not found | Comparisons: " + to_string(comparisons));
    Performance::log("CircularLL", "Search", comparisons, comparisons);
    return false;
}

