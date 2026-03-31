#include <iostream>
#include "performance.h"
using namespace std;

// Initialize static variable
vector<Record> Performance::logs;

void Performance::log(string operation, int steps) {
    logs.push_back({operation, steps});
}

void Performance::display() {
    cout << "\n========== PERFORMANCE REPORT ==========\n";

    if (logs.empty()) {
        cout << "[INFO] No operations recorded yet.\n";
        return;
    }

    for (int i = 0; i < logs.size(); i++) {
        cout << i + 1 << ". " << logs[i].operation
            << " | Steps: " << logs[i].steps << endl;
    }

    cout << "========================================\n";
}