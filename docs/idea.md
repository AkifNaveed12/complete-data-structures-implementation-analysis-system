# CDSIAS — Comprehensive Data Structure Implementation & Analysis System

## Master Idea Document (idea.md)

---

## 1. PROJECT IDENTITY

| Field        | Detail                                                        |
| ------------ | ------------------------------------------------------------- |
| Project Name | Comprehensive Data Structure Implementation & Analysis System |
| Short Name   | CDSIAS                                                        |
| Type         | Desktop Application (CLI now → Qt GUI future)                 |
| Language     | C++ (Pure, NO STL for core data structures)                   |
| Platform     | Windows                                                       |
| DBMS         | SQLite (future phase)                                         |
| Tools        | C++, Qt Framework, VS Code / Qt Creator                       |
| Team         | Akif Naveed (FA24-BSE-129), Arslan Shafiq (FA24-BSE-119)      |
| Supervisor   | Mr. Hassan Butt                                               |

## NOTE THAT ROOT FOLDER IS complete-data-structures-implementation-analysis-system

---

## 2. THE REAL PROBLEM BEING SOLVED

Students study data structures theoretically but never truly understand:

- How they work internally
- How they perform against each other
- What actually happens step by step during an operation

CDSIAS bridges the gap between **theory and practice** by building a fully interactive, visual, and analytical laboratory where every operation is shown step by step, performance is tracked in real time, and all structures are implemented manually — no STL shortcuts.

---

## 3. CORE VISION

> **CDSIAS is not just a project. It is a Complete Interactive Data Structure Laboratory System.**

The final product is a system where:

- A user launches the app
- Selects any data structure
- Performs an operation
- Watches it execute visually, step by step
- Sees real performance data (steps, comparisons, time complexity)
- Everything is logged, modular, and extensible

---

## 4. DESIGN PHILOSOPHY

1. **Learn by doing** — every operation is interactive
2. **Visualize every step** — no black-box execution
3. **Analyze performance** — every operation is measured
4. **Modular and scalable** — each module is independent
5. **Industry-level structure** — architecture is production quality
6. **No STL** — all core data structures built from scratch

---

## 5. TECHNOLOGY STACK

| Layer             | Technology                               |
| ----------------- | ---------------------------------------- |
| Core Logic        | C++ (no STL)                             |
| CLI Visualization | C++ with sleep delays + formatted output |
| GUI (future)      | Qt Framework                             |
| Database (future) | SQLite                                   |
| Version Control   | Git + GitHub                             |
| IDE               | VS Code / Qt Creator                     |
| Build System      | g++ / CMake (future)                     |

---

## 6. SYSTEM ARCHITECTURE

```
┌─────────────────────────────────────────────┐
│              CONTROL LAYER                  │
│         main.cpp — menu navigation          │
└────────────────────┬────────────────────────┘
                     │
       ┌─────────────┼─────────────┐
       ▼             ▼             ▼
┌──────────┐  ┌──────────┐  ┌──────────────┐
│  CORE    │  │ VISUAL   │  │  ANALYSIS    │
│  LAYER   │  │  LAYER   │  │   LAYER      │
│          │  │          │  │              │
│ Pure DS  │  │ CLI now  │  │ Performance  │
│ No STL   │  │ Qt future│  │ Logging      │
└──────────┘  └──────────┘  └──────────────┘
                                    │
                          ┌─────────▼────────┐
                          │   DATA LAYER     │
                          │ SQLite (future)  │
                          └──────────────────┘
```

### Layer Responsibilities

**Core Layer** (`src/core/`)

- Implements all data structures from scratch
- Zero UI logic — pure logic only
- No STL allowed

**Visualization Layer** (`src/analysis/visual.h`)

- All output goes through `visual.h` functions only
- No raw `cout` in module files
- Handles step-by-step display, highlighting, delays

**Analysis Layer** (`src/analysis/performance.cpp`)

- `Performance::log()` called after every single operation
- Tracks: steps, comparisons, traversals
- In-memory now → SQLite future

**Control Layer** (`src/main.cpp`)

- Menu-driven navigation
- Routes user to correct module
- Never contains business logic

**Future GUI Layer** (`src/gui/`)

- Qt-based graphical interface
- Replaces CLI menu, keeps core layer unchanged

---

## 7. FOLDER STRUCTURE

```
cdsias-dsa-engine/
│
├── src/
│   ├── core/
│   │   ├── linear/
│   │   │   ├── array.cpp
│   │   │   ├── array.h
│   │   │   ├── linked_list.cpp
│   │   │   └── linked_list.h
│   │   ├── stack_queue/
│   │   │   ├── stack.cpp / stack.h
│   │   │   ├── queue.cpp / queue.h
│   │   │   ├── circular_queue.cpp / .h
│   │   │   ├── priority_queue.cpp / .h
│   │   │   └── deque.cpp / deque.h
│   │   ├── trees/
│   │   │   ├── binary_tree.cpp / .h
│   │   │   ├── bst.cpp / bst.h
│   │   │   ├── avl.cpp / avl.h
│   │   │   └── heap.cpp / heap.h
│   │   ├── graph/
│   │   │   ├── graph.cpp / graph.h
│   │   │   ├── bfs.cpp / bfs.h
│   │   │   ├── dfs.cpp / dfs.h
│   │   │   ├── dijkstra.cpp / .h
│   │   │   └── mst.cpp / mst.h
│   │   ├── searching_sorting/
│   │   │   ├── searching.cpp / .h
│   │   │   └── sorting.cpp / sorting.h
│   │   └── hashing/
│   │       ├── hash_chaining.cpp / .h
│   │       └── hash_linear_probe.cpp / .h
│   │
│   ├── analysis/
│   │   ├── performance.cpp
│   │   ├── performance.h
│   │   └── visual.h
│   │
│   ├── gui/               ← future Qt files
│   │
│   └── main.cpp
│
├── tests/
│   ├── test_array.cpp
│   ├── test_linked_list.cpp
│   ├── test_stack.cpp
│   ├── test_queue.cpp
│   ├── test_trees.cpp
│   ├── test_graph.cpp
│   ├── test_sorting.cpp
│   ├── test_searching.cpp
│   └── test_hashing.cpp
│
└── docs/
    ├── idea.md            ← this file
    ├── planning.md
    └── context.md         ← always updated after every change
```

---

## 8. VISUALIZATION CONTRACT (FINALIZED — DO NOT CHANGE)

### 8.1 Operation Phase Flow

Every single operation in every module MUST follow this exact phase sequence:

```
BEFORE → STEP 1 → STEP 2 → ... → STEP N → AFTER
```

- Print the **full structure** at every phase (never partial)
- Active/highlighted element shown with parentheses: `(val)`
- Never skip phases even if the operation is simple

### 8.2 Timing Delays

| Event                              | Delay |
| ---------------------------------- | ----- |
| Element shift (array)              | 200ms |
| Traversal step (linked list, tree) | 300ms |
| Major transition (before→after)    | 500ms |
| AVL rotation                       | 400ms |

### 8.3 Output Format

```
------------------------------
[MODULE] Operation: value
------------------------------
Step 1: message
Step 2: message
...
Result: message
```

| Output Type | Format                                      |
| ----------- | ------------------------------------------- |
| Separator   | 30 dashes: `------------------------------` |
| Header      | `[MODULE] Operation: val`                   |
| Step        | `Step N: message`                           |
| Result      | `Result: message`                           |
| Error       | `Error: message`                            |

### 8.4 Shared visual.h Functions (ALL modules use these — no exceptions)

```cpp
void printSeparator();
void printHeader(string module, string operation);
void printStep(int n, string message);
void printResult(string message);
void printError(string message);
void sleep_ms(int ms);
string highlight(string val);   // returns "(val)"
```

### 8.5 Edge Case Output (standardized)

| Situation       | Output                                           |
| --------------- | ------------------------------------------------ |
| Empty structure | `Error: Structure is empty`                      |
| Invalid index i | `Error: Invalid index [i], valid range [0..n-1]` |
| Overflow        | `Error: Structure is full (capacity: N)`         |
| Value not found | `Result: Value X not found`                      |

---

## 9. PERFORMANCE LOGGING CONTRACT

- `Performance::log(module, operation, steps, comparisons)` called after **every** operation
- Stored in-memory (vector/array) for now
- Future: persisted to SQLite
- Performance report accessible from main menu

---

## 10. MODULE DESCRIPTIONS (DETAILED)

---

### MODULE 1 — LINEAR DATA STRUCTURES

**File:** `src/core/linear/array.cpp`, `linked_list.cpp`

#### Array

Operations:

- Insert at end
- Insert at position (index)
- Delete by index
- Search by value
- Display

Visualization:

- Insertion at index → elements shift right one by one, each shift is one step
- Active element highlighted with `(val)`
- Full array printed at every step

#### Linked List — Singly (DONE)

Operations:

- Insert at start
- Insert at end
- Delete by value
- Search
- Display / Traversal

Visualization:

- Traversal shown node by node
- Format: `(10) → 20 → 30 → NULL`
- Active node highlighted as it moves

#### Linked List — Doubly (NEXT)

- Same operations as singly
- Show both prev and next pointers in visualization
- Format: `NULL ← (10) ↔ 20 ↔ 30 → NULL`

#### Linked List — Circular (NEXT)

- Show circular nature: `10 → 20 → 30 → [back to 10]`

---

### MODULE 2 — STACK & QUEUE

**File:** `src/core/stack_queue/`

#### Static Stack

- Push / Pop / Peek
- Fixed array-based
- Overflow/underflow shown visually

#### Dynamic Stack

- Linked-list based
- Grows dynamically

#### Queue

- Enqueue / Dequeue / Display

#### Circular Queue

- Wrap-around visualization

#### Priority Queue

- Insert by priority
- Show priority ordering

#### Deque

- Insert/delete at both ends

Visualization for all:

- Stack: vertical display, top marked with `← TOP`
- Queue: horizontal display, front and rear marked

---

### MODULE 3 — TREES

**File:** `src/core/trees/`

#### Binary Tree

- Insert, traversals (Inorder, Preorder, Postorder)

#### BST

- Insert, Delete, Search
- Show path taken during search

#### AVL Tree

- Insert with rotations
- Show rotation type (LL, RR, LR, RL) at each step
- Rotation delay: 400ms

#### Heap (Min/Max)

- Insert, Extract-min/max
- Heapify visualization

Visualization:

- ASCII tree printed at every step
- Path to current node highlighted

---

### MODULE 4 — GRAPH

**File:** `src/core/graph/`

#### Representations

- Adjacency List
- Adjacency Matrix

#### Algorithms

- BFS — wave-by-wave traversal shown
- DFS — recursive path shown step by step
- Dijkstra — shortest path update shown at each relaxation
- MST — Kruskal (sort edges → add) and Prim (grow tree step by step)

Visualization:

- Nodes numbered
- Current node highlighted with `(N)`
- Visited nodes marked with `*`

---

### MODULE 5 — SEARCHING & SORTING

**File:** `src/core/searching_sorting/`

#### Searching

- Linear Search — checks each element one by one
- Binary Search — shows left/right/mid bounds at every step

#### Sorting

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort

Visualization:

- Full array printed at every step
- Elements being compared: `(A) vs (B)`
- Swapped elements highlighted
- Each pass is a new step

---

### MODULE 6 — HASHING

**File:** `src/core/hashing/`

#### Hash Functions

- Division method: `key % tableSize`

#### Collision Resolution

- Chaining — show linked chain at each slot
- Linear Probing — show probe steps one by one

Visualization:

- Hash table printed as indexed slots
- Probe steps shown one at a time
- Collision highlighted: `Collision at [i]! Probing...`

---

### MODULE 7 — PERFORMANCE ANALYTICS

**File:** `src/analysis/performance.cpp`

Tracks per operation:

- Module name
- Operation name
- Step count
- Comparison count

Output:

- Table of all logged operations
- Complexity label (O(1), O(n), O(log n)) per operation
- Future: bar chart comparison via Qt

---

### MODULE 8 — AUTH + TEACHER-STUDENT EXTENSION (FUTURE)

- Teacher login → assign exercises → view student performance
- Student login → solve tasks → submit

Not in current scope. Planned for final phase.

---

## 11. USER FLOW

```
System Launch
     ↓
Main Menu (modules listed)
     ↓
Select Module (e.g. Array)
     ↓
Select Operation (e.g. Insert at Index)
     ↓
Enter Value / Parameters
     ↓
Step-by-Step Visualization
     ↓
Result Message
     ↓
Performance Logged
     ↓
Return to Module Menu or Main Menu
```

---

## 12. CURRENT WORK STATUS

| Module                                                       | Status     |
| ------------------------------------------------------------ | ---------- |
| Array (insert/delete/search/display + shift animation)       | ✅ DONE    |
| Linked List — Singly (insert/delete/search/traversal visual) | ✅ DONE    |
| Performance tracking module                                  | ✅ DONE    |
| Modular folder structure                                     | ✅ DONE    |
| Menu-driven system (main.cpp)                                | ✅ DONE    |
| visual.h shared functions                                    | ✅ DONE    |
| Doubly Linked List                                           | ❌ NOT YET |
| Circular Linked List                                         | ❌ NOT YET |
| Stack (all variants)                                         | ❌ NOT YET |
| Queue (all variants)                                         | ❌ NOT YET |
| Trees (BT/BST/AVL/Heap)                                      | ❌ NOT YET |
| Graph (BFS/DFS/Dijkstra/MST)                                 | ❌ NOT YET |
| Searching & Sorting                                          | ❌ NOT YET |
| Hashing                                                      | ❌ NOT YET |
| Qt GUI                                                       | ❌ FUTURE  |
| SQLite integration                                           | ❌ FUTURE  |
| Teacher-Student module                                       | ❌ FUTURE  |

---

## 13. RULES — NON-NEGOTIABLE

1. **NO STL** in core data structures — ever
2. All output through `visual.h` functions — no raw `cout` in modules
3. `Performance::log()` called after every operation
4. Every new feature requires: core logic + visualization + performance log + test file
5. Edge cases always handled: empty, invalid index, overflow
6. Never break existing working code
7. Naming conventions consistent across all files
8. Modular architecture enforced — no mixing of layers
9. `docs/context.md` updated after every change (file modified, function modified, what changed, why)
10. Visual contract phases (BEFORE→STEPS→AFTER) followed in every single module

---

## 14. GOAL

> Build a 100% visualization-ready, modular, CLI-first Data Structure Laboratory that implements every fundamental and advanced data structure from scratch, with step-by-step visual output and real-time performance tracking — ready for Qt GUI layer to be placed on top without touching core logic.
