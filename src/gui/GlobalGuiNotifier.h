#ifndef GLOBAL_GUI_NOTIFIER_H
#define GLOBAL_GUI_NOTIFIER_H

#include <QObject>
#include <QString>

class GlobalGuiNotifier : public QObject {
    Q_OBJECT
public:
    static GlobalGuiNotifier* instance();

    void notifyStep(int stepNum, const QString& message);
    void notifyHeader(const QString& module, const QString& op);
    void notifyResult(const QString& message);
    void notifyError(const QString& message);
    void notifyStateChanged();
    void notifyArrayState(const int* arr, int size, int activeIndex);

signals:
    void stepLogged(int stepNum, const QString& message);
    void headerLogged(const QString& module, const QString& op);
    void resultLogged(const QString& message);
    void errorLogged(const QString& message);
    void stateChanged(); // triggers redraw of canvas
    void arrayStateChanged(const int* arr, int size, int activeIndex);

private:
    GlobalGuiNotifier(QObject* parent = nullptr) : QObject(parent) {}
};

#endif
