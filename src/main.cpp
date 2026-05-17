// ============================================================
//  CDSIAS — Control Layer
//  src/main.cpp
//
//  Menu-driven navigation ONLY.
//  No business logic here — only routing to modules.
//  All visual output through visual.h.
//  contracts.md §3.1, §10 (Architecture Boundary)
// ============================================================

#include <iostream>
#include <cstdlib>
#include "core/linear/array.h"
#include "core/linear/linked_list.h"
#include "core/stack_queue/stack.h"
#include "core/stack_queue/queue.h"
#include "core/trees/bt.h"
#include "core/trees/bst.h"
#include "core/trees/avl.h"
#include "analysis/performance.h"
#include "analysis/visual.h"

using namespace std;

// --------------------------------------------------------
// Forward declarations — module runners
// --------------------------------------------------------
void runArrayModule(Array& arr);
void runLinkedListModule(LinkedList& list);
void runDoublyLLModule(DoublyLinkedList& dll);
void runCircularLLModule(CircularLinkedList& cll);
void runStaticStackModule(StaticStack& stack);
void runDynamicStackModule(DynamicStack& stack);
void runSimpleQueueModule(SimpleQueue& queue);
void runCircularQueueModule(CircularQueue& queue);
void runPriorityQueueModule(PriorityQueue& queue);
void runDequeModule(Deque& queue);
void runBTModule(BinaryTree& tree);
void runBSTModule(BinarySearchTree& tree);
void runAVLModule(AVLTree& tree);

// --------------------------------------------------------
// Utility
// --------------------------------------------------------
void clearScreen() {
    system("cls");
}

// --------------------------------------------------------
// Main entry point
// --------------------------------------------------------
int main() {
    Array              arr(100);
    LinkedList         list;
    DoublyLinkedList   dll;
    CircularLinkedList cll;
    StaticStack        sStack(100);
    DynamicStack       dStack;
    SimpleQueue        sQueue(100);
    CircularQueue      cQueue(100);
    PriorityQueue      pQueue;
    Deque              dq;
    BinaryTree         bt;
    BinarySearchTree   bst;
    AVLTree            avl;

    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  CDSIAS — Data Structure Laboratory" << COL_RESET << "\n";
        cout << "  Comprehensive DS Implementation & Analysis\n";
        printSeparator();

        cout << "\n";
        cout << "  1. Linear Data Structures\n";
        cout << "  2. Stack & Queue\n";
        cout << "  3. Trees                   [Under Development]\n";
        cout << "  4. Graph Algorithms        [Under Development]\n";
        cout << "  5. Searching & Sorting     [Under Development]\n";
        cout << "  6. Hashing                 [Under Development]\n";
        cout << "  7. Performance Report\n";
        cout << "  8. Exit\n";
        cout << "\n";
        cout << "  Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                int subChoice;
                do {
                    clearScreen();
                    printSeparator();
                    cout << COL_ACCENT << "  LINEAR DATA STRUCTURES" << COL_RESET << "\n";
                    printSeparator();
                    cout << "\n";
                    cout << "  1. Array (Singly)\n";
                    cout << "  2. Singly Linked List\n";
                    cout << "  3. Doubly Linked List\n";
                    cout << "  4. Circular Linked List\n";
                    cout << "  5. Back\n";
                    cout << "\n  Enter choice: ";
                    cin >> subChoice;

                    if (subChoice == 1) runArrayModule(arr);
                    else if (subChoice == 2) runLinkedListModule(list);
                    else if (subChoice == 3) runDoublyLLModule(dll);
                    else if (subChoice == 4) runCircularLLModule(cll);

                } while (subChoice != 5);
                break;
            }

            case 2: {
                int subChoice;
                do {
                    clearScreen();
                    printSeparator();
                    cout << COL_ACCENT << "  STACK & QUEUE" << COL_RESET << "\n";
                    printSeparator();
                    cout << "\n";
                    cout << "  1. Static Stack (Array-based)\n";
                    cout << "  2. Dynamic Stack (Linked List-based)\n";
                    cout << "  3. Queue Variants\n";
                    cout << "  4. Back\n";
                    cout << "\n  Enter choice: ";
                    cin >> subChoice;

                    if (subChoice == 1) runStaticStackModule(sStack);
                    else if (subChoice == 2) runDynamicStackModule(dStack);
                    else if (subChoice == 3) {
                        int qChoice;
                        do {
                            clearScreen();
                            printSeparator();
                            cout << COL_ACCENT << "  QUEUE VARIANTS" << COL_RESET << "\n";
                            printSeparator();
                            cout << "\n";
                            cout << "  1. Simple Queue (Array-based)\n";
                            cout << "  2. Circular Queue (Array-based)\n";
                            cout << "  3. Priority Queue (Linked List-based)\n";
                            cout << "  4. Deque (Doubly Linked List-based)\n";
                            cout << "  5. Back\n";
                            cout << "\n  Enter choice: ";
                            cin >> qChoice;

                            if (qChoice == 1) runSimpleQueueModule(sQueue);
                            else if (qChoice == 2) runCircularQueueModule(cQueue);
                            else if (qChoice == 3) runPriorityQueueModule(pQueue);
                            else if (qChoice == 4) runDequeModule(dq);

                        } while (qChoice != 5);
                    }

                } while (subChoice != 4);
                break;
            }

            case 3: {
                int subChoice;
                do {
                    clearScreen();
                    printSeparator();
                    cout << COL_ACCENT << "  TREES" << COL_RESET << "\n";
                    printSeparator();
                    cout << "\n";
                    cout << "  1. Binary Tree\n";
                    cout << "  2. Binary Search Tree (BST)\n";
                    cout << "  3. AVL Tree\n";
                    cout << "  4. Heap (Min/Max) [Under Development]\n";
                    cout << "  5. Back\n";
                    cout << "\n  Enter choice: ";
                    cin >> subChoice;

                    if (subChoice == 1) runBTModule(bt);
                    else if (subChoice == 2) runBSTModule(bst);
                    else if (subChoice == 3) runAVLModule(avl);

                } while (subChoice != 5);
                break;
            }

            case 4:
            case 5:
            case 6:
                cout << "\n";
                printError("Module under development");
                cout << "\n  Press Enter to continue...\n";
                cin.ignore();
                cin.get();
                break;

            case 7:
                Performance::display();
                cout << "\n  Press Enter to continue...\n";
                cin.ignore();
                cin.get();
                break;

            case 8:
                break;

            default:
                printError("Invalid choice — enter 1 to 8");
                break;
        }

    } while (choice != 8);

    printSeparator();
    cout << COL_SUCCESS << "  Thank you for using CDSIAS." << COL_RESET << "\n";
    printSeparator();

    return 0;
}

// ============================================================
//  ARRAY MODULE RUNNER
// ============================================================
void runArrayModule(Array& arr) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  ARRAY MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state: ";
        arr.display();
        cout << "\n";

        cout << "  1. Insert at End\n";
        cout << "  2. Insert at Index\n";
        cout << "  3. Delete at Index\n";
        cout << "  4. Search\n";
        cout << "  5. Display\n";
        cout << "  6. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                int val;
                cout << "  Value: ";
                cin >> val;
                arr.insertEnd(val);
                break;
            }

            case 2: {
                int val, idx;
                cout << "  Index: ";
                cin >> idx;
                cout << "  Value: ";
                cin >> val;
                arr.insertAt(idx, val);
                break;
            }

            case 3: {
                int idx;
                cout << "  Index: ";
                cin >> idx;
                arr.deleteAt(idx);
                break;
            }

            case 4: {
                int val;
                cout << "  Value to search: ";
                cin >> val;
                arr.search(val);
                break;
            }

            case 5:
                cout << "\n";
                arr.display();
                break;
        }

        if (choice >= 1 && choice <= 5) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);
}

// ============================================================
//  LINKED LIST MODULE RUNNER
// ============================================================
void runLinkedListModule(LinkedList& list) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  SINGLY LINKED LIST MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state: ";
        list.display();
        cout << "\n";

        cout << "  1. Insert at Start\n";
        cout << "  2. Insert at End\n";
        cout << "  3. Delete by Value\n";
        cout << "  4. Search\n";
        cout << "  5. Display\n";
        cout << "  6. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                int val;
                cout << "  Value: ";
                cin >> val;
                list.insertAtStart(val);
                break;
            }

            case 2: {
                int val;
                cout << "  Value: ";
                cin >> val;
                list.insertAtEnd(val);
                break;
            }

            case 3: {
                int val;
                cout << "  Value to delete: ";
                cin >> val;
                list.deleteValue(val);
                break;
            }

            case 4: {
                int val;
                cout << "  Value to search: ";
                cin >> val;
                list.search(val);
                break;
            }

            case 5:
                cout << "\n";
                list.display();
                break;
        }

        if (choice >= 1 && choice <= 5) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);
}

// ============================================================
//  DOUBLY LINKED LIST MODULE RUNNER — M1-T4
// ============================================================
void runDoublyLLModule(DoublyLinkedList& dll) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  DOUBLY LINKED LIST MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state: ";
        dll.display();
        cout << "\n";

        cout << "  1. Insert at Start\n";
        cout << "  2. Insert at End\n";
        cout << "  3. Delete by Value\n";
        cout << "  4. Search\n";
        cout << "  5. Display\n";
        cout << "  6. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value: ";
                cin >> val;
                dll.insertStart(val);
                break;
            }
            case 2: {
                int val;
                cout << "  Value: ";
                cin >> val;
                dll.insertEnd(val);
                break;
            }
            case 3: {
                int val;
                cout << "  Value to delete: ";
                cin >> val;
                dll.deleteByValue(val);
                break;
            }
            case 4: {
                int val;
                cout << "  Value to search: ";
                cin >> val;
                dll.search(val);
                break;
            }
            case 5:
                cout << "\n";
                dll.display();
                break;
        }

        if (choice >= 1 && choice <= 5) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);
}

// ============================================================
//  CIRCULAR LINKED LIST MODULE RUNNER — M1-T6
// ============================================================
void runCircularLLModule(CircularLinkedList& cll) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  CIRCULAR LINKED LIST MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state: ";
        cll.display();
        cout << "\n";

        cout << "  1. Insert at Start\n";
        cout << "  2. Insert at End\n";
        cout << "  3. Delete by Value\n";
        cout << "  4. Search\n";
        cout << "  5. Display\n";
        cout << "  6. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value: ";
                cin >> val;
                cll.insertStart(val);
                break;
            }
            case 2: {
                int val;
                cout << "  Value: ";
                cin >> val;
                cll.insertEnd(val);
                break;
            }
            case 3: {
                int val;
                cout << "  Value to delete: ";
                cin >> val;
                cll.deleteByValue(val);
                break;
            }
            case 4: {
                int val;
                cout << "  Value to search: ";
                cin >> val;
                cll.search(val);
                break;
            }
            case 5:
                cout << "\n";
                cll.display();
                break;
        }

        if (choice >= 1 && choice <= 5) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);
}

// ============================================================
//  STATIC STACK MODULE RUNNER — M2-T0
// ============================================================
void runStaticStackModule(StaticStack& stack) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  STATIC STACK MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        stack.display();
        cout << "\n";

        cout << "  1. Push\n";
        cout << "  2. Pop\n";
        cout << "  3. Peek\n";
        cout << "  4. Display\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to push: ";
                cin >> val;
                stack.push(val);
                break;
            }
            case 2:
                stack.pop();
                break;
            case 3:
                stack.peek();
                break;
            case 4:
                cout << "\n";
                stack.display();
                break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);
}

// ============================================================
//  DYNAMIC STACK MODULE RUNNER — M2-T1
// ============================================================
void runDynamicStackModule(DynamicStack& stack) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  DYNAMIC STACK MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        stack.display();
        cout << "\n";

        cout << "  1. Push\n";
        cout << "  2. Pop\n";
        cout << "  3. Peek\n";
        cout << "  4. Display\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to push: ";
                cin >> val;
                stack.push(val);
                break;
            }
            case 2:
                stack.pop();
                break;
            case 3:
                stack.peek();
                break;
            case 4:
                cout << "\n";
                stack.display();
                break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);
}

// ============================================================
//  SIMPLE QUEUE MODULE RUNNER — M2-T2
// ============================================================
void runSimpleQueueModule(SimpleQueue& queue) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  SIMPLE QUEUE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        queue.display();
        cout << "\n";

        cout << "  1. Enqueue\n";
        cout << "  2. Dequeue\n";
        cout << "  3. Peek\n";
        cout << "  4. Display\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to enqueue: ";
                cin >> val;
                queue.enqueue(val);
                break;
            }
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.peek();
                break;
            case 4:
                cout << "\n";
                queue.display();
                break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);
}

// ============================================================
//  CIRCULAR QUEUE MODULE RUNNER — M2-T3
// ============================================================
void runCircularQueueModule(CircularQueue& queue) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  CIRCULAR QUEUE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        queue.display();
        cout << "\n";

        cout << "  1. Enqueue\n";
        cout << "  2. Dequeue\n";
        cout << "  3. Peek\n";
        cout << "  4. Display\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to enqueue: ";
                cin >> val;
                queue.enqueue(val);
                break;
            }
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.peek();
                break;
            case 4:
                cout << "\n";
                queue.display();
                break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);
}

// ============================================================
//  PRIORITY QUEUE MODULE RUNNER — M2-T4
// ============================================================
void runPriorityQueueModule(PriorityQueue& queue) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  PRIORITY QUEUE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        queue.display();
        cout << "\n";

        cout << "  1. Enqueue (Insert with Priority)\n";
        cout << "  2. Dequeue (Extract Max)\n";
        cout << "  3. Peek\n";
        cout << "  4. Display\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val, prio;
                cout << "  Value to enqueue: ";
                cin >> val;
                cout << "  Priority (higher number = higher priority): ";
                cin >> prio;
                queue.enqueue(val, prio);
                break;
            }
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.peek();
                break;
            case 4:
                cout << "\n";
                queue.display();
                break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);
}

// ============================================================
//  DEQUE MODULE RUNNER — M2-T5
// ============================================================
void runDequeModule(Deque& queue) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  DEQUE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        queue.display();
        cout << "\n";

        cout << "  1. Insert Front\n";
        cout << "  2. Insert Rear\n";
        cout << "  3. Delete Front\n";
        cout << "  4. Delete Rear\n";
        cout << "  5. Display\n";
        cout << "  6. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to insert at front: ";
                cin >> val;
                queue.insertFront(val);
                break;
            }
            case 2: {
                int val;
                cout << "  Value to insert at rear: ";
                cin >> val;
                queue.insertRear(val);
                break;
            }
            case 3:
                queue.deleteFront();
                break;
            case 4:
                queue.deleteRear();
                break;
            case 5:
                cout << "\n";
                queue.display();
                break;
        }

        if (choice >= 1 && choice <= 5) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);
}

// ============================================================
//  BINARY TREE MODULE RUNNER — M3-T0
// ============================================================
void runBTModule(BinaryTree& tree) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  BINARY TREE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        tree.display();
        cout << "\n";

        cout << "  1. Insert (Level-Order)\n";
        cout << "  2. In-order Traversal\n";
        cout << "  3. Pre-order Traversal\n";
        cout << "  4. Post-order Traversal\n";
        cout << "  5. Display Tree\n";
        cout << "  6. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            }
            case 2:
                tree.inorder();
                break;
            case 3:
                tree.preorder();
                break;
            case 4:
                tree.postorder();
                break;
            case 5:
                cout << "\n";
                tree.display();
                break;
        }

        if (choice >= 1 && choice <= 5) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);
}

// ============================================================
//  BINARY SEARCH TREE MODULE RUNNER — M3-T1
// ============================================================
void runBSTModule(BinarySearchTree& tree) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  BINARY SEARCH TREE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        tree.display();
        cout << "\n";

        cout << "  1. Insert Node\n";
        cout << "  2. Delete Node\n";
        cout << "  3. Search Node\n";
        cout << "  4. Display Tree\n";
        cout << "  5. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            }
            case 2: {
                int val;
                cout << "  Value to delete: ";
                cin >> val;
                tree.remove(val);
                break;
            }
            case 3: {
                int val;
                cout << "  Value to search: ";
                cin >> val;
                tree.search(val);
                break;
            }
            case 4:
                cout << "\n";
                tree.display();
                break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);
}

// ============================================================
//  AVL TREE MODULE RUNNER — M3-T2
// ============================================================
void runAVLModule(AVLTree& tree) {
    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  AVL TREE MODULE" << COL_RESET << "\n";
        printSeparator();

        cout << "\n  Current state:\n";
        tree.display();
        cout << "\n";

        cout << "  1. Insert Node (Auto-balance)\n";
        cout << "  2. Display Tree\n";
        cout << "  3. Back\n";
        cout << "\n  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            }
            case 2:
                cout << "\n";
                tree.display();
                break;
        }

        if (choice >= 1 && choice <= 2) {
            cout << "\n  Press Enter to continue...\n";
            cin.ignore();
            cin.get();
        }

    } while (choice != 3);
}


