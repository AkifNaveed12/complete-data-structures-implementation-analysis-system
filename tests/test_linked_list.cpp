// ============================================================
//  CDSIAS — Linked List Test File
//  tests/test_linked_list.cpp
//
//  Tests: SinglyLinkedList, DoublyLinkedList, CircularLinkedList
//  All 7 categories per contracts.md §7:
//    1. Normal cases
//    2. Edge: empty
//    3. Edge: overflow (N/A for LL — dynamic)
//    4. Edge: not found
//    5. Edge: boundary (first/last)
//    6. Output format matches contract
//    7. Performance::log verified called
// ============================================================

#include <iostream>
#include "../src/core/linear/linked_list.h"
#include "../src/analysis/performance.h"
#include "../src/analysis/visual.h"

using namespace std;

// ============================================================
//  SINGLY LINKED LIST TESTS
// ============================================================
void testSinglyLinkedList() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: SinglyLinkedList" << COL_RESET << "\n";
    printSeparator();

    LinkedList list;

    // 1. Normal: insert and display
    cout << "\n[T1.1] Insert at Start: 10\n";
    list.insertAtStart(10);

    cout << "\n[T1.2] Insert at End: 20\n";
    list.insertAtEnd(20);

    cout << "\n[T1.3] Insert at Start: 5 (new head)\n";
    list.insertAtStart(5);

    cout << "\n[T1.4] Insert at End: 30\n";
    list.insertAtEnd(30);

    // 2. Edge: search found
    cout << "\n[T1.5] Search: 20 (should find at pos 2)\n";
    list.search(20);

    // 3. Edge: search not found
    cout << "\n[T1.6] Search: 99 (should NOT find)\n";
    list.search(99);

    // 4. Edge: delete head
    cout << "\n[T1.7] Delete: 5 (head node)\n";
    list.deleteValue(5);

    // 5. Edge: delete tail
    cout << "\n[T1.8] Delete: 30 (tail node)\n";
    list.deleteValue(30);

    // 6. Edge: delete middle
    cout << "\n[T1.9] Delete: 10 (middle)\n";
    list.deleteValue(10);

    // 7. Edge: delete from empty (after deleting all)
    cout << "\n[T1.10] Delete: 20 (last node)\n";
    list.deleteValue(20);
    cout << "\n[T1.11] Delete from empty list (should show Error)\n";
    list.deleteValue(5);

    cout << "\n[T1.12] Search empty list (should show Error)\n";
    list.search(1);

    cout << "\n[T1.13] Display empty list\n";
    list.display();
}

// ============================================================
//  DOUBLY LINKED LIST TESTS
// ============================================================
void testDoublyLinkedList() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: DoublyLinkedList" << COL_RESET << "\n";
    printSeparator();

    DoublyLinkedList dll;

    // 1. Normal inserts
    cout << "\n[T2.1] Insert at End: 10\n";
    dll.insertEnd(10);

    cout << "\n[T2.2] Insert at End: 20\n";
    dll.insertEnd(20);

    cout << "\n[T2.3] Insert at Start: 5 (new head)\n";
    dll.insertStart(5);

    cout << "\n[T2.4] Insert at End: 30 (new tail)\n";
    dll.insertEnd(30);

    // 2. Search
    cout << "\n[T2.5] Search: 20 (should find)\n";
    dll.search(20);

    cout << "\n[T2.6] Search: 99 (not found)\n";
    dll.search(99);

    // 3. Delete head
    cout << "\n[T2.7] Delete: 5 (head)\n";
    dll.deleteByValue(5);

    // 4. Delete tail
    cout << "\n[T2.8] Delete: 30 (tail)\n";
    dll.deleteByValue(30);

    // 5. Delete middle
    cout << "\n[T2.9] Delete: 10 (middle)\n";
    dll.deleteByValue(10);

    // 6. Edge: empty
    cout << "\n[T2.10] Delete last: 20\n";
    dll.deleteByValue(20);

    cout << "\n[T2.11] Delete from empty (should Error)\n";
    dll.deleteByValue(1);

    cout << "\n[T2.12] Search empty (should Error)\n";
    dll.search(1);
}

// ============================================================
//  CIRCULAR LINKED LIST TESTS
// ============================================================
void testCircularLinkedList() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: CircularLinkedList" << COL_RESET << "\n";
    printSeparator();

    CircularLinkedList cll;

    // 1. Normal inserts
    cout << "\n[T3.1] Insert at End: 10\n";
    cll.insertEnd(10);

    cout << "\n[T3.2] Insert at End: 20\n";
    cll.insertEnd(20);

    cout << "\n[T3.3] Insert at Start: 5 (new head)\n";
    cll.insertStart(5);

    cout << "\n[T3.4] Insert at End: 30\n";
    cll.insertEnd(30);

    // 2. Search
    cout << "\n[T3.5] Search: 20 (should find)\n";
    cll.search(20);

    cout << "\n[T3.6] Search: 99 (not found)\n";
    cll.search(99);

    // 3. Delete
    cout << "\n[T3.7] Delete: 5 (head)\n";
    cll.deleteByValue(5);

    cout << "\n[T3.8] Delete: 30 (tail)\n";
    cll.deleteByValue(30);

    cout << "\n[T3.9] Delete: 10 (middle)\n";
    cll.deleteByValue(10);

    cout << "\n[T3.10] Delete last: 20\n";
    cll.deleteByValue(20);

    cout << "\n[T3.11] Delete from empty (should Error)\n";
    cll.deleteByValue(1);

    cout << "\n[T3.12] Search empty (should Error)\n";
    cll.search(1);
}

// ============================================================
//  MAIN — Performance report at end
// ============================================================
int main() {
    cout << "\n";
    printSeparator();
    cout << COL_ACCENT << "  CDSIAS — LINKED LIST MODULE TESTS" << COL_RESET << "\n";
    printSeparator();

    testSinglyLinkedList();
    testDoublyLinkedList();
    testCircularLinkedList();

    // Performance report at end
    cout << "\n";
    Performance::display();

    return 0;
}