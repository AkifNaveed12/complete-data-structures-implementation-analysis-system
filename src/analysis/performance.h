#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <string>
#include <vector>

using namespace std;

// ============================================================
//  CDSIAS Performance Layer — performance.h
//  Tracks every operation's steps, comparisons, and complexity.
//  contracts.md §2.1, §2.2, §2.3
// ============================================================

struct Record {
    string module;       // e.g. "Array", "LinkedList", "BST"
    string operation;    // e.g. "InsertAtIndex", "Search"
    int    steps;        // number of steps executed
    int    comparisons;  // number of comparisons made
    string complexity;   // auto-assigned Big-O label
};

class Performance {
private:
    static vector<Record> logs;

    // Auto-assign complexity label from module::operation key
    // contracts.md §2.4
    static string assignComplexity(const string& module, const string& operation);

public:
    // Log an operation (contracts.md §2.2)
    static void log(const string& module,
                    const string& operation,
                    int steps,
                    int comparisons);

    // Display formatted performance report (design.md §4.4)
    static void display();

    // Clear all logs (for testing)
    static void clear();

    // Total operations logged
    static int count();
};

#endif