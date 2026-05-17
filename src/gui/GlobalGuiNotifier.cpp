#include "GlobalGuiNotifier.h"

GlobalGuiNotifier* GlobalGuiNotifier::instance() {
    static GlobalGuiNotifier inst;
    return &inst;
}

void GlobalGuiNotifier::notifyStep(int stepNum, const QString& message) {
    emit stepLogged(stepNum, message);
}

void GlobalGuiNotifier::notifyHeader(const QString& module, const QString& op) {
    emit headerLogged(module, op);
}

void GlobalGuiNotifier::notifyResult(const QString& message) {
    emit resultLogged(message);
}

void GlobalGuiNotifier::notifyError(const QString& message) {
    emit errorLogged(message);
}

void GlobalGuiNotifier::notifyStateChanged() {
    emit stateChanged();
}

void GlobalGuiNotifier::notifyArrayState(const int* arr, int size, int activeIndex) {
    emit arrayStateChanged(arr, size, activeIndex);
}
