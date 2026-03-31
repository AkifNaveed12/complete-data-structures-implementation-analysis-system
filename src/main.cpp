#include <iostream>
#include "core/linear/array.h"
using namespace std;

int main() {
    Array arr(100);

    int choice;

    do {
        cout << "\n===== ARRAY MENU =====\n";
        cout << "1. Insert at End\n";
        cout << "2. Insert at Position\n";
        cout << "3. Delete at Position\n";
        cout << "4. Search Element\n";
        cout << "5. Display Array\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int val;
            cout << "Enter value: ";
            cin >> val;
            arr.insertEnd(val);
        }
        else if (choice == 2) {
            int val, index;
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter value: ";
            cin >> val;
            arr.insertAt(index, val);
        }
        else if (choice == 3) {
            int index;
            cout << "Enter index to delete: ";
            cin >> index;
            arr.deleteAt(index);
        }
        else if (choice == 4) {
            int val;
            cout << "Enter value to search: ";
            cin >> val;
            arr.search(val);
        }
        else if (choice == 5) {
            arr.display();
        }

    } while (choice != 6);

    return 0;
}