#ifndef LINKEDLIST_VIEW_H
#define LINKEDLIST_VIEW_H

#include "../modules/ModulePanel.h"
#include "../../core/linear/linked_list.h"
#include "../GlobalGuiNotifier.h"
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QString>
#include <QThread>
#include <QComboBox>
#include <QLabel>

// ─── Canvas ───────────────────────────────────────────────────────────────────
class LLCanvas : public QWidget {
    Q_OBJECT
public:
    enum Type { Singly, Doubly, Circular };

    explicit LLCanvas(QWidget* parent = nullptr);
    void updateState(const QVector<int>& vals, int activeIdx = -1, Type t = Singly);
    void clear();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QVector<int> m_vals;
    int          m_activeIdx = -1;
    Type         m_type      = Singly;
    QString      m_accent    = "#4FC3F7";
    static const int NODE_W  = 56;
    static const int NODE_H  = 48;
    static const int GAP     = 32;
};

// ─── Worker ───────────────────────────────────────────────────────────────────
class LLWorker : public QObject {
    Q_OBJECT
public:
    enum ListType { SinglyT, DoublyT, CircularT };
    enum Op       { InsertStart, InsertEnd, Delete, Search, Display };

    LLWorker(void* list, ListType lt, Op op, int val = 0)
        : m_list(list), m_lt(lt), m_op(op), m_val(val) {}

public slots:
    void run();
signals:
    void finished();

private:
    void*    m_list;
    ListType m_lt;
    Op       m_op;
    int      m_val;
};

// ─── View ─────────────────────────────────────────────────────────────────────
class LinkedListView : public QWidget {
    Q_OBJECT
public:
    explicit LinkedListView(QWidget* parent = nullptr);

private slots:
    void onListTypeChanged(int idx);
    void onOpSelected(int row);
    void onRun();
    void onReset();
    void onWorkerFinished();

private:
    void rebuildCurrentView();
    void setRunning(bool r);

    // Subwidgets
    QComboBox*  m_typeCombo;
    ModulePanel* m_panel;
    LLCanvas*   m_canvas;

    // Data structures (one per type, persistent)
    LinkedList*         m_singly;
    DoublyLinkedList*   m_doubly;
    CircularLinkedList* m_circular;

    LLCanvas::Type m_curType = LLCanvas::Singly;

    QThread*  m_thread = nullptr;
    LLWorker* m_worker = nullptr;
};

#endif
