// ============================================================
//  CDSIAS — visual_qt.cpp
//  Qt-mode implementations of the visual.h contract functions.
//  Compiled only when CDSIAS_GUI=1 is defined.
//  Routes all output through GlobalGuiNotifier signals.
// ============================================================

#include "GlobalGuiNotifier.h"
#include <QEventLoop>
#include <QTimer>
#include <QCoreApplication>
#include <string>

// --------------------------------------------------------
// sleep_ms — asynchronous sleep via QEventLoop so Qt
//            can process events (redraw) during delays.
// --------------------------------------------------------
void sleep_ms(int ms) {
    // First signal the state change so GUI can redraw
    GlobalGuiNotifier::instance()->notifyStateChanged();

    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

// --------------------------------------------------------
// printSeparator — visual only, no-op in GUI (log panel
//                 renders its own dividers)
// --------------------------------------------------------
void printSeparator() {
    // No-op in GUI mode
}

// --------------------------------------------------------
// printHeader — signals the module + operation start
// --------------------------------------------------------
void printHeader(const std::string& module, const std::string& op) {
    GlobalGuiNotifier::instance()->notifyHeader(
        QString::fromStdString(module),
        QString::fromStdString(op)
    );
}

// --------------------------------------------------------
// printStep — signals each algorithm step
// --------------------------------------------------------
void printStep(int n, const std::string& message) {
    GlobalGuiNotifier::instance()->notifyStep(n, QString::fromStdString(message));
}

// --------------------------------------------------------
// printResult — signals the final result
// --------------------------------------------------------
void printResult(const std::string& message) {
    GlobalGuiNotifier::instance()->notifyResult(QString::fromStdString(message));
    GlobalGuiNotifier::instance()->notifyStateChanged();
}

// --------------------------------------------------------
// printError — signals an error condition
// --------------------------------------------------------
void printError(const std::string& message) {
    GlobalGuiNotifier::instance()->notifyError(QString::fromStdString(message));
}

// --------------------------------------------------------
// highlight — string wrapper, same as CLI
// --------------------------------------------------------
std::string highlight(const std::string& val) {
    return "(" + val + ")";
}

std::string highlight(int val) {
    return "(" + std::to_string(val) + ")";
}

// --------------------------------------------------------
// notifyArrayState — signals the array visualization state
// --------------------------------------------------------
void notifyArrayState(const int* arr, int size, int activeIndex) {
    GlobalGuiNotifier::instance()->notifyArrayState(arr, size, activeIndex);
}
