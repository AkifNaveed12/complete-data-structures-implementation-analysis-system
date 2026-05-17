#ifndef TREE_VIEW_H
#define TREE_VIEW_H

#include "../modules/ModulePanel.h"
#include "../../core/trees/bt.h"
#include "../../core/trees/bst.h"
#include "../../core/trees/avl.h"
#include "../../core/trees/heap.h"
#include "../GlobalGuiNotifier.h"
#include <QWidget>
#include <QPainter>
#include <QComboBox>
#include <QThread>
#include <QVector>

// ─── TreeCanvas: draws any binary tree from its root ─────────────────────────
class TreeCanvas : public QWidget {
    Q_OBJECT
public:
    explicit TreeCanvas(QWidget* p = nullptr);
    void setRoot(TreeNode* root);
    void setHeapData(const QVector<int>& data, bool isMin);
    void clear();
protected:
    void paintEvent(QPaintEvent*) override;
private:
    void drawNode(QPainter& p, TreeNode* node, int x, int y, int spread, int depth, int activeVal);
    void drawHeap(QPainter& p);
    TreeNode*    m_root    = nullptr;
    QVector<int> m_heap;
    bool         m_isMin  = true;
    bool         m_heapMode = false;
    QString      m_accent = "#81C784";
    static const int NODE_R = 22;
    static const int LEVEL_H = 70;
};

// ─── Workers ─────────────────────────────────────────────────────────────────
class TreeWorker : public QObject {
    Q_OBJECT
public:
    enum TreeType { BT_T, BST_T, AVL_T, HEAP_T };
    enum Op { Insert, Remove, Search, Display, Extract };
    TreeWorker(void* t, TreeType tt, Op op, int val = 0)
        : m_t(t), m_tt(tt), m_op(op), m_val(val) {}
public slots: void run();
signals:     void finished();
private: void* m_t; TreeType m_tt; Op m_op; int m_val;
};

// ─── TreeView: main widget ────────────────────────────────────────────────────
class TreeView : public QWidget {
    Q_OBJECT
public:
    explicit TreeView(QWidget* parent = nullptr);
private slots:
    void onTreeTypeChanged(int idx);
    void onOpSelected(int row);
    void onRun();
    void onReset();
    void onWorkerFinished();
    void onStateChanged();
private:
    void setupBTOps();
    void setupBSTOps();
    void setupAVLOps();
    void setupHeapOps();
    void setRunning(bool r);

    QComboBox*   m_typeCombo;
    ModulePanel* m_panel;
    TreeCanvas*  m_canvas;

    BinaryTree*       m_bt;
    BinarySearchTree* m_bst;
    AVLTree*          m_avl;
    Heap*             m_minHeap;
    Heap*             m_maxHeap;

    int      m_treeIndex = 0;
    QThread* m_thread    = nullptr;
};

#endif
