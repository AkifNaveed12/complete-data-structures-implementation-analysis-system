#ifndef VISUAL_H
#define VISUAL_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// ============================================================
//  CDSIAS Visual Layer — visual.h
//  All module output goes through these functions ONLY.
//  No raw cout is allowed in any src/core/ file.
//  contracts.md §1.1, §1.7
// ============================================================

// ANSI Color codes (Windows terminal / modern console)
#define COL_ACCENT   "\033[96m"   // cyan  — default accent / highlighted elements
#define COL_SUCCESS  "\033[92m"   // green — Result / success messages
#define COL_ERROR    "\033[91m"   // red   — Error messages
#define COL_WARNING  "\033[93m"   // amber — Warnings
#define COL_MUTED    "\033[90m"   // grey  — labels, separators
#define COL_RESET    "\033[0m"    // reset to default

// --------------------------------------------------------
// sleep_ms — platform delay (contracts.md §1.5)
// --------------------------------------------------------
inline void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// --------------------------------------------------------
// printSeparator — 30 dashes (contracts.md §1.3)
// --------------------------------------------------------
inline void printSeparator() {
    cout << COL_MUTED << "------------------------------" << COL_RESET << "\n";
}

// --------------------------------------------------------
// printHeader — [MODULE] Operation: value (contracts.md §1.3)
// --------------------------------------------------------
inline void printHeader(const string& module, const string& op) {
    printSeparator();
    cout << COL_ACCENT << "[" << module << "] " << COL_RESET << op << "\n";
    printSeparator();
}

// --------------------------------------------------------
// printStep — Step N: message (contracts.md §1.3)
// --------------------------------------------------------
inline void printStep(int n, const string& message) {
    cout << COL_MUTED << "Step " << n << ": " << COL_RESET << message << "\n";
}

// --------------------------------------------------------
// printResult — Result: message (contracts.md §1.3)
// --------------------------------------------------------
inline void printResult(const string& message) {
    cout << COL_SUCCESS << "Result: " << COL_RESET << message << "\n";
}

// --------------------------------------------------------
// printError — Error: message (contracts.md §1.6)
// --------------------------------------------------------
inline void printError(const string& message) {
    cout << COL_ERROR << "Error: " << COL_RESET << message << "\n";
}

// --------------------------------------------------------
// highlight — wraps a value in parentheses: "(val)"
// contracts.md §1.4
// --------------------------------------------------------
inline string highlight(const string& val) {
    return "(" + val + ")";
}

inline string highlight(int val) {
    return "(" + to_string(val) + ")";
}

#endif