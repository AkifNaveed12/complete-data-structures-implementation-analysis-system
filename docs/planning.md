# CDSIAS — Project Planning & Task Breakdown

## planning.md

---

## APPROACH

This project follows **vibe coding** through Claude (antigravity instruct mode).
Each task is atomic, testable, and follows this rule:

> One task = one feature = one test = one commit = one context.md update

Tasks are labeled: `T0, T1, T2...` per module.
Each task produces a working, tested, committed state.

---

## PRE-REQUISITE PHASE — REPO ANALYSIS & HEALTH CHECK

Before writing a single new line of code, we fully analyze and validate the existing repo.

---

### PRE-T0 — Full Repo Structure Scan

**Goal:** Map every file currently in the repo, its purpose, and its state.

## NOTE THAT ROOT FOLDER IS complete-data-structures-implementation-analysis-system

**Actions:**

1. List all files and folders recursively
2. Identify what exists vs what the architecture requires
3. Flag: missing files, extra files, misplaced files
4. Document the exact current folder tree in `docs/context.md`

**Deliverable:** Confirmed folder map in context.md

**Commit:** `chore: repo structure scan - pre analysis phase`

---

### PRE-T1 — Code Quality Audit: array.cpp + array.h

**Goal:** Read and validate the array module thoroughly.

**Checklist:**

- [ ] All 4 operations present: insert-end, insert-at-index, delete, search, display
- [ ] No STL usage anywhere
- [ ] Visualization uses `visual.h` functions only (no raw cout)
- [ ] `Performance::log()` called after every operation
- [ ] Edge cases handled: empty, invalid index, overflow
- [ ] Output format matches visual contract exactly
- [ ] Highlight uses `(val)` format
- [ ] Phase flow: BEFORE → STEP N → AFTER present

**Flag:** Any violation is a bug → noted → fixed in PRE-T3

**Commit:** `audit: array module code review complete`

---

### PRE-T2 — Code Quality Audit: linked_list.cpp + linked_list.h

**Goal:** Read and validate the linked list (singly) module.

**Checklist:**

- [ ] Operations: insert-start, insert-end, delete-by-value, search, display
- [ ] No STL
- [ ] visual.h only output
- [ ] Performance::log() called
- [ ] Edge cases handled
- [ ] Traversal visualization: `(10) → 20 → 30 → NULL` format
- [ ] Phase flow correct

**Flag:** Violations noted

**Commit:** `audit: linked list module code review complete`

---

### PRE-T3 — Code Quality Audit: performance.cpp + visual.h

**Goal:** Validate the analysis layer.

**Checklist for visual.h:**

- [ ] `printSeparator()` → 30 dashes exactly
- [ ] `printHeader(module, operation)` → correct format
- [ ] `printStep(n, msg)` → `Step N: msg`
- [ ] `printResult(msg)` → `Result: msg`
- [ ] `printError(msg)` → `Error: msg`
- [ ] `sleep_ms(ms)` → works on Windows
- [ ] `highlight(val)` → returns `"(val)"`

**Checklist for performance.cpp:**

- [ ] `Performance::log(module, op, steps, comparisons)` exists
- [ ] In-memory storage working (vector or array)
- [ ] `Performance::report()` prints formatted table

**Commit:** `audit: analysis layer (visual.h + performance.cpp) review complete`

---

### PRE-T4 — Code Quality Audit: main.cpp

**Goal:** Validate the control layer.

**Checklist:**

- [ ] Module menu exists and routes correctly
- [ ] Array and Linked List both reachable
- [ ] No business logic in main.cpp
- [ ] Clean menu display
- [ ] Input validation on menu selection

**Commit:** `audit: main.cpp control layer review complete`

---

### PRE-T5 — Run Full System End-to-End Test

**Goal:** Compile and run the entire current system. Confirm it works.

**Steps:**

1. Compile with g++: `g++ src/main.cpp src/core/linear/array.cpp src/core/linear/linked_list.cpp src/analysis/performance.cpp -o cdsias`
2. Run and test every existing operation manually
3. Verify visual output matches contracts
4. Verify no crashes, no undefined behavior
5. Document: what passes, what fails

**Commit:** `test: full system end-to-end run - baseline established`

---

### PRE-T6 — Fix All Audit Issues

**Goal:** Fix every bug/violation found in PRE-T1 through PRE-T5.

**Rules:**

- Fix one file at a time
- After each fix: recompile and test
- No new features during this phase
- Update context.md after each fix

**Commit per fix:** `fix: [file] - [what was fixed] - [why]`
Example: `fix: array.cpp - missing Performance::log in delete op - contract violation`

---

### PRE-T7 — Update docs/context.md with Final Baseline State

**Goal:** context.md fully reflects the verified, working state of the repo.

**Must include:**

- Exact folder structure (copy of tree)
- Status of each file (verified/working)
- What each function does
- Last verified date

**Commit:** `docs: context.md updated - baseline state documented`

---

> ✅ After PRE phase: system is 100% clean, working, contract-compliant, and documented.
> Now we begin feature development.

---

## MODULE 1 — DOUBLY LINKED LIST

**Files:** `src/core/linear/linked_list.cpp`, `linked_list.h`, `tests/test_linked_list.cpp`

---

### M1-T0 — Design Doubly Linked List Node & Class Structure

**Goal:** Define `DoublyLinkedList` class with node struct in `linked_list.h`

**Node struct:**

```cpp
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
};
```

**Class methods to declare:**

- `insertStart(int val)`
- `insertEnd(int val)`
- `deleteByValue(int val)`
- `search(int val)`
- `display()`

**No implementation yet — header only**

**Commit:** `feat: doubly linked list - node and class header defined`

---

### M1-T1 — Implement Doubly LL Core Logic (No Visualization)

**Goal:** Pure logic implementation, no output yet

**Rules:**

- No STL
- No cout
- Pointer management: set prev and next correctly on every insert/delete
- Handle: empty list, single node, multiple nodes

**Commit:** `feat: doubly linked list - core logic implemented`

---

### M1-T2 — Add Visualization to Doubly LL

**Goal:** Add step-by-step CLI visualization using visual.h only

**Format:**

```
NULL ← (10) ↔ 20 ↔ 30 → NULL
```

**Phase flow:**

- `insertStart(5)`:
  - BEFORE: `NULL ← 10 ↔ 20 → NULL`
  - Step 1: `Creating new node (5)`
  - Step 2: `Linking (5) → 10, prev = NULL`
  - AFTER: `NULL ← (5) ↔ 10 ↔ 20 → NULL`

- Delays: 300ms per traversal step

**All output via visual.h — zero raw cout**

**Commit:** `feat: doubly linked list - visualization added`

---

### M1-T3 — Add Performance Logging to Doubly LL

**Goal:** `Performance::log()` called after every operation with correct step count

**Steps counted:**

- insertStart: steps = 1 (no traversal)
- insertEnd: steps = n (traverse to end)
- delete: steps = position of node
- search: steps = position of node (or n if not found)

**Commit:** `feat: doubly linked list - performance logging added`

---

### M1-T4 — Add Doubly LL to Main Menu

**Goal:** Wire doubly LL into main.cpp module menu

**Menu entry:** Under "Linked Lists" → "Doubly Linked List"

**Commit:** `feat: main.cpp - doubly linked list menu wired`

---

### M1-T5 — Write Test File: test_linked_list.cpp (Doubly Section)

**Goal:** Test all operations + edge cases

**Test cases:**

- Insert into empty list
- Insert at start (single and multiple)
- Insert at end
- Delete head
- Delete tail
- Delete middle node
- Delete from empty list → Error message
- Delete non-existent value → not found
- Search found
- Search not found
- Display empty list

**Compile and run all tests manually, verify output**

**Commit:** `test: doubly linked list - all test cases passing`

---

### M1-T6 — Circular Linked List (same T0–T5 pattern)

**Format:** `10 → 20 → 30 → [HEAD]`
**Head pointer loops back — visualize the loop**

**Sub-tasks:**

- M1-T6-a: Header definition
- M1-T6-b: Core logic
- M1-T6-c: Visualization
- M1-T6-d: Performance logging
- M1-T6-e: Main menu wiring
- M1-T6-f: Test file

**Commit per sub-task.**
**Final commit:** `feat: circular linked list - complete with tests`

---

### M1-T7 — Update docs/context.md

**Document:**

- Files modified: linked_list.h, linked_list.cpp, main.cpp, tests/test_linked_list.cpp
- Functions added
- What changed and why

**Commit:** `docs: context.md updated after module 1 completion`

---

## MODULE 2 — STACK & QUEUE

**Files:** `src/core/stack_queue/`, `tests/test_stack.cpp`, `tests/test_queue.cpp`

---

### M2-T0 — Static Stack

**Header:** `stack.h` — `StaticStack` class
**Operations:** push, pop, peek, display, isEmpty, isFull
**Max capacity:** defined as constant (e.g. 100)
**Visualization:**

```
[ TOP ]
  (30)
   20
   10
```

- Push: show element going in at top
- Pop: show element leaving from top
- Overflow: `Error: Structure is full (capacity: 100)`
- Underflow: `Error: Structure is empty`

**Sub-tasks:** header → logic → visualization → perf log → menu → test → context.md update
**Commit:** `feat: static stack - complete with tests`

---

### M2-T1 — Dynamic Stack (Linked-list based)

Same structure as static stack but no overflow (grows dynamically).
Underflow still possible.

**Commit:** `feat: dynamic stack - complete with tests`

---

### M2-T2 — Simple Queue

**Operations:** enqueue, dequeue, peek, display
**Visualization:**

```
FRONT → [ 10 ] [ 20 ] [ (30) ] ← REAR
```

**Commit:** `feat: simple queue - complete with tests`

---

### M2-T3 — Circular Queue

**Visualization:** show wrap-around when rear wraps to index 0

```
[ 30 ] [ 10 ] [ 20 ]
  ↑REAR       ↑FRONT
```

**Commit:** `feat: circular queue - complete with tests`

---

### M2-T4 — Priority Queue

**Operations:** insert-by-priority, extract-max-priority
**Visualization:** show ordering after each insert
**Commit:** `feat: priority queue - complete with tests`

---

### M2-T5 — Deque

**Operations:** insertFront, insertRear, deleteFront, deleteRear, display
**Commit:** `feat: deque - complete with tests`

---

### M2-T6 — Update docs/context.md

**Commit:** `docs: context.md updated after module 2 completion`

---

## MODULE 3 — TREES

**Files:** `src/core/trees/`, `tests/test_trees.cpp`

---

### M3-T0 — Binary Tree

**Operations:** insert (level-order), traversals (inorder, preorder, postorder)
**Visualization:** ASCII tree printed at each step

```
        50
       /  \
     30    70
```

**Commit:** `feat: binary tree - complete with tests`

---

### M3-T1 — BST (Binary Search Tree)

**Operations:** insert, delete, search
**Visualization:**

- Search: show path taken (`Going left... Going right...`)
- Delete: show which case (leaf / one child / two children)

**Commit:** `feat: BST - complete with tests`

---

### M3-T2 — AVL Tree

**Operations:** insert with auto-balancing
**Visualization:**

- Show balance factors at each node after insert
- Show rotation type: `LL Rotation`, `RR Rotation`, `LR Rotation`, `RL Rotation`
- Rotation delay: 400ms
- Print tree before and after rotation

**Commit:** `feat: AVL tree - complete with tests`

---

### M3-T3 — Heap (Min and Max)

**Operations:** insert, extract-min/max, heapify
**Visualization:**

- Show heap as array representation
- Highlight element being swapped during heapify

**Commit:** `feat: heap (min+max) - complete with tests`

---

### M3-T4 — Update docs/context.md

**Commit:** `docs: context.md updated after module 3 completion`

---

## MODULE 4 — GRAPH

**Files:** `src/core/graph/`, `tests/test_graph.cpp`

---

### M4-T0 — Graph Representation

**Two modes:** Adjacency List, Adjacency Matrix
**Operations:** addNode, addEdge, display (both formats)

**Commit:** `feat: graph representation (list + matrix) - complete`

---

### M4-T1 — BFS

**Visualization:**

- Level by level: show which nodes are added to queue at each step
- Current node: `(N)`, visited: `*N`

**Commit:** `feat: BFS - complete with tests`

---

### M4-T2 — DFS

**Visualization:**

- Show recursive path: `Visiting (1) → Visiting (3) → Backtrack → Visiting (2)`

**Commit:** `feat: DFS - complete with tests`

---

### M4-T3 — Dijkstra

**Visualization:**

- Show distance table at every relaxation step
- Highlight edge being relaxed

**Commit:** `feat: Dijkstra - complete with tests`

---

### M4-T4 — MST: Kruskal + Prim

**Kruskal:** show edges sorted → show each accepted/rejected edge
**Prim:** show tree growing node by node

**Commit:** `feat: MST (Kruskal + Prim) - complete with tests`

---

### M4-T5 — Update docs/context.md

**Commit:** `docs: context.md updated after module 4 completion`

---

## MODULE 5 — SEARCHING & SORTING

**Files:** `src/core/searching_sorting/`, `tests/test_searching.cpp`, `tests/test_sorting.cpp`

---

### M5-T0 — Linear Search

**Visualization:** highlight each element checked: `Checking (10)... Checking (20)...`

**Commit:** `feat: linear search - complete with tests`

---

### M5-T1 — Binary Search

**Visualization:**

- Show left, right, mid at every step
- `[left=0] [mid=4] [right=8]`

**Commit:** `feat: binary search - complete with tests`

---

### M5-T2 — Bubble Sort

**Visualization:** full array at every pass, swapped elements highlighted

**Commit:** `feat: bubble sort - complete with tests`

---

### M5-T3 — Selection Sort

**Visualization:** show minimum found, then show swap

**Commit:** `feat: selection sort - complete with tests`

---

### M5-T4 — Insertion Sort

**Visualization:** show element being inserted into sorted portion step by step

**Commit:** `feat: insertion sort - complete with tests`

---

### M5-T5 — Merge Sort

**Visualization:** show split steps, then merge steps with comparison at each merge

**Commit:** `feat: merge sort - complete with tests`

---

### M5-T6 — Quick Sort

**Visualization:** show pivot selection, partitioning step by step

**Commit:** `feat: quick sort - complete with tests`

---

### M5-T7 — Update docs/context.md

**Commit:** `docs: context.md updated after module 5 completion`

---

## MODULE 6 — HASHING

**Files:** `src/core/hashing/`, `tests/test_hashing.cpp`

---

### M6-T0 — Hash Table Foundation

**Hash function:** `key % tableSize`
**Table display:**

```
[0]:  →
[1]:  → 11 → 21
[2]:  → 2
```

**Commit:** `feat: hash table base structure`

---

### M6-T1 — Chaining (Separate Chaining)

**Visualization:**

- Show which slot the key maps to
- Show chain before and after insert
- Show collision: `Collision at [1]! Adding to chain`

**Commit:** `feat: hash chaining - complete with tests`

---

### M6-T2 — Linear Probing

**Visualization:**

- Show probe steps one by one
- `Slot [3] occupied → probing [4] → probing [5] → inserted at [5]`

**Commit:** `feat: hash linear probing - complete with tests`

---

### M6-T3 — Update docs/context.md

**Commit:** `docs: context.md updated after module 6 completion`

---

## MODULE 7 — PERFORMANCE ANALYTICS UPGRADE

**Files:** `src/analysis/performance.cpp`, `performance.h`

---

### M7-T0 — Enhance Performance Report

**Goal:** Current report → detailed formatted table

**Output format:**

```
==============================
     PERFORMANCE REPORT
==============================
Module          | Operation      | Steps | Comparisons | Complexity
----------------|----------------|-------|-------------|----------
Array           | Insert(index)  |  5    |   0         | O(n)
LinkedList      | Search         |  3    |   3         | O(n)
```

**Commit:** `feat: performance report - enhanced formatted table`

---

### M7-T1 — Complexity Labels

**Goal:** Auto-assign Big-O label per operation type

**Map:**

- Array insert at end → O(1)
- Array insert at index → O(n)
- Linked list search → O(n)
- BST search (balanced) → O(log n)
- BFS/DFS → O(V+E)
- Heap insert → O(log n)
- Bubble sort → O(n²)
- Merge sort → O(n log n)

**Commit:** `feat: performance - auto complexity label assignment`

---

### M7-T2 — Update docs/context.md

**Commit:** `docs: context.md updated after module 7 completion`

---

## FINAL PHASE — SYSTEM INTEGRATION TEST

---

### FIN-T0 — Full System Compile Test

Compile all modules together. Zero warnings. Zero errors.

**Commit:** `test: full system compile - all modules integrated`

---

### FIN-T1 — Full User Flow Test

Walk through every module, every operation manually.
Verify:

- Visualization correct
- Performance logged
- Edge cases all show correct error messages
- Menu navigation works flawlessly

**Commit:** `test: full user flow - all operations verified`

---

### FIN-T2 — Final docs/context.md

Complete, final, accurate context.md with:

- Full folder structure
- Every file's role
- Every function's description
- Complete status of all modules

**Commit:** `docs: final context.md - project complete`

---

## TASK SEQUENCE SUMMARY

```
PRE-T0  → Repo scan
PRE-T1  → Array audit
PRE-T2  → Linked list audit
PRE-T3  → visual.h + performance audit
PRE-T4  → main.cpp audit
PRE-T5  → End-to-end run
PRE-T6  → Fix all issues
PRE-T7  → context.md baseline

M1: Doubly LL → Circular LL (T0–T7)
M2: Static Stack → Deque (T0–T6)
M3: BT → BST → AVL → Heap (T0–T4)
M4: Graph → BFS → DFS → Dijkstra → MST (T0–T5)
M5: Linear/Binary Search → 5 Sorts (T0–T7)
M6: Hashing Chaining + Linear Probe (T0–T3)
M7: Performance Report Upgrade (T0–T2)

FIN-T0 → Compile test
FIN-T1 → Full flow test
FIN-T2 → Final context.md
```

---

## COMMIT MESSAGE CONVENTION

```
type: module - description - reason (if fix)

Types:
  feat    → new feature
  fix     → bug fix
  test    → test file
  docs    → documentation update
  chore   → structure/config change
  audit   → code review result
  refactor→ restructure without behavior change
```

**Examples:**

```
feat: doubly linked list - core logic implemented
fix: array.cpp - missing Performance::log in delete - contract violation
test: BST - all edge cases passing
docs: context.md updated after module 3 completion
audit: visual.h - all contract functions verified
```

---

## RULES REMINDER (EVERY TASK)

1. No STL in core modules
2. All output through visual.h
3. Performance::log() after every operation
4. Edge cases: empty, invalid index, overflow — always
5. Never break existing code
6. Update context.md after every task
7. Visual contract: BEFORE → STEPS → AFTER — always
8. One task → one test → one commit
