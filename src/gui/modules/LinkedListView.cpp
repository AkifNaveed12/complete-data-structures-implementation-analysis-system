#include "LinkedListView.h"
#include <QPainter>
#include <QPen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

// ─────────────────────────────────────────────────────────────────────────────
// LLCanvas
// ─────────────────────────────────────────────────────────────────────────────
LLCanvas::LLCanvas(QWidget* parent) : QWidget(parent) { setMinimumHeight(160); }

void LLCanvas::updateState(const QVector<int>& vals, int activeIdx, Type t) {
    m_vals      = vals;
    m_activeIdx = activeIdx;
    m_type      = t;
    update();
}

void LLCanvas::clear() {
    m_vals.clear();
    m_activeIdx = -1;
    update();
}

void LLCanvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (m_vals.isEmpty()) {
        p.setPen(QColor("#444466"));
        p.setFont(QFont("Consolas", 13, QFont::Normal, true));
        p.drawText(rect(), Qt::AlignCenter, "[ Empty — no nodes ]");
        return;
    }

    const int n      = m_vals.size();
    const int totalW = n * (NODE_W + GAP) + GAP;
    int x0           = (width() - totalW) / 2 + GAP / 2;
    if (x0 < 10) x0 = 10;
    const int y0 = (height() - NODE_H) / 2;

    QFont dataFont("Consolas", 13, QFont::Medium);
    QFont arrFont("Consolas", 10);

    for (int i = 0; i < n; i++) {
        int x        = x0 + i * (NODE_W + GAP);
        bool isActive = (i == m_activeIdx);
        QColor accent   = QColor("#4FC3F7");
        QColor nodeBg   = isActive ? QColor("#1A3040") : QColor("#1E1E2E");
        QColor nodeBdr  = isActive ? accent : QColor("#2A2A3E");

        // Draw node box
        QRect nr(x, y0, NODE_W, NODE_H);
        p.setBrush(nodeBg);
        p.setPen(QPen(nodeBdr, isActive ? 2 : 1));
        p.drawRoundedRect(nr, 6, 6);

        // Value
        p.setFont(dataFont);
        p.setPen(isActive ? accent : QColor("#A8E6CF"));
        QString txt = isActive ? QString("(%1)").arg(m_vals[i]) : QString::number(m_vals[i]);
        p.drawText(nr, Qt::AlignCenter, txt);

        // Arrow →
        if (i < n - 1) {
            int ax = x + NODE_W;
            int ay = y0 + NODE_H / 2;
            p.setPen(QPen(QColor("#2A2A3E"), 1));
            p.drawLine(ax, ay, ax + GAP - 2, ay);
            // Arrowhead
            p.drawLine(ax + GAP - 8, ay - 5, ax + GAP - 2, ay);
            p.drawLine(ax + GAP - 8, ay + 5, ax + GAP - 2, ay);
        }

        // For Doubly: also draw ← arrow back
        if (m_type == Doubly && i > 0) {
            int ax = x;
            int ay = y0 + NODE_H / 2 - 8;
            p.setPen(QPen(QColor("#FFB74D"), 1));
            // Just draw a small backpointer indicator above the forward arrow
            p.drawLine(ax, ay, ax - GAP + 2, ay);
            p.drawLine(ax - GAP + 8, ay - 5, ax - GAP + 2, ay);
            p.drawLine(ax - GAP + 8, ay + 5, ax - GAP + 2, ay);
        }
    }

    // Circular: draw arc from last node back to first
    if (m_type == Circular && n > 1) {
        int lastX = x0 + (n - 1) * (NODE_W + GAP) + NODE_W / 2;
        int firstX = x0 + NODE_W / 2;
        int arcY  = y0 + NODE_H + 18;

        p.setPen(QPen(QColor("#81C784"), 1, Qt::DashLine));
        p.setBrush(Qt::NoBrush);
        QPoint pts[] = {
            QPoint(lastX,  y0 + NODE_H),
            QPoint(lastX,  arcY),
            QPoint(firstX, arcY),
            QPoint(firstX, y0 + NODE_H)
        };
        for (int i = 0; i < 3; i++) p.drawLine(pts[i], pts[i+1]);

        // Arrow back up
        p.drawLine(pts[3], QPoint(firstX - 5, y0 + NODE_H - 6));
        p.drawLine(pts[3], QPoint(firstX + 5, y0 + NODE_H - 6));

        // "[HEAD]" label
        p.setFont(QFont("Consolas", 9));
        p.setPen(QColor("#81C784"));
        p.drawText(firstX - 20, arcY + 14, "[HEAD]");
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// LLWorker
// ─────────────────────────────────────────────────────────────────────────────
void LLWorker::run() {
    if (m_lt == SinglyT) {
        auto* ll = static_cast<LinkedList*>(m_list);
        switch (m_op) {
            case InsertStart: ll->insertAtStart(m_val); break;
            case InsertEnd:   ll->insertAtEnd(m_val);   break;
            case Delete:      ll->deleteValue(m_val);   break;
            case Search:      ll->search(m_val);        break;
            case Display:     ll->display();            break;
        }
    } else if (m_lt == DoublyT) {
        auto* dl = static_cast<DoublyLinkedList*>(m_list);
        switch (m_op) {
            case InsertStart: dl->insertStart(m_val);      break;
            case InsertEnd:   dl->insertEnd(m_val);        break;
            case Delete:      dl->deleteByValue(m_val);    break;
            case Search:      dl->search(m_val);           break;
            case Display:     dl->display();               break;
        }
    } else {
        auto* cl = static_cast<CircularLinkedList*>(m_list);
        switch (m_op) {
            case InsertStart: cl->insertStart(m_val);   break;
            case InsertEnd:   cl->insertEnd(m_val);     break;
            case Delete:      cl->deleteByValue(m_val); break;
            case Search:      cl->search(m_val);        break;
            case Display:     cl->display();            break;
        }
    }
    emit finished();
}

// ─────────────────────────────────────────────────────────────────────────────
// LinkedListView
// ─────────────────────────────────────────────────────────────────────────────
LinkedListView::LinkedListView(QWidget* parent) : QWidget(parent) {
    m_singly   = new LinkedList();
    m_doubly   = new DoublyLinkedList();
    m_circular = new CircularLinkedList();

    QVBoxLayout* vl = new QVBoxLayout(this);
    vl->setContentsMargins(0,0,0,0);
    vl->setSpacing(0);

    // Type selector bar
    QWidget* typeBar = new QWidget(this);
    typeBar->setStyleSheet("background:#1a1a2e; border-bottom:1px solid #2a2a3e;");
    typeBar->setFixedHeight(44);
    QHBoxLayout* tbl = new QHBoxLayout(typeBar);
    tbl->setContentsMargins(16,0,16,0);
    QLabel* typeLbl = new QLabel("List Type:", typeBar);
    typeLbl->setStyleSheet("color:#8888aa; font-size:13px;");
    m_typeCombo = new QComboBox(typeBar);
    m_typeCombo->addItem("Singly Linked List");
    m_typeCombo->addItem("Doubly Linked List");
    m_typeCombo->addItem("Circular Linked List");
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

    // Main panel
    m_panel = new ModulePanel("Linked List", "#4FC3F7", this);
    vl->addWidget(m_panel, 1);

    // Canvas
    m_canvas = new LLCanvas(m_panel->canvasArea());
    QVBoxLayout* cl = new QVBoxLayout(m_panel->canvasArea());
    cl->setContentsMargins(24,24,24,24);
    cl->addWidget(m_canvas, 1);

    // Operations
    m_panel->operationList()->addItem("Insert at Start");
    m_panel->operationList()->addItem("Insert at End");
    m_panel->operationList()->addItem("Delete by Value");
    m_panel->operationList()->addItem("Search Value");
    m_panel->operationList()->addItem("Display");
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1Label()->setText("Value:");
    m_panel->input1()->setPlaceholderText("e.g. 42");
    m_panel->input2()->hide();
    m_panel->input2Label()->hide();

    // Signals
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged,   m_panel, &ModulePanel::logStep);
    connect(notifier, &GlobalGuiNotifier::resultLogged, m_panel, &ModulePanel::logResult);
    connect(notifier, &GlobalGuiNotifier::errorLogged,  m_panel, &ModulePanel::logError);
    connect(notifier, &GlobalGuiNotifier::headerLogged, m_panel, &ModulePanel::logHeader);
    connect(notifier, &GlobalGuiNotifier::stateChanged, this, [this]() { rebuildCurrentView(); });

    connect(m_panel, &ModulePanel::runRequested,   this, &LinkedListView::onRun);
    connect(m_panel, &ModulePanel::resetRequested, this, &LinkedListView::onReset);
    connect(m_panel->operationList(), &QListWidget::currentRowChanged, this, &LinkedListView::onOpSelected);
    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LinkedListView::onListTypeChanged);
}

void LinkedListView::onListTypeChanged(int idx) {
    m_curType = static_cast<LLCanvas::Type>(idx);
    m_panel->clearLog();
    m_canvas->clear();
    rebuildCurrentView();
}

void LinkedListView::onOpSelected(int row) {
    bool needsValue = (row != 4);
    m_panel->input1()->setVisible(needsValue);
    m_panel->input1Label()->setVisible(needsValue);
}

void LinkedListView::onRun() {
    int row = m_panel->operationList()->currentRow();
    bool ok = true;
    int val = 0;
    if (row != 4) { val = m_panel->input1()->text().toInt(&ok); }
    if (!ok) { m_panel->logError("Invalid input."); return; }

    m_panel->clearLog();
    setRunning(true);

    LLWorker::Op op = static_cast<LLWorker::Op>(row);
    LLWorker::ListType lt = static_cast<LLWorker::ListType>(m_curType);
    void* listPtr = nullptr;
    if (lt == LLWorker::SinglyT)   listPtr = m_singly;
    else if (lt == LLWorker::DoublyT) listPtr = m_doubly;
    else                            listPtr = m_circular;

    m_thread = new QThread(this);
    m_worker = new LLWorker(listPtr, lt, op, val);
    m_worker->moveToThread(m_thread);

    connect(m_thread, &QThread::started,    m_worker, &LLWorker::run);
    connect(m_worker, &LLWorker::finished,  this,     &LinkedListView::onWorkerFinished, Qt::QueuedConnection);
    connect(m_worker, &LLWorker::finished,  m_thread, &QThread::quit);
    connect(m_thread, &QThread::finished,   m_thread, &QThread::deleteLater);
    connect(m_thread, &QThread::finished,   m_worker, &QObject::deleteLater);
    m_thread->start();
}

void LinkedListView::onReset() {
    delete m_singly;   m_singly   = new LinkedList();
    delete m_doubly;   m_doubly   = new DoublyLinkedList();
    delete m_circular; m_circular = new CircularLinkedList();
    m_canvas->clear();
    m_panel->clearLog();
    m_panel->logResult("List cleared.");
    setRunning(false);
}

void LinkedListView::onWorkerFinished() {
    setRunning(false);
    rebuildCurrentView();
}

// Rebuilds canvas by traversing the active list
void LinkedListView::rebuildCurrentView() {
    QVector<int> vals;
    if (m_curType == LLCanvas::Singly) {
        // We need to traverse — but LinkedList doesn't expose head publicly.
        // For now, we rely on the stateChanged signal fired by visual_qt during operations.
    }
    // Just trigger repaint — the canvas keeps its own state updated via signals
    m_canvas->update();
}

void LinkedListView::setRunning(bool r) {
    m_panel->runButton()->setEnabled(!r);
    m_panel->statusLabel()->setText(r ? "\xe2\x9a\x99 Running..." : "");
}
