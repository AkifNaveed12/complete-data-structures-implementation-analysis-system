# Activity Diagrams for CDSIAS

This document contains the Activity Diagrams illustrating the typical workflow and user interactions within the **Complete Data Structures Implementation & Analysis System (CDSIAS)**.

## High-Level User Session Workflow
This diagram represents the step-by-step activity flow from the moment the user launches the application to executing a data structure operation.

```mermaid
stateDiagram-v2
    [*] --> LaunchApplication
    
    LaunchApplication --> SelectModule: Click Sidebar Navigation
    
    SelectModule --> ConfigureDataStructure: Choose Specific DS (e.g., Dynamic Stack, AVL Tree)
    ConfigureDataStructure --> SelectOperation: Select Op (Push, Pop, Insert, Delete)
    SelectOperation --> InputParameters: Enter Node Value, Edge Weight, etc.
    
    InputParameters --> ValidateInput: Click "Run" Button
    
    ValidateInput --> InvalidInput: Validation Fails
    InvalidInput --> SelectOperation: Display Error Message
    
    ValidateInput --> RunExecution: Validation Succeeds
    
    state RunExecution {
        [*] --> SpawnWorkerThread
        SpawnWorkerThread --> ExecuteCoreAlgorithm: Call Backend C++ function
        
        ExecuteCoreAlgorithm --> EmitStepLogs
        ExecuteCoreAlgorithm --> EmitStateChanges
        ExecuteCoreAlgorithm --> LogPerformanceMetrics
        
        EmitStepLogs --> [*]
        EmitStateChanges --> [*]
        LogPerformanceMetrics --> [*]
    }
    
    RunExecution --> UpdateUIComponents
    
    state UpdateUIComponents {
        [*] --> RedrawCanvas
        [*] --> AppendRichTextLogs
        [*] --> UpdatePerformanceTable
    }
    
    UpdateUIComponents --> AwaitNextAction: Operation Complete
    
    AwaitNextAction --> SelectOperation: Continue same DS
    AwaitNextAction --> SelectModule: Switch to new module
    AwaitNextAction --> [*]: Exit Application
```

---

## Detailed Backend Execution Activity
This diagram dives deeper into how a specific core algorithm execution behaves internally.

```mermaid
stateDiagram-v2
    [*] --> StartAlgorithm
    
    StartAlgorithm --> PreConditionCheck: e.g., Is Stack Full? Is Queue Empty?
    
    PreConditionCheck --> ThrowUnderflowOverflow: Condition Fails
    ThrowUnderflowOverflow --> LogErrorResult
    LogErrorResult --> [*]: Terminate Op Early
    
    PreConditionCheck --> PerformOperation: Condition Met
    
    PerformOperation --> UpdateMemoryPointers: Modify array/nodes
    PerformOperation --> IncrementOperationCount: Track global success count
    
    UpdateMemoryPointers --> BroadcastState: Send state array to Notifier
    IncrementOperationCount --> LogResult: Append final status & Op Count
    
    BroadcastState --> CompileMetrics
    LogResult --> CompileMetrics
    
    CompileMetrics --> SendToPerformanceEngine: Calculate Time Complexity
    SendToPerformanceEngine --> [*]: Algorithm Finished
```
