# CDSIAS Project Context

## Project Overview

CDSIAS is a Data Structures Implementation & Analysis System built in C++.

It provides:

- Manual implementations (no STL)
- CLI-based visualization
- Performance tracking
- Modular architecture

---

## Folder Structure

cdsias-dsa-engine/
│
├── src/
│ ├── core/
│ │ ├── linear/
│ │ │ ├── array.cpp
│ │ │ ├── linked_list.cpp
│ │
│ ├── analysis/
│ │ ├── performance.cpp
│ │ ├── visual.h
│ │
│ ├── gui/ (future Qt GUI)
│ ├── main.cpp
│
├── tests/
│ ├── test_array.cpp
│ ├── test_linked_list.cpp

---

## Implemented Modules

### Array

- Insert (end, position)
- Delete
- Search
- Display
- CLI visualization (shifting animation)

### Linked List

- Insert (start, end)
- Delete by value
- Search
- Display
- CLI traversal visualization

---

## Performance Module

- Logs steps for operations
- Tracks complexity behavior

---

## Visualization System

- Uses delays (sleep_ms)
- Highlights active elements
- Shows step transitions

---

## System Flow

User → Main Menu → Module Selection → Operation → Visualization → Performance Log

---

## Future Work

- Qt GUI implementation
- SQLite integration
- Teacher-Student system
