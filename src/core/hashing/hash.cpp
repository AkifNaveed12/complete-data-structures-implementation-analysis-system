#include "hash.h"

using namespace std;

// --- Hash Chaining ---

HashChaining::HashChaining() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

int HashChaining::hashFunction(int key) {
    return key % TABLE_SIZE;
}

void HashChaining::insert(int key) {
    printHeader("HashChaining", "Insert");
    printStep(1, "BEFORE: Starting insertion for key " + highlight(key));
    
    int index = hashFunction(key);
    int steps = 1;
    int comps = 0;
    
    printStep(2, "Hash function: " + to_string(key) + " % " + to_string(TABLE_SIZE) + " = " + highlight(index));
    sleep_ms(300);
    
    HashNode* newNode = new HashNode(key);
    
    if (table[index] == nullptr) {
        table[index] = newNode;
        printStep(3, "Slot [" + to_string(index) + "] is empty. Inserted directly.");
    } else {
        comps++;
        printStep(3, "Collision at [" + to_string(index) + "]! Adding to chain.");
        HashNode* temp = table[index];
        while (temp->next != nullptr) {
            steps++;
            comps++;
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    printResult("AFTER: Key " + highlight(key) + " inserted at index " + to_string(index));
    display();
    Performance::log("HashChaining", "Insert", steps, comps);
}

void HashChaining::display() {
    printSeparator();
    for (int i = 0; i < TABLE_SIZE; i++) {
        string row = "[" + to_string(i) + "]: ";
        HashNode* temp = table[i];
        while (temp != nullptr) {
            row += " -> " + to_string(temp->key);
            temp = temp->next;
        }
        printStep(0, row); // Custom output
    }
    printSeparator();
}

// --- Hash Linear Probing ---

HashLinearProbe::HashLinearProbe() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = -1; // -1 means empty
    }
}

int HashLinearProbe::hashFunction(int key) {
    return key % TABLE_SIZE;
}

void HashLinearProbe::insert(int key) {
    printHeader("HashLinearProbe", "Insert");
    printStep(1, "BEFORE: Starting insertion for key " + highlight(key));
    
    int index = hashFunction(key);
    int steps = 1;
    int comps = 0;
    
    printStep(2, "Hash function: " + to_string(key) + " % " + to_string(TABLE_SIZE) + " = " + highlight(index));
    sleep_ms(300);
    
    int originalIndex = index;
    int i = 0;
    
    while (table[(index + i) % TABLE_SIZE] != -1) {
        comps++;
        int probeIndex = (index + i) % TABLE_SIZE;
        printStep(steps + 2, "Slot [" + to_string(probeIndex) + "] occupied -> probing...");
        sleep_ms(300);
        i++;
        steps++;
        
        if (i == TABLE_SIZE) {
            printError("Hash table is full (capacity: " + to_string(TABLE_SIZE) + ")");
            Performance::log("HashLinearProbe", "Insert", steps, comps);
            return;
        }
    }
    
    int finalIndex = (index + i) % TABLE_SIZE;
    table[finalIndex] = key;
    
    printResult("AFTER: Key " + highlight(key) + " inserted at index " + to_string(finalIndex));
    display();
    Performance::log("HashLinearProbe", "Insert", steps, comps);
}

void HashLinearProbe::display() {
    printSeparator();
    for (int i = 0; i < TABLE_SIZE; i++) {
        string row = "[" + to_string(i) + "]: ";
        if (table[i] == -1) {
            row += " (empty)";
        } else {
            row += to_string(table[i]);
        }
        printStep(0, row);
    }
    printSeparator();
}
