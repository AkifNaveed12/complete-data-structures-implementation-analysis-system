#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "performance.h"

using namespace std;

// ============================================================
//  CDSIAS Performance Layer — performance.cpp
//  contracts.md §2.1–2.4
// ============================================================

// Static storage init
vector<Record> Performance::logs;

// --------------------------------------------------------
// assignComplexity
// Maps "Module::Operation" → Big-O label (contracts.md §2.4)
// --------------------------------------------------------
string Performance::assignComplexity(const string& module, const string& operation) {
    string key = module + "::" + operation;

    if (key == "Array::InsertEnd")          return "O(1)";
    if (key == "Array::InsertAtIndex")      return "O(n)";
    if (key == "Array::DeleteAtIndex")      return "O(n)";
    if (key == "Array::Search")             return "O(n)";

    if (key == "LinkedList::InsertStart")   return "O(1)";
    if (key == "LinkedList::InsertEnd")     return "O(n)";
    if (key == "LinkedList::Delete")        return "O(n)";
    if (key == "LinkedList::Search")        return "O(n)";

    if (key == "DoublyLL::InsertStart")     return "O(1)";
    if (key == "DoublyLL::InsertEnd")       return "O(n)";
    if (key == "DoublyLL::Delete")          return "O(n)";
    if (key == "DoublyLL::Search")          return "O(n)";

    if (key == "CircularLL::InsertStart")   return "O(1)";
    if (key == "CircularLL::InsertEnd")     return "O(n)";
    if (key == "CircularLL::Delete")        return "O(n)";

    if (key == "Stack::Push")               return "O(1)";
    if (key == "Stack::Pop")                return "O(1)";
    if (key == "Stack::Peek")               return "O(1)";

    if (key == "Queue::Enqueue")            return "O(1)";
    if (key == "Queue::Dequeue")            return "O(1)";

    if (key == "BST::Insert")              return "O(log n) avg";
    if (key == "BST::Search")             return "O(log n) avg";
    if (key == "BST::Delete")             return "O(log n) avg";

    if (key == "AVL::Insert")             return "O(log n)";

    if (key == "Heap::Insert")            return "O(log n)";
    if (key == "Heap::ExtractMin")        return "O(log n)";
    if (key == "Heap::ExtractMax")        return "O(log n)";

    if (key == "Graph::BFS")             return "O(V+E)";
    if (key == "Graph::DFS")             return "O(V+E)";
    if (key == "Graph::Dijkstra")        return "O(V²)";
    if (key == "Graph::Kruskal")         return "O(E log E)";
    if (key == "Graph::Prim")            return "O(V²)";

    if (key == "Search::Linear")         return "O(n)";
    if (key == "Search::Binary")         return "O(log n)";

    if (key == "Sort::Bubble")           return "O(n²)";
    if (key == "Sort::Selection")        return "O(n²)";
    if (key == "Sort::Insertion")        return "O(n²)";
    if (key == "Sort::Merge")            return "O(n log n)";
    if (key == "Sort::Quick")            return "O(n log n) avg";

    if (key == "Hash::InsertChaining")   return "O(1) avg";
    if (key == "Hash::InsertProbing")    return "O(1) avg";
    if (key == "Hash::Search")           return "O(1) avg";

    return "O(?)";  // unknown — should not happen
}

// --------------------------------------------------------
// log — record one operation (contracts.md §2.2)
// --------------------------------------------------------
void Performance::log(const string& module,
                      const string& operation,
                      int steps,
                      int comparisons)
{
    Record r;
    r.module      = module;
    r.operation   = operation;
    r.steps       = steps;
    r.comparisons = comparisons;
    r.complexity  = assignComplexity(module, operation);
    logs.push_back(r);
}

// --------------------------------------------------------
// display — formatted performance report (design.md §4.4)
// --------------------------------------------------------
void Performance::display() {
    cout << "\n";
    cout << "==============================\n";
    cout << "     PERFORMANCE REPORT\n";
    cout << "==============================\n";

    if (logs.empty()) {
        cout << "  No operations logged yet.\n";
        cout << "==============================\n";
        return;
    }

    // Header row
    cout << left
         << setw(16) << "Module"
         << setw(18) << "Operation"
         << setw(8)  << "Steps"
         << setw(13) << "Comparisons"
         << setw(18) << "Complexity"
         << "\n";

    cout << string(73, '-') << "\n";

    for (const Record& r : logs) {
        cout << left
             << setw(16) << r.module
             << setw(18) << r.operation
             << setw(8)  << r.steps
             << setw(13) << r.comparisons
             << setw(18) << r.complexity
             << "\n";
    }

    cout << "==============================\n";
    cout << "Total operations: " << logs.size() << "\n";
    cout << "==============================\n";
}

// --------------------------------------------------------
// clear — wipe all logs (used in tests)
// --------------------------------------------------------
void Performance::clear() {
    logs.clear();
}

// --------------------------------------------------------
// count — number of logs
// --------------------------------------------------------
int Performance::count() {
    return (int)logs.size();
}
// --------------------------------------------------------
// Expose logs for GUI
// --------------------------------------------------------
const vector<Record>& Performance::getLogs() {
    return logs;
}
