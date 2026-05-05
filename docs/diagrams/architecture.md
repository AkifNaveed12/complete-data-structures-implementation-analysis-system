# CDSIAS â€” System Architecture Document

## architecture.md

---

## 1. HIGH-LEVEL SYSTEM ARCHITECTURE

The system is divided into 5 clean, non-overlapping layers. Each layer has one responsibility. No layer talks to a layer it shouldn't.

```mermaid
graph TD
    subgraph CONTROL["ðŸŽ® CONTROL LAYER â€” main.cpp"]
        MENU[Menu Controller]
        NAV[Module Navigator]
    end

    subgraph VISUAL["ðŸŽ¨ VISUALIZATION LAYER â€” visual.h"]
        CLI[CLI Renderer]
        ANIM[Animation Engine - sleep_ms]
        FMT[Output Formatter]
    end

    subgraph CORE["âš™ï¸ CORE LAYER â€” src/core/"]
        LINEAR[Linear DS\nArray Â· SLL Â· DLL Â· CLL]
        SQ[Stack & Queue\nStatic Â· Dynamic Â· Circular Â· Priority Â· Deque]
        TREE[Trees\nBT Â· BST Â· AVL Â· Heap]
        GRAPH[Graph\nBFS Â· DFS Â· Dijkstra Â· MST]
        SS[Searching & Sorting\nLinear Â· Binary Â· Bubble Â· Merge Â· Quick Â· ...]
        HASH[Hashing\nChaining Â· Linear Probe]
    end

    subgraph ANALYSIS["ðŸ“Š ANALYSIS LAYER â€” src/analysis/"]
        PERF[Performance Logger\nperformance.cpp]
        REPORT[Report Generator]
    end

    subgraph DATA["ðŸ-„ï¸ DATA LAYER â€” Future"]
        SQLITE[(SQLite DB)]
    end

    subgraph GUI["ðŸ–¥ï¸ GUI LAYER â€” Future Qt"]
        QTWIN[Qt Main Window]
        QTANIM[Qt Animation Engine]
        QTCHART[Qt Charts]
    end

    MENU --> NAV
    NAV --> LINEAR & SQ & TREE & GRAPH & SS & HASH
    LINEAR & SQ & TREE & GRAPH & SS & HASH --> CLI
    LINEAR & SQ & TREE & GRAPH & SS & HASH --> PERF
    CLI --> ANIM --> FMT
    PERF --> REPORT
    REPORT --> SQLITE
    QTWIN --> LINEAR & SQ & TREE & GRAPH & SS & HASH
    QTANIM --> QTWIN
    QTCHART --> REPORT
```

---

## 2. DETAILED LAYER ARCHITECTURE

```mermaid
graph LR
    subgraph CL["Control Layer"]
        MAIN[main.cpp\nEntry Point]
        MH[Menu Handler\nInput Validation]
        MR[Module Router\nswitch-case dispatch]
    end

    subgraph VL["Visualization Layer"]
        VH[visual.h\nShared Functions]
        PS[printSeparator]
        PH[printHeader]
        PT[printStep]
        PR[printResult]
        PE[printError]
        HL[highlight]
        SL[sleep_ms]
    end

    subgraph AL["Analysis Layer"]
        PC[performance.cpp\nperformance.h]
        LOG[Performance::log]
        REP[Performance::report]
        MEM[In-Memory Store\nvector of LogEntry]
    end

    MAIN --> MH --> MR
    MR --> VH
    MR --> PC
    VH --> PS & PH & PT & PR & PE & HL & SL
    PC --> LOG --> MEM
    MEM --> REP
```

---

## 3. CORE LAYER â€” MODULE DEPENDENCY MAP

```mermaid
graph TD
    CORE[Core Layer\nsrc/core/]

    CORE --> LIN[linear/]
    CORE --> SQ[stack_queue/]
    CORE --> TR[trees/]
    CORE --> GR[graph/]
    CORE --> SORT[searching_sorting/]
    CORE --> HASH[hashing/]

    LIN --> ARR[array.cpp / array.h]
    LIN --> SLL[linked_list.cpp\nSinglyLinkedList]
    LIN --> DLL[linked_list.cpp\nDoublyLinkedList]
    LIN --> CLL[linked_list.cpp\nCircularLinkedList]

    SQ --> STKS[stack.cpp\nStaticStack]
    SQ --> STKD[stack.cpp\nDynamicStack]
    SQ --> QUE[queue.cpp\nSimpleQueue]
    SQ --> CQ[queue.cpp\nCircularQueue]
    SQ --> PQ[queue.cpp\nPriorityQueue]
    SQ --> DQ[deque.cpp\nDeque]

    TR --> BT[binary_tree.cpp]
    TR --> BST[bst.cpp]
    TR --> AVL[avl.cpp]
    TR --> HEAP[heap.cpp\nMinHeap Â· MaxHeap]

    GR --> GREPR[graph.cpp\nAdjList Â· AdjMatrix]
    GR --> BFS[bfs.cpp]
    GR --> DFS[dfs.cpp]
    GR --> DIJ[dijkstra.cpp]
    GR --> MST[mst.cpp\nKruskal Â· Prim]

    SORT --> SRCH[searching.cpp\nLinear Â· Binary]
    SORT --> BUBBLE[sorting.cpp\nBubble]
    SORT --> SEL[sorting.cpp\nSelection]
    SORT --> INS[sorting.cpp\nInsertion]
    SORT --> MERGE[sorting.cpp\nMerge]
    SORT --> QUICK[sorting.cpp\nQuick]

    HASH --> CHAIN[hash_chaining.cpp]
    HASH --> LP[hash_linear_probe.cpp]
```

---

## 4. USER FLOW DIAGRAM

```mermaid
flowchart TD
    START([System Launch]) --> SPLASH[Splash Screen\nCDSIAS â€” Data Structure Visualizer]
    SPLASH --> DASH[Main Dashboard\n8 Module Buttons]

    DASH --> M1[Linear Structures]
    DASH --> M2[Stack & Queue]
    DASH --> M3[Trees]
    DASH --> M4[Graph Algorithms]
    DASH --> M5[Searching & Sorting]
    DASH --> M6[Hashing]
    DASH --> M7[Performance Reports]
    DASH --> EXIT([Exit])

    M1 --> M1OP[Select Structure\nArray Â· SLL Â· DLL Â· CLL]
    M1OP --> M1ACT[Select Operation\nInsert Â· Delete Â· Search Â· Display]

    M2 --> M2OP[Select Structure\nStack Â· Queue Â· CircQ Â· PriorQ Â· Deque]
    M2OP --> M2ACT[Select Operation\nPushÂ·Pop Â· EnqueueÂ·Dequeue Â· etc]

    M3 --> M3OP[Select Tree\nBT Â· BST Â· AVL Â· Heap]
    M3OP --> M3ACT[Select Operation\nInsert Â· Delete Â· Traversal Â· Rotate]

    M4 --> M4OP[Select Algo\nBFS Â· DFS Â· Dijkstra Â· Kruskal Â· Prim]
    M4OP --> M4ACT[Enter Graph\nNodes + Edges]

    M5 --> M5OP[Select Type\nSearching Â· Sorting]
    M5OP --> M5ACT[Select Algorithm]

    M6 --> M6OP[Select Method\nChaining Â· Linear Probe]
    M6OP --> M6ACT[Select Operation\nInsert Â· Search Â· Delete]

    M1ACT & M2ACT & M3ACT & M4ACT & M5ACT & M6ACT --> INPUT[Enter Value / Parameters]
    INPUT --> VIZ[Step-by-Step\nVisualization]
    VIZ --> LOG[Performance Logged\nsteps Â· comparisons Â· complexity]
    LOG --> RESULT[Show Result Message]
    RESULT --> CONT{Continue?}
    CONT -- Yes --> DASH
    CONT -- Same Module --> M1OP
    CONT -- No --> EXIT
```

---

## 5. OPERATION EXECUTION FLOW (LOW LEVEL)

```mermaid
sequenceDiagram
    participant USER as User
    participant MAIN as main.cpp
    participant MOD as Module (e.g. array.cpp)
    participant VIS as visual.h
    participant PERF as performance.cpp

    USER->>MAIN: Selects module + operation + value
    MAIN->>MOD: Calls operation function (e.g. insertAtIndex(3, 99))
    MOD->>VIS: printSeparator()
    MOD->>VIS: printHeader("Array", "Insert at Index 3")
    MOD->>VIS: printStep(1, "BEFORE: [10][20][30][40]")
    MOD->>VIS: sleep_ms(300)
    MOD->>VIS: printStep(2, "Shifting [40] â†’ right")
    MOD->>VIS: sleep_ms(200)
    MOD->>VIS: printStep(3, "Shifting [30] â†’ right")
    MOD->>VIS: sleep_ms(200)
    MOD->>MOD: Internal pointer/index manipulation
    MOD->>VIS: printResult("AFTER: [10][20][30](99)[40]")
    MOD->>PERF: Performance::log("Array", "InsertAtIndex", steps, comparisons)
    PERF-->>MAIN: Logged
    MAIN-->>USER: Returns to menu
```

---

## 6. DATA FLOW DIAGRAM

```mermaid
flowchart LR
    USER([User Input]) --> CTRL[Control Layer\nmain.cpp]
    CTRL --> CORE[Core Layer\nDS Logic]
    CORE --> VIS[Visual Layer\nvisual.h output]
    CORE --> ANA[Analysis Layer\nperformance.cpp]
    VIS --> STDOUT[Console / Qt Widget]
    ANA --> MEM[In-Memory Log]
    MEM --> RPT[Report Display]
    MEM -.->|Future| DB[(SQLite)]
    DB -.->|Future| TEACHER[Teacher Dashboard]
```

---

## 7. FILE DEPENDENCY MAP

```mermaid
graph TD
    MAIN[main.cpp] --> ARR[array.h]
    MAIN --> LL[linked_list.h]
    MAIN --> STK[stack.h]
    MAIN --> QUE[queue.h]
    MAIN --> BST[bst.h]
    MAIN --> AVL[avl.h]
    MAIN --> HEAP[heap.h]
    MAIN --> GR[graph.h]
    MAIN --> SS[searching.h\nsorting.h]
    MAIN --> HASH[hash_chaining.h\nhash_linear_probe.h]
    MAIN --> PERF[performance.h]

    ARR --> VIS[visual.h]
    LL --> VIS
    STK --> VIS
    QUE --> VIS
    BST --> VIS
    AVL --> VIS
    HEAP --> VIS
    GR --> VIS
    SS --> VIS
    HASH --> VIS

    ARR --> PERF
    LL --> PERF
    STK --> PERF
    QUE --> PERF
    BST --> PERF
    AVL --> PERF
    HEAP --> PERF
    GR --> PERF
    SS --> PERF
    HASH --> PERF
```

---

## 8. FUTURE Qt GUI ARCHITECTURE

```mermaid
graph TD
    subgraph QT["Qt Application Layer"]
        QMAIN[QMainWindow\nCDSIAS_Window]
        QSTACK[QStackedWidget\nScreen Manager]
        SPLASH_W[SplashScreen Widget]
        DASH_W[Dashboard Widget]
        MOD_W[Module Widget\nper DS]
        VIZ_W[Visualization Widget\nCustom QPainter canvas]
        PERF_W[Performance Widget\nQChartView]
    end

    subgraph CORE2["Core Layer (unchanged)"]
        COREMOD[All DS Modules]
    end

    QMAIN --> QSTACK
    QSTACK --> SPLASH_W
    QSTACK --> DASH_W
    QSTACK --> MOD_W
    QSTACK --> VIZ_W
    QSTACK --> PERF_W
    MOD_W --> COREMOD
    COREMOD --> VIZ_W
    COREMOD --> PERF_W
```

---

## 9. BUILD ARCHITECTURE

```mermaid
graph LR
    SRC[src/] --> COMP[g++ Compiler\nor CMake]
    TESTS[tests/] --> COMP
    COMP --> BIN[cdsias.exe\nWindows Binary]
    BIN --> RUN[Runtime Execution\nCLI Terminal]
    BIN -.->|Future| QT[Qt Runtime\nGUI Window]
```

---

## 10. LAYER COMMUNICATION RULES

```
â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
â”‚  ALLOWED COMMUNICATION PATHS                           â”‚
â”‚                                                        â”‚
â”‚  Control  â†’  Core         âœ… (call DS operations)      â”‚
â”‚  Core     â†’  Visual       âœ… (output via visual.h)     â”‚
â”‚  Core     â†’  Analysis     âœ… (log via Performance::log) â”‚
â”‚  Control  â†’  Analysis     âœ… (request report)           â”‚
â”‚                                                        â”‚
â”‚  FORBIDDEN PATHS                                       â”‚
â”‚                                                        â”‚
â”‚  Core  â†’  Control         âŒ (DS logic never calls menu)â”‚
â”‚  Visual â†’  Core           âŒ (renderer never triggers DS)â”‚
â”‚  Visual â†’  Analysis       âŒ (output has no logging)    â”‚
â”‚  Analysis â†’ Core          âŒ (logger never calls DS)    â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
```

