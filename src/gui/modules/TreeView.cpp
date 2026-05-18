#include "TreeView.h"
#include <QPainter>
#include <QPen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <cmath>
#include <QRegularExpression>

// ─────────────────────────────────────────────────────────────────────────────
// TreeCanvas
// ─────────────────────────────────────────────────────────────────────────────
TreeCanvas::TreeCanvas(QWidget* p) : QWidget(p) { setMinimumHeight(300); }

void TreeCanvas::setRoot(TreeNode* root) {
    m_root = root; m_heapMode = false; update();
}
void TreeCanvas::setHeapData(const QVector<int>& data, bool isMin) {
    m_heap = data; m_isMin = isMin; m_heapMode = true; update();
}
void TreeCanvas::clear() {
    m_root = nullptr; m_heap.clear(); m_heapMode = false; update();
}

void TreeCanvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (m_heapMode) { drawHeap(p); return; }

    if (!m_root) {
        p.setPen(QColor("#444466"));
        p.setFont(QFont("Consolas", 13, QFont::Normal, true));
        p.drawText(rect(), Qt::AlignCenter, "[ Tree is Empty ]");
        return;
    }

    drawNode(p, m_root, width() / 2, 40, width() / 4, 0, m_activeVal);
}

void TreeCanvas::drawNode(QPainter& p, TreeNode* node, int x, int y, int spread, int depth, int activeVal) {
    if (!node) return;

    const int maxDepth = 8;
    if (depth > maxDepth) return;

    // Draw edges to children first
    if (node->left) {
        int cx = x - spread;
        int cy = y + LEVEL_H;
        p.setPen(QPen(QColor("#2A2A3E"), 1));
        p.drawLine(x, y, cx, cy);
        drawNode(p, node->left, cx, cy, spread / 2 > 20 ? spread / 2 : 20, depth + 1, activeVal);
    }
    if (node->right) {
        int cx = x + spread;
        int cy = y + LEVEL_H;
        p.setPen(QPen(QColor("#2A2A3E"), 1));
        p.drawLine(x, y, cx, cy);
        drawNode(p, node->right, cx, cy, spread / 2 > 20 ? spread / 2 : 20, depth + 1, activeVal);
    }

    // Node circle
    bool isActive = (node->data == activeVal);
    QColor fill   = isActive ? QColor("#1A3020") : QColor("#1E1E2E");
    QColor border = isActive ? QColor(m_accent) : QColor("#81C784");

    p.setBrush(fill);
    p.setPen(QPen(border, isActive ? 2 : 1));
    p.drawEllipse(QPoint(x, y), NODE_R, NODE_R);

    // Value text
    p.setFont(QFont("Consolas", 10, QFont::Medium));
    p.setPen(QColor(m_accent));
    p.drawText(QRect(x - NODE_R, y - NODE_R, NODE_R * 2, NODE_R * 2),
               Qt::AlignCenter, QString::number(node->data));

    // AVL BF indicator (for AVL trees, node height is updated)
    int hl = node->left ? node->left->height : 0;
    int hr = node->right ? node->right->height : 0;
    int bf = hl - hr;
    
    // Only show BF if we are in AVL mode (we can guess by checking if heights are being maintained > 0)
    // Actually all TreeNode constructors set height=1. So we can just show BF always, it's 0 for BT/BST.
    if (node->height > 0) {
        p.setFont(QFont("Segoe UI", 8, QFont::Bold));
        QColor bfColor = (bf > 1 || bf < -1) ? QColor("#FF5370") : QColor("#8888aa");
        p.setPen(bfColor);
        p.drawText(x + NODE_R + 2, y - NODE_R + 10, QString("BF:%1").arg(bf));
    }
}

void TreeCanvas::drawHeap(QPainter& p) {
    if (m_heap.isEmpty()) {
        p.setPen(QColor("#444466"));
        p.setFont(QFont("Consolas", 13, QFont::Normal, true));
        p.drawText(rect(), Qt::AlignCenter, "[ Heap is Empty ]");
        return;
    }

    int n = m_heap.size();
    // Calculate positions level by level
    int levels = 0;
    int tmp = n;
    while (tmp > 0) { levels++; tmp /= 2; }

    struct Pos { int x; int y; };
    QVector<Pos> pos(n);

    int level = 0, count = 0;
    while (count < n) {
        int nodes_in_level = 1 << level;
        int spread = width() / (nodes_in_level + 1);
        for (int j = 0; j < nodes_in_level && count < n; j++, count++) {
            pos[count] = { (j + 1) * spread, 40 + level * 70 };
        }
        level++;
    }

    // Draw edges
    p.setPen(QPen(QColor("#2A2A3E"), 1));
    for (int i = 0; i < n; i++) {
        int lc = 2*i+1, rc = 2*i+2;
        if (lc < n) p.drawLine(pos[i].x, pos[i].y, pos[lc].x, pos[lc].y);
        if (rc < n) p.drawLine(pos[i].x, pos[i].y, pos[rc].x, pos[rc].y);
    }

    // Draw nodes
    QColor accent("#81C784");
    for (int i = 0; i < n; i++) {
        bool isRoot = (i == 0);
        p.setBrush(isRoot ? QColor("#1A2A10") : QColor("#1E1E2E"));
        p.setPen(QPen(accent, isRoot ? 2 : 1));
        p.drawEllipse(QPoint(pos[i].x, pos[i].y), 22, 22);

        p.setFont(QFont("Consolas", 10, QFont::Medium));
        p.setPen(accent);
        p.drawText(QRect(pos[i].x - 22, pos[i].y - 22, 44, 44),
                   Qt::AlignCenter, QString::number(m_heap[i]));
    }

    // Label
    p.setFont(QFont("Segoe UI", 10));
    p.setPen(QColor("#81C784"));
    p.drawText(8, 20, m_isMin ? "Min-Heap" : "Max-Heap");
}

// ─────────────────────────────────────────────────────────────────────────────
// TreeWorker
// ─────────────────────────────────────────────────────────────────────────────
void TreeWorker::run() {
    if (m_tt == BT_T) {
        auto* t = static_cast<BinaryTree*>(m_t);
        if      (m_op == Insert)  t->insert(m_val);
        else if (m_op == Inorder) t->inorder();
        else if (m_op == Preorder) t->preorder();
        else if (m_op == Postorder) t->postorder();
        else if (m_op == Display) t->display();
    } else if (m_tt == BST_T) {
        auto* t = static_cast<BinarySearchTree*>(m_t);
        if      (m_op == Insert)  t->insert(m_val);
        else if (m_op == Remove)  t->remove(m_val);
        else if (m_op == Search)  t->search(m_val);
        else if (m_op == Display) t->display();
    } else if (m_tt == AVL_T) {
        auto* t = static_cast<AVLTree*>(m_t);
        if      (m_op == Insert)  t->insert(m_val);
        else if (m_op == Display) t->display();
    } else { // Heap
        auto* t = static_cast<Heap*>(m_t);
        if      (m_op == Insert)  t->insert(m_val);
        else if (m_op == Extract) t->extract();
        else                      t->display();
    }
    emit finished();
}

// ─────────────────────────────────────────────────────────────────────────────
// TreeView
// ─────────────────────────────────────────────────────────────────────────────
TreeView::TreeView(QWidget* parent) : QWidget(parent) {
    m_bt      = new BinaryTree();
    m_bst     = new BinarySearchTree();
    m_avl     = new AVLTree();
    m_minHeap = new Heap(50, true);
    m_maxHeap = new Heap(50, false);

    QVBoxLayout* vl = new QVBoxLayout(this);
    vl->setContentsMargins(0,0,0,0);
    vl->setSpacing(0);

    // Type bar
    QWidget* typeBar = new QWidget(this);
    typeBar->setStyleSheet("background:#1a1a2e; border-bottom:1px solid #2a2a3e;");
    typeBar->setFixedHeight(44);
    QHBoxLayout* tbl = new QHBoxLayout(typeBar);
    tbl->setContentsMargins(16,0,16,0);
    QLabel* typeLbl = new QLabel("Tree Type:", typeBar);
    typeLbl->setStyleSheet("color:#8888aa; font-size:13px;");
    m_typeCombo = new QComboBox(typeBar);
    m_typeCombo->addItem("Binary Tree (BT)");
    m_typeCombo->addItem("Binary Search Tree (BST)");
    m_typeCombo->addItem("AVL Tree");
    m_typeCombo->addItem("Min-Heap");
    m_typeCombo->addItem("Max-Heap");
    m_typeCombo->setStyleSheet(R"(
        QComboBox { background:#1e1e2e; color:#e8e8f0; border:1px solid #2a2a3e;
                    border-radius:6px; padding:4px 10px; font-size:13px; min-width:200px; }
        QComboBox::drop-down { border:none; }
        QComboBox QAbstractItemView { background:#1e1e2e; color:#e8e8f0;
                                      selection-background-color:#252540; }
    )");
    tbl->addWidget(typeLbl);
    tbl->addWidget(m_typeCombo);
    tbl->addStretch();
    vl->addWidget(typeBar);

    m_panel = new ModulePanel("Trees", "#81C784", this);
    vl->addWidget(m_panel, 1);

    m_canvas = new TreeCanvas(m_panel->canvasArea());
    QVBoxLayout* cl = new QVBoxLayout(m_panel->canvasArea());
    cl->setContentsMargins(16, 16, 16, 16);
    cl->addWidget(m_canvas, 1);

    setupBTOps();

    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged,   m_panel, &ModulePanel::logStep);
    connect(notifier, &GlobalGuiNotifier::stepLogged,   this,    &TreeView::onStepLogged);
    connect(notifier, &GlobalGuiNotifier::resultLogged, m_panel, &ModulePanel::logResult);
    connect(notifier, &GlobalGuiNotifier::errorLogged,  m_panel, &ModulePanel::logError);
    connect(notifier, &GlobalGuiNotifier::headerLogged, m_panel, &ModulePanel::logHeader);
    connect(notifier, &GlobalGuiNotifier::stateChanged, this, &TreeView::onStateChanged);

    connect(m_panel, &ModulePanel::runRequested,   this, &TreeView::onRun);
    connect(m_panel, &ModulePanel::resetRequested, this, &TreeView::onReset);
    connect(m_panel->operationList(), &QListWidget::currentRowChanged, this, &TreeView::onOpSelected);
    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TreeView::onTreeTypeChanged);
}

void TreeView::onStateChanged() {
    // Refresh the tree view after every step
    if (m_treeIndex == 0)        m_canvas->setRoot(m_bt->getRoot());
    else if (m_treeIndex == 1)   m_canvas->setRoot(m_bst->getRoot());
    else if (m_treeIndex == 2)   m_canvas->setRoot(m_avl->getRoot());
    else {
        Heap* h = (m_treeIndex == 3) ? m_minHeap : m_maxHeap;
        int buf[100]; int n = h->getSnapshot(buf, 100);
        QVector<int> v; for (int i = 0; i < n; i++) v.append(buf[i]);
        m_canvas->setHeapData(v, h->isMin());
    }
}

void TreeView::onStepLogged(int stepNum, const QString& msg) {
    QRegularExpression re("\\((\\d+)\\)");
    QRegularExpressionMatch match = re.match(msg);
    if (match.hasMatch()) {
        m_canvas->setActiveVal(match.captured(1).toInt());
    } else {
        m_canvas->setActiveVal(-1);
    }
}

void TreeView::setupBTOps() {
    m_panel->operationList()->clear();
    m_panel->operationList()->addItem("Insert");
    m_panel->operationList()->addItem("In-order Traversal");
    m_panel->operationList()->addItem("Pre-order Traversal");
    m_panel->operationList()->addItem("Post-order Traversal");
    m_panel->operationList()->addItem("Display Tree");
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1Label()->setText("Value:");
    m_panel->input2()->hide(); m_panel->input2Label()->hide();
}
void TreeView::setupBSTOps() {
    m_panel->operationList()->clear();
    m_panel->operationList()->addItem("Insert");
    m_panel->operationList()->addItem("Delete");
    m_panel->operationList()->addItem("Search");
    m_panel->operationList()->addItem("Display");
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1Label()->setText("Value:");
    m_panel->input2()->hide(); m_panel->input2Label()->hide();
}
void TreeView::setupAVLOps() {
    m_panel->operationList()->clear();
    m_panel->operationList()->addItem("Insert");
    m_panel->operationList()->addItem("Display");
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1Label()->setText("Value:");
    m_panel->input2()->hide(); m_panel->input2Label()->hide();
}
void TreeView::setupHeapOps() {
    m_panel->operationList()->clear();
    m_panel->operationList()->addItem("Insert");
    m_panel->operationList()->addItem("Extract Root");
    m_panel->operationList()->addItem("Display");
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1Label()->setText("Value:");
    m_panel->input2()->hide(); m_panel->input2Label()->hide();
}

void TreeView::onTreeTypeChanged(int idx) {
    m_treeIndex = idx;
    m_panel->clearLog();
    m_canvas->clear();
    if (idx == 0) setupBTOps();
    else if (idx == 1) setupBSTOps();
    else if (idx == 2) setupAVLOps();
    else setupHeapOps();
    onStateChanged();
}

void TreeView::onOpSelected(int row) {
    bool needsVal = (row == 0); // only Insert
    if (m_treeIndex >= 3 && row == 0) needsVal = true;  // heap insert
    m_panel->input1()->setVisible(needsVal);
    m_panel->input1Label()->setVisible(needsVal);
}

void TreeView::onRun() {
    int row = m_panel->operationList()->currentRow();
    bool ok = true;
    int val = 0;
    if (m_panel->input1()->isVisible())
        val = m_panel->input1()->text().toInt(&ok);
    if (!ok) { m_panel->logError("Invalid input."); return; }

    m_panel->clearLog();
    setRunning(true);

    TreeWorker::Op op;
    if (m_treeIndex <= 2) {
        static const TreeWorker::Op btOps[]  = { TreeWorker::Insert, TreeWorker::Inorder, TreeWorker::Preorder, TreeWorker::Postorder, TreeWorker::Display };
        static const TreeWorker::Op bstOps[] = { TreeWorker::Insert, TreeWorker::Remove, TreeWorker::Search, TreeWorker::Display };
        static const TreeWorker::Op avlOps[] = { TreeWorker::Insert, TreeWorker::Display };
        
        if (m_treeIndex == 0) op = btOps[row];
        else if (m_treeIndex == 1) op = bstOps[row];
        else op = avlOps[row];
    } else {
        static const TreeWorker::Op heapOps[] = { TreeWorker::Insert, TreeWorker::Extract, TreeWorker::Display };
        op = heapOps[row];
    }

    void* treePtr = nullptr;
    TreeWorker::TreeType tt;
    if (m_treeIndex == 0)      { treePtr = m_bt;      tt = TreeWorker::BT_T; }
    else if (m_treeIndex == 1) { treePtr = m_bst;     tt = TreeWorker::BST_T; }
    else if (m_treeIndex == 2) { treePtr = m_avl;     tt = TreeWorker::AVL_T; }
    else if (m_treeIndex == 3) { treePtr = m_minHeap; tt = TreeWorker::HEAP_T; }
    else                       { treePtr = m_maxHeap; tt = TreeWorker::HEAP_T; }

    auto* thread = new QThread(this);
    auto* worker = new TreeWorker(treePtr, tt, op, val);
    worker->moveToThread(thread);
    connect(thread, &QThread::started,    worker, &TreeWorker::run);
    connect(worker, &TreeWorker::finished, this,  &TreeView::onWorkerFinished, Qt::QueuedConnection);
    connect(worker, &TreeWorker::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished,   thread, &QThread::deleteLater);
    connect(thread, &QThread::finished,   worker, &QObject::deleteLater);
    m_thread = thread;
    thread->start();
}

void TreeView::onReset() {
    delete m_bt;      m_bt      = new BinaryTree();
    delete m_bst;     m_bst     = new BinarySearchTree();
    delete m_avl;     m_avl     = new AVLTree();
    delete m_minHeap; m_minHeap = new Heap(50, true);
    delete m_maxHeap; m_maxHeap = new Heap(50, false);
    m_canvas->clear();
    m_panel->clearLog();
    m_panel->logResult("Tree cleared.");
    setRunning(false);
}

void TreeView::onWorkerFinished() {
    onStateChanged();
    setRunning(false);
}

void TreeView::setRunning(bool r) {
    m_panel->runButton()->setEnabled(!r);
    m_panel->statusLabel()->setText(r ? "\xe2\x9a\x99 Running..." : "");
}
