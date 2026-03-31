#include <iostream>
#include "core/linear/array.h"
#include "core/linear/linked_list.h"
#include "analysis/performance.h"

using namespace std;

// Function declarations
void arrayMenu(Array &arr);
void linkedListMenu(LinkedList &list);

// Utility function for clean screen separation
void printHeader(string title) {
    cout << "\n=================================================\n";
    cout << "   " << title << endl;
    cout << "=================================================\n";
}

int main() {

    Array arr(100);
    LinkedList list;

    int choice;

    do {
        printHeader("DATA STRUCTURE IMPLEMENTATION SYSTEM");

        cout << "1. Linear Data Structures\n";
        cout << "2. Stack & Queue        [Under Development]\n";
        cout << "3. Trees                [Under Development]\n";
        cout << "4. Graph Algorithms     [Under Development]\n";
        cout << "5. Searching & Sorting  [Under Development]\n";
        cout << "6. Hashing              [Under Development]\n";
        cout << "7. Performance Reports  [Alpha Version* under testing]\n";
        cout << "8. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                int subChoice;
                do {
                    printHeader("LINEAR DATA STRUCTURES");

                    cout << "1. Array\n";
                    cout << "2. Linked List\n";
                    cout << "3. Back\n";

                    cout << "\nEnter choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1: arrayMenu(arr); break;
                        case 2: linkedListMenu(list); break;
                    }

                } while (subChoice != 3);
                break;
            }

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                cout << "\n[INFO] This module is under development.\n";
                break;
            case 7:
                Performance::display();
                break;

        }

    } while (choice != 8);

    cout << "\n[EXIT] Thank you for using CDSIAS.\n";

    return 0;
}

//array menu implementation
void arrayMenu(Array &arr) {
    int choice;

    do {
        printHeader("ARRAY MODULE");

        cout << "1. Insert at End\n";
        cout << "2. Insert at Position\n";
        cout << "3. Delete at Position\n";
        cout << "4. Search Element\n";
        cout << "5. Display Array\n";
        cout << "6. Back\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                arr.insertEnd(val);
                break;
            }

            case 2: {
                int val, index;
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter value: ";
                cin >> val;
                arr.insertAt(index, val);
                break;
            }

            case 3: {
                int index;
                cout << "Enter index: ";
                cin >> index;
                arr.deleteAt(index);
                break;
            }

            case 4: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                arr.search(val);
                break;
            }

            case 5:
                arr.display();
                break;
        }

    } while (choice != 6);
}

//linked list menu implementation
void linkedListMenu(LinkedList &list) {
    int choice;

    do {
        printHeader("LINKED LIST MODULE");

        cout << "1. Insert at Start\n";
        cout << "2. Insert at End\n";
        cout << "3. Delete by Value\n";
        cout << "4. Search\n";
        cout << "5. Display\n";
        cout << "6. Back\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                list.insertAtStart(val);
                break;
            }

            case 2: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                list.insertAtEnd(val);
                break;
            }

            case 3: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                list.deleteValue(val);
                break;
            }

            case 4: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                list.search(val);
                break;
            }

            case 5:
                list.display();
                break;
        }

    } while (choice != 6);
}