#ifndef ARRAY_VIEW_H
#define ARRAY_VIEW_H

// ============================================================
//  ArrayView — GUI panel for Array operations.
//  Uses ModulePanel as the shell.
//  design.md §5.1
// ============================================================

#include "ModulePanel.h"
#include "../../core/linear/array.h"
#include "../../gui/GlobalGuiNotifier.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QThread>
#include <QVector>

class ArrayCanvas : public QWidget {
    Q_OBJECT
public:
    explicit ArrayCanvas(QWidget* parent = nullptr);

    void updateState(const int* arr, int size, int activeIndex = -1);
    void clear();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<int> m_values;
    int m_activeIndex = -1;
    QString m_accent = "#4FC3F7";
    static const int CELL_W = 64;
    static const int CELL_H = 64;
    static const int MARGIN  = 40;
};

// Worker to run Array core logic in a background thread
class ArrayWorker : public QObject {
    Q_OBJECT
public:
    enum Op { InsertEnd, InsertAt, DeleteAt, Search, Display };
    ArrayWorker(Array* arr, Op op, int v1 = 0, int v2 = 0)
        : m_arr(arr), m_op(op), m_v1(v1), m_v2(v2) {}

public slots:
    void run();

signals:
    void finished();

private:
    Array* m_arr;
    Op     m_op;
    int    m_v1, m_v2;
};

class ArrayView : public ModulePanel {
    Q_OBJECT
public:
    explicit ArrayView(QWidget* parent = nullptr);

private slots:
    void onRun();
    void onReset();
    void onArrayState(const int* arr, int size, int activeIndex);
    void onStep(int n, const QString& msg);
    void onResult(const QString& msg);
    void onError(const QString& msg);
    void onHeader(const QString& module, const QString& op);
    void onWorkerFinished();
    void onOpSelected(int row);

private:
    void setupOps();
    void setRunning(bool running);

    Array*       m_array;
    ArrayCanvas* m_arrayCanvas;
    QThread*     m_thread = nullptr;
    ArrayWorker* m_worker = nullptr;
};

#endif
