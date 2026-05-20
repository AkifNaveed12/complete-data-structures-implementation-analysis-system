# Data Flow Diagrams (DFD) for CDSIAS

This document outlines the Data Flow Diagrams for the **Complete Data Structures Implementation & Analysis System (CDSIAS)**. These diagrams trace how information flows from the user interface, through the execution engine, and into the visual/analytical outputs.

## Level 0: Context Diagram
The Level 0 DFD (Context Diagram) shows the system as a single high-level process interacting with external entities (the User).

```mermaid
flowchart TD
    User[/User/]
    System((0.0\nCDSIAS System))

    User -- "Select Data Structure & Operation\nProvide Input Data (Values, Nodes, Edges)" --> System
    System -- "Visual Animations & State Rendering\nStep-by-step Operation Logs\nComplexity & Performance Reports" --> User
```

---

## Level 1: System Level DFD
The Level 1 DFD decomposes the system into main functional sub-processes: Input Dispatch, the Core DS Engine, the Visualization Renderer, and the Performance Analytics Engine.

```mermaid
flowchart TD
    User[/User/]
    
    P1((1.0\nInput Processing\n& Dispatch))
    P2((2.0\nCore Data Structure\nEngine))
    P3((3.0\nVisualization &\nUI Renderer))
    P4((4.0\nPerformance\nAnalytics Engine))
    
    DS1[(D1. DS Internal Memory State)]
    DS2[(D2. Performance Metrics Store)]

    User -- "UI Events (Select Module, Run Op)" --> P1
    P1 -- "Op Type, Parameters" --> P2
    
    P2 <-- "Read/Update State" --> DS1
    P2 -- "Emit State Changes\n(GlobalGuiNotifier)" --> P3
    P2 -- "Execution Data\n(Steps, Comparisons, Complexity)" --> P4
    
    P4 -- "Store Metrics" --> DS2
    
    DS2 -- "Retrieve Analytics" --> P3
    P3 -- "Render Canvas\nShow Logs\nUpdate Tables" --> User
```

---

## Level 2: Data Structure Engine (Decomposition of Process 2.0)
This level dives deeper into how the Core Engine routes operations to specific algorithm handlers and interacts with the Global Event Bus.

```mermaid
flowchart TD
    Input>Operation Request from Process 1.0]
    
    P2_1((2.1\nLinear DS\nOperations))
    P2_2((2.2\nTree & Graph\nOperations))
    P2_3((2.3\nSorting & Searching\nOperations))
    
    State[(D1. Active DS State)]
    Notifier>GlobalGuiNotifier\nEvent Bus]
    Metrics[(D2. Performance Store)]
    
    Input -->|Stack, Queue, Array, LL| P2_1
    Input -->|BST, AVL, Heap, Graphs| P2_2
    Input -->|Sort, Search Algorithms| P2_3
    
    P2_1 <-- "Modify/Access Memory" --> State
    P2_2 <-- "Modify/Access Nodes/Edges" --> State
    P2_3 <-- "Modify/Access Array Data" --> State
    
    P2_1 -- "Log step, Snapshot Canvas" --> Notifier
    P2_2 -- "Highlight Node/Edge Traversal" --> Notifier
    P2_3 -- "Visual Swaps, Comparisons" --> Notifier
    
    P2_1 -- "Metrics (Steps: 1, Comparisons: 0)" --> Metrics
    P2_2 -- "Metrics (O(log n), O(V+E))" --> Metrics
    P2_3 -- "Metrics (O(n log n), O(n^2))" --> Metrics
```

---

## Level 2: Visualization & Reporting System (Decomposition of Processes 3.0 & 4.0)
This diagram details how the event bus updates the specific GUI components and how the performance store generates the final report.

```mermaid
flowchart TD
    Bus>GlobalGuiNotifier\nEvent Bus]
    Metrics[(D2. Performance Metrics Store)]
    
    P3_1((3.1\nCanvas Renderer))
    P3_2((3.2\nOperation Log Manager))
    P4_1((4.1\nPerformance Report\nGenerator))
    
    UI_Canvas[/Visual Canvas Display/]
    UI_Log[/Operation Log Panel/]
    UI_Report[/Analytics Data Table/]
    
    Bus -- "State Snapshot Event" --> P3_1
    P3_1 -- "Draw Nodes/Edges/Array States" --> UI_Canvas
    
    Bus -- "Log/Result Event" --> P3_2
    P3_2 -- "Append Rich Text Log\n(Calculate Operation Count)" --> UI_Log
    
    Metrics -- "Raw Execution Data" --> P4_1
    P4_1 -- "Aggregate & Format Row\nCalculate Time Complexity" --> UI_Report
```
