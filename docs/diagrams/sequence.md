# Sequence Diagrams for CDSIAS

This document contains Sequence Diagrams that map out the chronological interactions between the frontend GUI, multithreaded workers, the global event bus, and the core backend data structures of the **Complete Data Structures Implementation & Analysis System (CDSIAS)**.

## Core Operation Execution Sequence
This diagram illustrates the lifecycle of a single operation (e.g., Push, Enqueue, Insert Edge), showing how the UI spawns a background thread to keep the interface responsive while the C++ backend calculates and emits events.

```mermaid
sequenceDiagram
    autonumber
    actor User
    participant UI as ModuleView (GUI)
    participant Thread as QThread (Worker)
    participant Core as CoreDataStructure Engine
    participant Notifier as GlobalGuiNotifier
    participant Perf as PerformanceLogger

    User->>UI: Selects Operation (e.g. Push)
    User->>UI: Inputs Data Value & Clicks "Run"
    
    UI->>UI: Validate User Input
    UI->>UI: setRunning(true) & Lock UI Controls
    UI->>Thread: Instantiate Worker & Move to QThread
    UI->>Thread: thread->start()
    
    activate Thread
    Thread->>Core: Execute DS Operation (e.g., stack.push(val))
    activate Core
    
    %% Step Logging
    Core->>Notifier: printStep(1, "Before operation...")
    Notifier-->>UI: emit stepLogged(msg)
    UI->>UI: Append Step to Operation Log
    
    %% Core Processing
    Core->>Core: Modify Memory Array / Pointers
    Core->>Core: Increment g_sqOperationCount (if applicable)
    
    %% Result Logging
    Core->>Notifier: printResult("Value inserted\nOperation Count: X")
    Notifier-->>UI: emit resultLogged(msg)
    UI->>UI: Append Bold Result to Operation Log
    
    %% Visual State Update
    Core->>Notifier: emit stateChanged()
    Notifier-->>UI: emit stateChanged()
    UI->>UI: Fetch Snapshot & Redraw Canvas
    
    %% Performance Tracking
    Core->>Perf: log("Stack", "Push", steps, comparisons)
    activate Perf
    Perf->>Perf: Calculate Complexity
    Perf-->>Core: Acknowledge Metric Stored
    deactivate Perf
    
    Core-->>Thread: Return Control
    deactivate Core
    
    Thread-->>UI: emit finished()
    deactivate Thread
    
    UI->>UI: setRunning(false) & Unlock UI Controls
    UI->>Thread: thread->deleteLater()
    UI-->>User: Visuals & Logs fully updated
```

---

## GlobalGuiNotifier Event Propagation Sequence
This diagram focuses purely on the pub-sub architecture of the system using the Singleton `GlobalGuiNotifier` to decouple the backend engines from Qt UI.

```mermaid
sequenceDiagram
    participant Algorithm as Backend Algorithm (e.g. Dijkstra)
    participant Notifier as GlobalGuiNotifier (Singleton)
    participant LogPanel as ModulePanel (Log UI)
    participant Canvas as GraphView (Canvas UI)

    Algorithm->>Algorithm: Evaluate Adjacency Matrix
    
    Algorithm->>Notifier: printStep(N, "Checking Node V")
    activate Notifier
    Notifier->>LogPanel: emit stepLogged("Checking Node V")
    LogPanel->>LogPanel: Render HTML text
    deactivate Notifier
    
    Algorithm->>Notifier: activeVertex(V)
    activate Notifier
    Notifier->>Canvas: emit activeNodeChanged(V)
    Canvas->>Canvas: Highlight Node V in Yellow
    deactivate Notifier
    
    Algorithm->>Algorithm: Update Minimum Distance array
    
    Algorithm->>Notifier: emit stateChanged()
    activate Notifier
    Notifier->>Canvas: emit stateChanged()
    Canvas->>Canvas: Redraw all edges and nodes
    deactivate Notifier
```
