# CDSIAS — User Flows Document

## userflows.md

> This document defines exactly how a user interacts with the system from launch to exit, for every module and every operation. Every screen, every prompt, every output, every path.

---

## FLOW 0 — SYSTEM LAUNCH & MAIN DASHBOARD

```
┌─────────────────────────────────────────────────────────┐
│                                                         │
│        CDSIAS — Data Structure Visualizer               │
│        Comprehensive DS Implementation & Analysis       │
│                                                         │
│                 [1] Start System                        │
│                 [2] Login    (Future)                   │
│                 [0] Exit                                │
│                                                         │
└─────────────────────────────────────────────────────────┘

User enters: 1
```

**→ Goes to Main Dashboard**

```
==================================
    DATA STRUCTURE LAB SYSTEM
==================================

  [1] Linear Data Structures
  [2] Stack & Queue
  [3] Trees
  [4] Graph Algorithms
  [5] Searching & Sorting
  [6] Hashing
  [7] Performance Reports
  [0] Exit

Enter choice:
```

---

## FLOW 1 — LINEAR DATA STRUCTURES

### 1A. Array Operations

```
User enters: 1   (Linear Structures)

==================================
     LINEAR DATA STRUCTURES
==================================

  [1] Array
  [2] Singly Linked List
  [3] Doubly Linked List
  [4] Circular Linked List
  [0] Back

Enter choice: 1

==================================
         ARRAY MODULE
==================================

  [1] Insert at End
  [2] Insert at Index
  [3] Delete at Index
  [4] Search
  [5] Display
  [0] Back

Enter choice:
```

**Flow 1A-1: Insert at End**

```
Enter choice: 1
Enter value: 50

------------------------------
[Array] Insert: 50 at end
------------------------------
Step 1: BEFORE: [ 10 ][ 20 ][ 30 ][ 40 ]
Step 2: Placing (50) at index 4
Result: AFTER:  [ 10 ][ 20 ][ 30 ][ 40 ][ 50 ]
Performance: Steps=1 | O(1)

Press Enter to continue...
```

**Flow 1A-2: Insert at Index**

```
Enter choice: 2
Enter value: 99
Enter index: 2

------------------------------
[Array] Insert: 99 at index 2
------------------------------
Step 1: BEFORE: [ 10 ][ 20 ][ 30 ][ 40 ]
Step 2: Shifting (40) right → index 4
Step 3: Shifting (30) right → index 3
Step 4: Placing (99) at index 2
Result: AFTER:  [ 10 ][ 20 ][ 99 ][ 30 ][ 40 ]
Performance: Steps=2 | Comparisons=0 | O(n)

Press Enter to continue...
```

**Flow 1A-3: Delete at Index**

```
Enter choice: 3
Enter index: 1

------------------------------
[Array] Delete at index 1
------------------------------
Step 1: BEFORE: [ 10 ][ 20 ][ 30 ][ 40 ]
Step 2: Removing (20) from index 1
Step 3: Shifting [ 30 ] left → index 1
Step 4: Shifting [ 40 ] left → index 2
Result: AFTER:  [ 10 ][ 30 ][ 40 ]
Performance: Steps=2 | O(n)

Press Enter to continue...
```

**Flow 1A-4: Search**

```
Enter choice: 4
Enter value: 30

------------------------------
[Array] Search: 30
------------------------------
Step 1: Checking index 0: [ (10) ][ 20 ][ 30 ][ 40 ] — No match
Step 2: Checking index 1: [ 10 ][ (20) ][ 30 ][ 40 ] — No match
Step 3: Checking index 2: [ 10 ][ 20 ][ (30) ][ 40 ] — Match!
Result: Value 30 found at index 2
Performance: Steps=3 | Comparisons=3 | O(n)

Press Enter to continue...
```

**Edge Case: Invalid Index**

```
Enter index: 99

Error: Invalid index [99], valid range [0..3]

Press Enter to continue...
```

**Edge Case: Empty Array**

```
Error: Structure is empty

Press Enter to continue...
```

---

### 1B. Singly Linked List

```
Enter choice: 2   (Singly Linked List)

==================================
      SINGLY LINKED LIST
==================================

  [1] Insert at Start
  [2] Insert at End
  [3] Delete by Value
  [4] Search
  [5] Display / Traverse
  [0] Back
```

**Flow 1B-1: Insert at Start**

```
Enter value: 5

------------------------------
[SinglyLL] Insert at Start: 5
------------------------------
Step 1: BEFORE: 10 → 20 → 30 → NULL
Step 2: Creating node (5)
Step 3: Linking (5) → 10
Result: AFTER:  (5) → 10 → 20 → 30 → NULL
Performance: Steps=1 | O(1)
```

**Flow 1B-2: Traversal / Display**

```
------------------------------
[SinglyLL] Traversal
------------------------------
Step 1: Visiting (10) → 20 → 30 → NULL
Step 2: Visiting 10 → (20) → 30 → NULL
Step 3: Visiting 10 → 20 → (30) → NULL
Step 4: Reached NULL
Result: Traversal complete. Nodes visited: 3
Performance: Steps=3 | O(n)
```

---

### 1C. Doubly Linked List

**Flow 1C-1: Display**

```
------------------------------
[DoublyLL] Traversal (forward)
------------------------------
Step 1: NULL ← (10) ↔ 20 ↔ 30 → NULL
Step 2: NULL ← 10 ↔ (20) ↔ 30 → NULL
Step 3: NULL ← 10 ↔ 20 ↔ (30) → NULL
Result: Traversal complete. Nodes: 3
```

---

### 1D. Circular Linked List

**Flow 1D-1: Display**

```
------------------------------
[CircularLL] Traversal
------------------------------
Step 1: (10) → 20 → 30 → [back to HEAD]
Step 2: 10 → (20) → 30 → [back to HEAD]
Step 3: 10 → 20 → (30) → [back to HEAD]
Result: Circular traversal complete. Nodes: 3
```

---

## FLOW 2 — STACK & QUEUE

```
Enter choice: 2   (Stack & Queue)

==================================
        STACK & QUEUE
==================================

  [1] Stack (Static)
  [2] Stack (Dynamic)
  [3] Simple Queue
  [4] Circular Queue
  [5] Priority Queue
  [6] Deque
  [0] Back
```

**Flow 2-1: Stack Push**

```
Enter choice: 1   (Static Stack)
Enter choice: 1   (Push)
Enter value: 40

------------------------------
[StaticStack] Push: 40
------------------------------
Step 1: BEFORE:
         [ 30 ] ← TOP
         [ 20 ]
         [ 10 ]
Step 2: Pushing (40) onto top
Result: AFTER:
         [ (40) ] ← TOP
         [ 30 ]
         [ 20 ]
         [ 10 ]
Performance: Steps=1 | O(1)
```

**Flow 2-2: Stack Pop**

```
------------------------------
[StaticStack] Pop
------------------------------
Step 1: BEFORE:
         [ (40) ] ← TOP
         [ 30 ]
         [ 20 ]
Result: Removed (40) from top
        AFTER:
         [ 30 ] ← TOP
         [ 20 ]
         [ 10 ]
Performance: Steps=1 | O(1)
```

**Flow 2-3: Queue Enqueue**

```
------------------------------
[Queue] Enqueue: 50
------------------------------
Step 1: BEFORE: FRONT → [ 10 ][ 20 ][ 30 ] ← REAR
Step 2: Adding (50) at rear
Result: AFTER:  FRONT → [ 10 ][ 20 ][ 30 ][ (50) ] ← REAR
Performance: Steps=1 | O(1)
```

**Flow 2-4: Circular Queue (wrap-around)**

```
------------------------------
[CircularQueue] Enqueue: 99
------------------------------
Step 1: BEFORE: [ 30 ][ _ ][ 10 ][ 20 ]
                  ↑REAR     ↑FRONT
Step 2: Rear wrapping to index 1
Step 3: Inserting (99) at index 1
Result: AFTER:  [ 30 ][ (99) ][ 10 ][ 20 ]
                        ↑REAR   ↑FRONT
```

---

## FLOW 3 — TREES

```
Enter choice: 3

==================================
           TREES
==================================

  [1] Binary Tree
  [2] Binary Search Tree (BST)
  [3] AVL Tree
  [4] Heap (Min/Max)
  [0] Back
```

**Flow 3-1: BST Insert**

```
Enter choice: 2
Enter choice: 1   (Insert)
Enter value: 25

------------------------------
[BST] Insert: 25
------------------------------
Step 1: BEFORE:
             50
            /  \
           30   70
Step 2: 25 < 50 → going left
Step 3: 25 < 30 → going left
Step 4: Left of 30 is empty → inserting (25)
Result: AFTER:
             50
            /  \
           30   70
          /
        (25)
Performance: Steps=2 | O(log n) avg
```

**Flow 3-2: AVL Insert with Rotation**

```
------------------------------
[AVL] Insert: 5
------------------------------
Step 1: BEFORE:
             20
            /
           10
Step 2: Inserting (5) left of 10
Step 3: Checking balance...
        Node 20: balance = +2 (left heavy) — UNBALANCED
Step 4: LL Rotation required
Step 5: Performing LL Rotation...
Result: AFTER:
             10
            /  \
           (5)  20
Performance: Steps=3 | Rotations=1 | O(log n)
```

**Flow 3-3: BST Inorder Traversal**

```
------------------------------
[BST] Inorder Traversal
------------------------------
Step 1: Visit (20) → traversing left subtree
Step 2: Visit (10) → no left child
Step 3: Output: 10
Step 4: Output: 20
Step 5: Traversing right subtree of 20
Step 6: Output: 30
Result: Inorder: 10 → 20 → 30
```

---

## FLOW 4 — GRAPH ALGORITHMS

```
Enter choice: 4

==================================
        GRAPH ALGORITHMS
==================================

  [1] Build Graph
  [2] BFS Traversal
  [3] DFS Traversal
  [4] Dijkstra Shortest Path
  [5] MST — Kruskal
  [6] MST — Prim
  [0] Back
```

**Flow 4-1: BFS**

```
Enter choice: 2
Enter start node: 0

------------------------------
[Graph] BFS from node 0
------------------------------
Step 1: Queue: [(0)]  Visited: [0]
        Exploring neighbors of (0): 1, 2
Step 2: Queue: [(1)(2)]  Visited: [0,1,2]
        Exploring neighbors of (1): 3
Step 3: Queue: [(2)(3)]  Visited: [0,1,2,3]
        Exploring neighbors of (2): none new
Step 4: Queue: [(3)]
        Exploring neighbors of (3): none new
Result: BFS Order: 0 → 1 → 2 → 3
Performance: Steps=8 | O(V+E)
```

**Flow 4-2: Dijkstra**

```
------------------------------
[Graph] Dijkstra from node 0
------------------------------
Step 1: Initial distances: [0:0] [1:∞] [2:∞] [3:∞]
Step 2: Processing (0): Update 1=4, Update 2=1
        Distances: [0:0] [1:4] [2:1] [3:∞]
Step 3: Processing (2): Update 3=3
        Distances: [0:0] [1:4] [2:1] [3:3]
Step 4: Processing (3): Update 1=min(4,5)=4
        Distances: [0:0] [1:4] [2:1] [3:3]
Step 5: Processing (1): No updates
Result: Shortest paths from 0:
        0→1: 4 | 0→2: 1 | 0→3: 3
Performance: Steps=12 | O(V²)
```

---

## FLOW 5 — SEARCHING & SORTING

```
Enter choice: 5

==================================
      SEARCHING & SORTING
==================================

  [1] Linear Search
  [2] Binary Search
  [3] Bubble Sort
  [4] Selection Sort
  [5] Insertion Sort
  [6] Merge Sort
  [7] Quick Sort
  [0] Back
```

**Flow 5-1: Binary Search**

```
Enter choice: 2
Array (sorted): [ 10 ][ 20 ][ 30 ][ 40 ][ 50 ]
Enter value: 30

------------------------------
[BinarySearch] Search: 30
------------------------------
Step 1: left=0 right=4 mid=2
        Array: [ 10 ][ 20 ][ (30) ][ 40 ][ 50 ]
        arr[2]=30 — Match found!
Result: Value 30 found at index 2
Performance: Steps=1 | O(log n)
```

**Flow 5-2: Bubble Sort**

```
------------------------------
[BubbleSort] Sort array
------------------------------
Step 1: BEFORE: [ 40 ][ 10 ][ 30 ][ 20 ]
--- Pass 1 ---
Step 2: Comparing (40) vs (10) → Swap!
        [ (10) ][ (40) ][ 30 ][ 20 ]
Step 3: Comparing (40) vs (30) → Swap!
        [ 10 ][ (30) ][ (40) ][ 20 ]
Step 4: Comparing (40) vs (20) → Swap!
        [ 10 ][ 30 ][ (20) ][ (40) ]
--- Pass 2 ---
Step 5: Comparing (10) vs (30) → No swap
Step 6: Comparing (30) vs (20) → Swap!
        [ 10 ][ (20) ][ (30) ][ 40 ]
--- Pass 3 ---
Step 7: No swaps needed
Result: AFTER:  [ 10 ][ 20 ][ 30 ][ 40 ]
Performance: Steps=6 | Comparisons=6 | O(n²)
```

---

## FLOW 6 — HASHING

```
Enter choice: 6

==================================
           HASHING
==================================

  [1] Chaining
  [2] Linear Probing
  [0] Back

Enter choice: 1   (Chaining)

==================================
      HASH TABLE (Chaining)
==================================
  Table size: 7

  [1] Insert
  [2] Search
  [3] Delete
  [4] Display Table
  [0] Back
```

**Flow 6-1: Hash Insert with Chaining**

```
Enter value: 15

------------------------------
[HashChaining] Insert: 15
------------------------------
Step 1: Hash(15) = 15 % 7 = 1
Step 2: Checking slot [1]...
        Slot [1] has: 8 →
        Collision! Adding to chain.
Step 3: Appending (15) to chain at slot [1]
Result: Slot [1]: 8 → (15) → NULL
Performance: Steps=2 | O(1) avg
```

**Flow 6-2: Linear Probe Insert**

```
Enter value: 22

------------------------------
[HashProbe] Insert: 22
------------------------------
Step 1: Hash(22) = 22 % 7 = 1
Step 2: Probing slot [1] → OCCUPIED (8)
Step 3: Probing slot [2] → OCCUPIED (9)
Step 4: Probing slot [3] → EMPTY
Step 5: Inserting (22) at slot [3]
Result: Inserted at slot [3]
Performance: Steps=3 | O(1) avg / O(n) worst
```

---

## FLOW 7 — PERFORMANCE REPORT

```
Enter choice: 7

==================================
       PERFORMANCE REPORT
==================================

Module          | Operation       | Steps | Compare | Complexity
----------------|-----------------|-------|---------|------------
Array           | InsertAtIndex   |   3   |    0    | O(n)
Array           | Search          |   4   |    4    | O(n)
SinglyLL        | InsertEnd       |   5   |    0    | O(n)
SinglyLL        | Traversal       |   5   |    0    | O(n)
BST             | Insert          |   3   |    3    | O(log n) avg
BubbleSort      | Sort(n=4)       |   6   |    6    | O(n²)
BinarySearch    | Search          |   1   |    1    | O(log n)

Total operations logged: 7

Press Enter to return to menu...
```

---

## FLOW 8 — EXIT

```
Enter choice: 0   (from Main Dashboard)

Thank you for using CDSIAS.
Goodbye.
```

---

## ERROR PATHS — ALL MODULES

These paths apply universally. Every module handles them identically:

```
Scenario: Delete from empty structure
→ Error: Structure is empty

Scenario: Insert beyond capacity (static structures)
→ Error: Structure is full (capacity: 100)

Scenario: Search value not in structure
→ Result: Value 99 not found

Scenario: Access invalid index
→ Error: Invalid index [5], valid range [0..3]

Scenario: Invalid menu input
→ Invalid choice. Please enter a number from the menu.
   (reprompts same menu)
```

---

## NAVIGATION MAP (COMPLETE)

```
Launch
 └── Main Dashboard
      ├── [1] Linear Structures
      │    ├── [1] Array
      │    │    ├── [1] Insert End
      │    │    ├── [2] Insert at Index
      │    │    ├── [3] Delete at Index
      │    │    ├── [4] Search
      │    │    └── [5] Display
      │    ├── [2] Singly LL
      │    │    ├── [1] Insert Start
      │    │    ├── [2] Insert End
      │    │    ├── [3] Delete by Value
      │    │    ├── [4] Search
      │    │    └── [5] Display
      │    ├── [3] Doubly LL (same ops)
      │    └── [4] Circular LL (same ops)
      │
      ├── [2] Stack & Queue
      │    ├── [1] Static Stack → Push/Pop/Peek/Display
      │    ├── [2] Dynamic Stack → Push/Pop/Peek/Display
      │    ├── [3] Simple Queue → Enqueue/Dequeue/Display
      │    ├── [4] Circular Queue → Enqueue/Dequeue/Display
      │    ├── [5] Priority Queue → Insert/ExtractMax/Display
      │    └── [6] Deque → InsertFront/InsertRear/DelFront/DelRear/Display
      │
      ├── [3] Trees
      │    ├── [1] Binary Tree → Insert/Traversals
      │    ├── [2] BST → Insert/Delete/Search/Traversals
      │    ├── [3] AVL → Insert/Delete/Traversals
      │    └── [4] Heap → Insert/ExtractMin/ExtractMax/Display
      │
      ├── [4] Graph
      │    ├── [1] Build Graph
      │    ├── [2] BFS
      │    ├── [3] DFS
      │    ├── [4] Dijkstra
      │    ├── [5] Kruskal MST
      │    └── [6] Prim MST
      │
      ├── [5] Searching & Sorting
      │    ├── [1] Linear Search
      │    ├── [2] Binary Search
      │    ├── [3] Bubble Sort
      │    ├── [4] Selection Sort
      │    ├── [5] Insertion Sort
      │    ├── [6] Merge Sort
      │    └── [7] Quick Sort
      │
      ├── [6] Hashing
      │    ├── [1] Chaining → Insert/Search/Delete/Display
      │    └── [2] Linear Probing → Insert/Search/Delete/Display
      │
      ├── [7] Performance Reports
      └── [0] Exit
```
