# CDSIAS — System Contracts Document

## contracts.md

> This document defines every contract in the system. A contract is a binding rule between two parts of the system. Breaking any contract = breaking the system. These rules do not change.

---

## 1. VISUAL OUTPUT CONTRACT

### 1.1 The One Law of Output

> **Every single output in every module goes through `visual.h` functions. Zero exceptions. No raw `cout` in any module file.**

If a module file contains `cout <<` anywhere, it is a contract violation.

---

### 1.2 Phase Contract — Every Operation, Every Time

Every operation in every module **must** follow this exact phase sequence:

```
BEFORE → STEP 1 → STEP 2 → ... → STEP N → AFTER
```

- **BEFORE:** Print the full structure as it exists before the operation
- **STEP N:** Print the full structure with the active element highlighted at each intermediate step
- **AFTER:** Print the final state of the full structure

**"Full structure"** means the entire array/list/tree/graph — never partial.

---

### 1.3 Output Format Contract

| Component   | Exact Format                                |
| ----------- | ------------------------------------------- |
| Separator   | 30 dashes: `------------------------------` |
| Header      | `[MODULE] Operation: value`                 |
| Step line   | `Step N: message`                           |
| Result line | `Result: message`                           |
| Error line  | `Error: message`                            |

**Correct example:**

```
------------------------------
[Array] Insert: 99 at index 3
------------------------------
Step 1: BEFORE: [ 10 ][ 20 ][ 30 ][ 40 ]
Step 2: Shifting (40) right
Step 3: Shifting (30) right
Step 4: Placing (99) at index 3
Result: AFTER: [ 10 ][ 20 ][ 30 ][ 99 ][ 40 ]
```

---

### 1.4 Highlight Contract

Active/current element is always wrapped in parentheses:

- `highlight(val)` returns `"(val)"`
- Example: element `42` highlighted = `(42)`
- Example in array: `[ 10 ][ (42) ][ 30 ]` — only active element has parens

---

### 1.5 Timing Delay Contract

| Situation                                      | Delay           |
| ---------------------------------------------- | --------------- |
| Array element shift                            | `sleep_ms(200)` |
| Linked list / tree traversal step              | `sleep_ms(300)` |
| Major state transition (BEFORE→AFTER boundary) | `sleep_ms(500)` |
| AVL rotation step                              | `sleep_ms(400)` |
| Graph traversal step                           | `sleep_ms(300)` |
| Sorting swap                                   | `sleep_ms(200)` |

Delays are mandatory — removing them breaks the visualization experience.

---

### 1.6 Edge Case Output Contract

Every edge case produces an exact, standardized error message via `printError()`:

| Situation                   | Exact Output                                     |
| --------------------------- | ------------------------------------------------ |
| Structure is empty          | `Error: Structure is empty`                      |
| Invalid index `i`, size `n` | `Error: Invalid index [i], valid range [0..n-1]` |
| Overflow, capacity `N`      | `Error: Structure is full (capacity: N)`         |
| Value `X` not found         | `Result: Value X not found`                      |

No custom error messages. These four cover all edge cases across all modules.

---

### 1.7 visual.h Function Contract

These are the **only** functions used for output. Their signatures are fixed:

```cpp
void printSeparator();                           // prints 30 dashes
void printHeader(string module, string op);      // [MODULE] Operation: val
void printStep(int n, string message);           // Step N: message
void printResult(string message);                // Result: message
void printError(string message);                 // Error: message
void sleep_ms(int ms);                           // Windows: Sleep(ms)
string highlight(string val);                    // returns "(val)"
```

Any module needing output calls exactly these. Adding new functions to visual.h requires updating this contracts.md and context.md.

---

## 2. PERFORMANCE LOGGING CONTRACT

### 2.1 The Log-After-Every-Operation Rule

> `Performance::log()` is called after **every single operation** in every module. No exceptions. Even operations that fail (e.g. delete on empty) get logged with 0 steps.

### 2.2 Log Function Signature

```cpp
Performance::log(
    string module,      // e.g. "Array", "BST", "Graph"
    string operation,   // e.g. "InsertAtIndex", "BFS", "AVLInsert"
    int steps,          // number of steps executed
    int comparisons     // number of comparisons made
);
```

### 2.3 Step Counting Rules Per Module

| Module        | Operation         | Step Count Definition              |
| ------------- | ----------------- | ---------------------------------- |
| Array         | InsertAtEnd       | 1 (direct)                         |
| Array         | InsertAtIndex i   | n - i (shifts required)            |
| Array         | Delete at index i | n - i - 1 (shifts)                 |
| Array         | Search            | position found (or n if not found) |
| Linked List   | InsertStart       | 1                                  |
| Linked List   | InsertEnd         | n (traverse to end)                |
| Linked List   | Delete            | position of node                   |
| Linked List   | Search            | position of node (n if not found)  |
| Stack         | Push              | 1                                  |
| Stack         | Pop               | 1                                  |
| Queue         | Enqueue           | 1                                  |
| Queue         | Dequeue           | 1                                  |
| BST           | Insert            | depth of new node                  |
| BST           | Search            | depth of found node                |
| AVL           | Insert            | depth + rotations performed        |
| Heap          | Insert            | log₂(n) heapify steps              |
| BFS           | Traverse          | V + E (vertices + edges)           |
| DFS           | Traverse          | V + E                              |
| Dijkstra      | Shortest Path     | V × V (relaxations)                |
| Bubble Sort   | Sort              | n² comparisons                     |
| Merge Sort    | Sort              | n log n steps                      |
| Binary Search | Search            | log₂(n) steps                      |
| Hash          | Insert (probe)    | probe count                        |

### 2.4 Complexity Label Assignment Contract

```cpp
// performance.cpp maps operation → complexity label
"Array::InsertEnd"      → "O(1)"
"Array::InsertAtIndex"  → "O(n)"
"Array::Search"         → "O(n)"
"LinkedList::Search"    → "O(n)"
"LinkedList::InsertEnd" → "O(n)"
"Stack::Push"           → "O(1)"
"Stack::Pop"            → "O(1)"
"Queue::Enqueue"        → "O(1)"
"BST::Search"           → "O(log n) avg / O(n) worst"
"AVL::Insert"           → "O(log n)"
"Heap::Insert"          → "O(log n)"
"BFS"                   → "O(V+E)"
"DFS"                   → "O(V+E)"
"Dijkstra"              → "O(V²)"
"BubbleSort"            → "O(n²)"
"MergeSort"             → "O(n log n)"
"QuickSort"             → "O(n log n) avg"
"LinearSearch"          → "O(n)"
"BinarySearch"          → "O(log n)"
"HashInsert::Chaining"  → "O(1) avg"
"HashInsert::Probe"     → "O(1) avg / O(n) worst"
```

---

## 3. MODULE INTEGRATION CONTRACT

### 3.1 How Modules Integrate Into main.cpp

Every module exposes a single entry function called from main.cpp:

```cpp
// In main.cpp — module routers
void runArrayModule();
void runLinkedListModule();
void runStackQueueModule();
void runTreeModule();
void runGraphModule();
void runSortingModule();
void runHashingModule();
void runPerformanceReport();
```

Each `run*Module()` function:

1. Shows the sub-menu for that module
2. Takes user input
3. Calls the appropriate DS function
4. Returns to main menu when user is done

### 3.2 Module Independence Contract

- No module includes another module's header
- Modules only include `visual.h` and `performance.h`
- A module must compile independently from all other modules
- Cross-module dependencies = architecture violation

### 3.3 Module File Contract

Each module must have exactly these files:

```
src/core/<folder>/
    <name>.h        ← class definition, no implementation
    <name>.cpp      ← implementation only

tests/
    test_<name>.cpp ← all test cases for that module
```

Header contains:

- Class declaration
- Struct definitions
- Function signatures only
- `#include "../../analysis/visual.h"`
- `#include "../../analysis/performance.h"`

No implementation in headers. No circular includes.

---

## 4. NO-STL CONTRACT

The following are **permanently banned** in all files under `src/core/`:

```cpp
#include <vector>      ❌
#include <list>        ❌
#include <stack>       ❌
#include <queue>       ❌
#include <map>         ❌
#include <set>         ❌
#include <algorithm>   ❌
#include <string>      ⚠️  // Only allowed in visual.h for formatting
std::sort(...)         ❌
std::find(...)         ❌
std::push_back(...)    ❌
```

Allowed everywhere:

```cpp
#include <iostream>    ✅  // only in visual.h, never in modules
#include <chrono>      ✅  // for timing in performance.cpp
#include <cstring>     ✅  // memcpy, memset if needed
```

Note: `std::string` and `std::cout` are allowed **only** inside `visual.h` because that file is the output layer. They must never appear in core module files.

---

## 5. NAMING CONVENTION CONTRACT

### Classes

```cpp
class Array              // PascalCase
class SinglyLinkedList
class DoublyLinkedList
class CircularLinkedList
class StaticStack
class DynamicStack
class SimpleQueue
class CircularQueue
class PriorityQueue
class Deque
class BinaryTree
class BST
class AVLTree
class MinHeap
class MaxHeap
class Graph
class HashChaining
class HashLinearProbe
```

### Functions

```cpp
void insertAtEnd(int val);        // camelCase
void insertAtIndex(int val, int index);
void deleteByValue(int val);
void deleteAtIndex(int index);
bool search(int val);
void display();
void traverseInorder();
void traversePreorder();
void traversePostorder();
void bfs(int start);
void dfs(int start);
void dijkstra(int src);
```

### Variables

```cpp
int data;          // camelCase
Node* head;
Node* tail;
int size;
int capacity;
int top;           // for stack
int front, rear;   // for queue
```

### Files

```
array.cpp / array.h
linked_list.cpp / linked_list.h
stack.cpp / stack.h
queue.cpp / queue.h
binary_tree.cpp / binary_tree.h
bst.cpp / bst.h
avl.cpp / avl.h
heap.cpp / heap.h
graph.cpp / graph.h
bfs.cpp / bfs.h
dfs.cpp / dfs.h
dijkstra.cpp / dijkstra.h
mst.cpp / mst.h
searching.cpp / searching.h
sorting.cpp / sorting.h
hash_chaining.cpp / hash_chaining.h
hash_linear_probe.cpp / hash_linear_probe.h
performance.cpp / performance.h
visual.h
```

---

## 6. CONTEXT.md UPDATE CONTRACT

After **every single task** (every commit), `docs/context.md` must be updated with:

```markdown
## Last Modified: [date]

### Files Changed

- `src/core/linear/linked_list.cpp`
- `tests/test_linked_list.cpp`

### Functions Changed

- `DoublyLinkedList::insertEnd()` — added
- `DoublyLinkedList::display()` — added

### What Changed

- Implemented doubly linked list insert at end with pointer management

### Why It Changed

- Part of M1-T1: core logic phase for doubly LL module

### Current System State

- Array module: complete ✅
- Singly LL: complete ✅
- Doubly LL: core logic done, visualization pending ⏳
```

Failing to update context.md after a task = task not complete.

---

## 7. TESTING CONTRACT

Every module test file must include these categories:

```
1. Normal cases     — typical inputs, expected outputs
2. Edge: empty      — operation on empty structure
3. Edge: overflow   — insert beyond capacity
4. Edge: not found  — search/delete non-existent value
5. Edge: boundary   — first/last element operations
6. Visualization    — verify output format matches contract
7. Performance      — verify Performance::log was called
```

Test format:

```cpp
// Test: [module] - [operation] - [case]
// Input: [what is passed]
// Expected: [what should happen]
// Actual: [run and observe]
```

Tests are manual (run → observe output) for now. No test framework.

---

## 8. GIT COMMIT CONTRACT

```
type: module - description

type options:
  feat     → new working feature
  fix      → bug fix
  test     → test file or test result
  docs     → documentation only
  chore    → config, structure, cleanup
  audit    → review result
  refactor → restructure, no behavior change
```

**One commit per task. No bundling multiple tasks into one commit.**

Examples:

```
feat: doubly linked list - visualization added
fix: array.cpp - Performance::log missing in delete op
test: BST - all edge cases passing
docs: context.md updated after module 3 AVL completion
audit: visual.h - all 7 contract functions verified
```

---

## 9. SYSTEM INTEGRATION CONTRACT

### Integration Order

Modules are integrated into main.cpp in this exact order. Do not add to menu before core + viz + perf are all done:

```
Phase 0 (DONE):   Array, Singly LL, Performance, visual.h
Phase 1 (M1):     Doubly LL, Circular LL
Phase 2 (M2):     Static Stack, Dynamic Stack, Queue, Circular Queue, Priority Queue, Deque
Phase 3 (M3):     Binary Tree, BST, AVL, Heap
Phase 4 (M4):     Graph (repr + BFS + DFS + Dijkstra + MST)
Phase 5 (M5):     Linear Search, Binary Search, Bubble, Selection, Insertion, Merge, Quick
Phase 6 (M6):     Hash Chaining, Linear Probing
Phase 7 (M7):     Performance Report Upgrade
Phase 8 (FUTURE): Qt GUI
Phase 9 (FUTURE): SQLite
Phase 10 (FUTURE):Teacher-Student Module
```

### Integration Rule

A module is only added to main.cpp's menu **after** all of these pass:

- [ ] Core logic compiles with zero errors
- [ ] Visualization output matches contract format exactly
- [ ] `Performance::log()` verified working
- [ ] All edge cases tested
- [ ] Test file written and passing
- [ ] context.md updated

---

## 10. THE ARCHITECTURE BOUNDARY CONTRACT

```
These boundaries are permanent and never crossed:

Control Layer    never implements DS logic
Core Layer       never produces output (no cout)
Core Layer       never calls menu or navigation functions
Visual Layer     never modifies data structures
Visual Layer     never calls Performance::log
Analysis Layer   never calls DS operations
Analysis Layer   never produces visualization output
```

Any code that crosses these boundaries must be refactored immediately before proceeding.
