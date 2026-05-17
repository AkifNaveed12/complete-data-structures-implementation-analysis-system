#ifndef VISUAL_H
#define VISUAL_H

// ============================================================
//  CDSIAS Visual Layer — visual.h
//  All module output goes through these functions ONLY.
//  No raw cout is allowed in any src/core/ file.
//  contracts.md §1.1, §1.7
//
//  This file supports two modes:
//    - CLI mode:  prints to console (default)
//    - GUI mode:  forwards to GlobalGuiNotifier (set CDSIAS_GUI=1)
// ============================================================

#include <string>

// Colors (still defined, but empty in GUI mode — no ANSI escapes needed)
#ifdef CDSIAS_GUI
  #define COL_ACCENT   ""
  #define COL_SUCCESS  ""
  #define COL_ERROR    ""
  #define COL_WARNING  ""
  #define COL_MUTED    ""
  #define COL_RESET    ""
#else
  #define COL_ACCENT   "\033[96m"
  #define COL_SUCCESS  "\033[92m"
  #define COL_ERROR    "\033[91m"
  #define COL_WARNING  "\033[93m"
  #define COL_MUTED    "\033[90m"
  #define COL_RESET    "\033[0m"
#endif

// ============================================================
//  Function declarations — implemented in visual_qt.cpp (GUI)
//  or as inline functions below (CLI)
// ============================================================

#ifdef CDSIAS_GUI

// --- GUI Mode: just declarations, implemented in visual_qt.cpp ---
void sleep_ms(int ms);
void printSeparator();
void printHeader(const std::string& module, const std::string& op);
void printStep(int n, const std::string& message);
void printResult(const std::string& message);
void printError(const std::string& message);
std::string highlight(const std::string& val);
std::string highlight(int val);
void notifyArrayState(const int* arr, int size, int activeIndex = -1);

#else

// --- CLI Mode: full inline implementations ---
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

inline void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void printSeparator() {
    cout << COL_MUTED << "------------------------------" << COL_RESET << "\n";
}

inline void printHeader(const string& module, const string& op) {
    printSeparator();
    cout << COL_ACCENT << "[" << module << "] " << COL_RESET << op << "\n";
    printSeparator();
}

inline void printStep(int n, const string& message) {
    cout << COL_MUTED << "Step " << n << ": " << COL_RESET << message << "\n";
}

inline void printResult(const string& message) {
    cout << COL_SUCCESS << "Result: " << COL_RESET << message << "\n";
}

inline void printError(const string& message) {
    cout << COL_ERROR << "Error: " << COL_RESET << message << "\n";
}

inline string highlight(const string& val) {
    return "(" + val + ")";
}

inline string highlight(int val) {
    return "(" + to_string(val) + ")";
}

inline void notifyArrayState(const int* arr, int size, int activeIndex = -1) {
    if (size == 0) {
        cout << "[ empty ]\n";
        return;
    }
    string line = "[ ";
    for (int i = 0; i < size; i++) {
        if (i == activeIndex) line += highlight(arr[i]);
        else line += to_string(arr[i]);
        if (i < size - 1) line += " | ";
    }
    line += " ]";
    cout << line << "\n";
}

#endif // CDSIAS_GUI

#endif // VISUAL_H