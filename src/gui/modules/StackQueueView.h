#ifndef STACK_QUEUE_VIEW_H
#define STACK_QUEUE_VIEW_H

#include "../modules/ModulePanel.h"
#include "../../core/stack_queue/stack.h"
#include "../../core/stack_queue/queue.h"
#include "../GlobalGuiNotifier.h"
#include <QComboBox>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QThread>

// ─── StackCanvas ──────────────────────────────────────────────────────────────
class StackCanvas : public QWidget {
    Q_OBJECT
public:
    explicit StackCanvas(QWidget* p = nullptr);
    void updateState(const QVector<int>& vals, int activeIdx = -1);
    void clear();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    QVector<int> m_vals;
    int m_activeIdx = -1;
    static const int CELL_H = 50;
    static const int CELL_W = 120;
};

// ─── QueueCanvas ─────────────────────────────────────────────────────────────
class QueueCanvas : public QWidget {
    Q_OBJECT
public:
    explicit QueueCanvas(QWidget* p = nullptr);
    void updateState(const QVector<int>& vals, int activeIdx = -1);
    void clear();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    QVector<int> m_vals;
    int m_activeIdx = -1;
    static const int CELL_W = 60;
    static const int CELL_H = 54;
};

// ─── Workers ─────────────────────────────────────────────────────────────────
class StackWorker : public QObject {
    Q_OBJECT
public:
    enum StackType { StaticT, DynamicT };
    enum Op { Push, Pop, Peek, Display };
    StackWorker(void* s, StackType t, Op op, int val = 0)
        : m_s(s), m_t(t), m_op(op), m_val(val) {}
public slots: void run();
signals:     void finished();
private: void* m_s; StackType m_t; Op m_op; int m_val;
};

class QueueWorker : public QObject {
    Q_OBJECT
public:
    enum QueueType { SimpleT, CircularT, PriorityT, DequeT };
    enum Op { Enqueue, Dequeue, Peek, Display, InsertFront, InsertRear, DeleteFront, DeleteRear };
    QueueWorker(void* q, QueueType t, Op op, int val = 0, int prio = 0)
        : m_q(q), m_t(t), m_op(op), m_val(val), m_prio(prio) {}
public slots: void run();
signals:     void finished();
private: void* m_q; QueueType m_t; Op m_op; int m_val; int m_prio;
};

// ─── Main View ────────────────────────────────────────────────────────────────
class StackQueueView : public QWidget {
    Q_OBJECT
public:
    explicit StackQueueView(QWidget* parent = nullptr);

private slots:
    void onDSTypeChanged(int idx);
    void onOpSelected(int row);
    void onRun();
    void onReset();
    void onWorkerFinished();

private:
    void setupStackOps();
    void setupQueueOps();
    void setRunning(bool r);
    void refreshCanvas();

    QComboBox*   m_typeCombo;
    ModulePanel* m_panel;
    StackCanvas* m_stackCanvas;
    QueueCanvas* m_queueCanvas;

    StaticStack*   m_staticStack;
    DynamicStack*  m_dynamicStack;
    SimpleQueue*   m_simpleQueue;
    CircularQueue* m_circularQueue;
    PriorityQueue* m_priorityQueue;
    Deque*         m_deque;

    int      m_dsIndex = 0;   // 0=StaticStack, 1=DynStack, 2=SimpleQ, 3=CircQ, 4=PrioQ, 5=Deque
    QThread* m_thread = nullptr;
};

#endif
