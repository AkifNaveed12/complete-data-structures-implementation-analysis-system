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
#include "analysis/performance.h"
#include "analysis/visual.h"

using namespace std;

// --------------------------------------------------------
// Forward declarations — module runners
// --------------------------------------------------------
void runArrayModule(Array& arr);
void runLinkedListModule(LinkedList& list);

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
    Array      arr(100);   // capacity 100, starts empty
    LinkedList list;       // starts empty

    int choice;

    do {
        clearScreen();
        printSeparator();
        cout << COL_ACCENT << "  CDSIAS — Data Structure Laboratory" << COL_RESET << "\n";
        cout << "  Comprehensive DS Implementation & Analysis\n";
        printSeparator();

        cout << "\n";
        cout << "  1. Linear Data Structures\n";
        cout << "  2. Stack & Queue           [Under Development]\n";
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
                    cout << "  3. Back\n";
                    cout << "\n  Enter choice: ";
                    cin >> subChoice;

                    if (subChoice == 1) runArrayModule(arr);
                    else if (subChoice == 2) runLinkedListModule(list);

                } while (subChoice != 3);
                break;
            }

            case 2:
            case 3:
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