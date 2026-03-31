#include <iostream>
#include "../src/core/linear/linked_list.h"
using namespace std;

int main() {
    LinkedList list;

    cout << "===== LINKED LIST TEST =====\n";

    list.display();

    cout << "\n--- Insert Start ---\n";
    list.insertAtStart(5);
    list.display();

    cout << "\n--- Insert End ---\n";
    list.insertAtEnd(40);
    list.display();

    cout << "\n--- Search ---\n";
    list.search(20);

    cout << "\n--- Delete ---\n";
    list.deleteValue(20);
    list.display();

    return 0;
}