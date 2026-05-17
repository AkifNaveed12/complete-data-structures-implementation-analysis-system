#include "StackQueueView.h"
#include <QPainter>
#include <QPen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QFont>

// ─────────────────────────────────────────────────────────────────────────────
// StackCanvas — draws vertical tower of elements
// ─────────────────────────────────────────────────────────────────────────────
StackCanvas::StackCanvas(QWidget* p) : QWidget(p) { setMinimumHeight(200); }

void StackCanvas::updateState(const QVector<int>& vals, int activeIdx) {
    m_vals = vals; m_activeIdx = activeIdx; update();
}
void StackCanvas::clear() { m_vals.clear(); m_activeIdx = -1; update(); }

void StackCanvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (m_vals.isEmpty()) {
        p.setPen(QColor("#444466"));
        p.setFont(QFont("Consolas", 13, QFont::Normal, true));
        p.drawText(rect(), Qt::AlignCenter, "[ Stack is Empty ]");
        return;
    }

    int cx = width() / 2 - CELL_W / 2;
    int topY = 24;
    QFont df("Consolas", 13, QFont::Medium);
    QFont lf("Segoe UI", 9);

    for (int i = 0; i < m_vals.size(); i++) {
        int y = topY + i * (CELL_H + 3);
        bool isActive = (i == m_activeIdx);
        bool isTop    = (i == 0);

        p.setBrush(isActive ? QColor("#1A3040") : QColor("#1E1E2E"));
        p.setPen(QPen(isActive ? QColor("#FFB74D") : (isTop ? QColor("#FFB74D") : QColor("#2A2A3E")),
                      isTop ? 2 : 1));
        p.drawRoundedRect(cx, y, CELL_W, CELL_H, 6, 6);

        p.setFont(df);
        p.setPen(isActive ? QColor("#FFB74D") : (isTop ? QColor("#FFB74D") : QColor("#A8E6CF")));
        QString txt = isActive ? QString("(%1)").arg(m_vals[i]) : QString::number(m_vals[i]);
        p.drawText(QRect(cx, y, CELL_W, CELL_H), Qt::AlignCenter, txt);

        if (isTop) {
            p.setFont(lf);
            p.setPen(QColor("#FFB74D"));
            p.drawText(cx + CELL_W + 8, y + CELL_H / 2 + 4, "← TOP");
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// QueueCanvas — draws horizontal sequence
// ─────────────────────────────────────────────────────────────────────────────
QueueCanvas::QueueCanvas(QWidget* p) : QWidget(p) { setMinimumHeight(160); }

void QueueCanvas::updateState(const QVector<int>& vals, int activeIdx) {
    m_vals = vals; m_activeIdx = activeIdx; update();
}
void QueueCanvas::clear() { m_vals.clear(); m_activeIdx = -1; update(); }

void QueueCanvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (m_vals.isEmpty()) {
        p.setPen(QColor("#444466"));
        p.setFont(QFont("Consolas", 13, QFont::Normal, true));
        p.drawText(rect(), Qt::AlignCenter, "[ Queue is Empty ]");
        return;
    }

    int n      = m_vals.size();
    int totalW = n * (CELL_W + 4) - 4;
    int x0     = (width() - totalW) / 2;
    int y0     = (height() - CELL_H) / 2;
    QFont df("Consolas", 12, QFont::Medium);
    QFont lf("Segoe UI", 9);

    for (int i = 0; i < n; i++) {
        int x = x0 + i * (CELL_W + 4);
        bool isActive = (i == m_activeIdx);
        bool isFront  = (i == 0);
        bool isRear   = (i == n - 1);

        p.setBrush(isActive ? QColor("#1A2A20") : QColor("#1E1E2E"));
        p.setPen(QPen(isActive ? QColor("#FFB74D") : (isFront || isRear ? QColor("#FFB74D") : QColor("#2A2A3E")),
                      (isFront || isRear) ? 2 : 1));
        p.drawRoundedRect(x, y0, CELL_W, CELL_H, 6, 6);

        p.setFont(df);
        p.setPen(isActive ? QColor("#FFB74D") : QColor("#A8E6CF"));
        p.drawText(QRect(x, y0, CELL_W, CELL_H), Qt::AlignCenter,
                   isActive ? QString("(%1)").arg(m_vals[i]) : QString::number(m_vals[i]));

        p.setFont(lf);
        p.setPen(QColor("#FFB74D"));
        if (isFront) p.drawText(x, y0 + CELL_H + 16, "FRONT");
        if (isRear)  p.drawText(x + CELL_W - 30, y0 - 8, "REAR");
    }

    // FRONT→ REAR→ arrows
    if (n > 0) {
        p.setPen(QPen(QColor("#FFB74D"), 1));
        p.drawLine(x0 - 22, y0 + CELL_H/2, x0 - 2, y0 + CELL_H/2);
        p.drawLine(x0 - 8, y0 + CELL_H/2 - 5, x0 - 2, y0 + CELL_H/2);
        p.drawLine(x0 - 8, y0 + CELL_H/2 + 5, x0 - 2, y0 + CELL_H/2);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Workers
// ─────────────────────────────────────────────────────────────────────────────
void StackWorker::run() {
    if (m_t == StaticT) {
        auto* s = static_cast<StaticStack*>(m_s);
        if (m_op == Push) s->push(m_val);
        else if (m_op == Pop) s->pop();
        else if (m_op == Peek) s->peek();
        else s->display();
    } else {
        auto* s = static_cast<DynamicStack*>(m_s);
        if (m_op == Push) s->push(m_val);
        else if (m_op == Pop) s->pop();
        else if (m_op == Peek) s->peek();
        else s->display();
    }
    emit finished();
}

void QueueWorker::run() {
    if (m_t == SimpleT) {
        auto* q = static_cast<SimpleQueue*>(m_q);
        if (m_op == Enqueue) q->enqueue(m_val);
        else if (m_op == Dequeue) q->dequeue();
        else if (m_op == Peek) q->peek();
        else q->display();
    } else if (m_t == CircularT) {
        auto* q = static_cast<CircularQueue*>(m_q);
        if (m_op == Enqueue) q->enqueue(m_val);
        else if (m_op == Dequeue) q->dequeue();
        else if (m_op == Peek) q->peek();
        else q->display();
    } else if (m_t == PriorityT) {
        auto* q = static_cast<PriorityQueue*>(m_q);
        if (m_op == Enqueue) q->enqueue(m_val, m_prio);
        else if (m_op == Dequeue) q->dequeue();
        else if (m_op == Peek) q->peek();
        else q->display();
    } else {
        auto* q = static_cast<Deque*>(m_q);
        if (m_op == InsertFront) q->insertFront(m_val);
        else if (m_op == InsertRear) q->insertRear(m_val);
        else if (m_op == DeleteFront) q->deleteFront();
        else if (m_op == DeleteRear) q->deleteRear();
        else q->display();
    }
    emit finished();
}

// ─────────────────────────────────────────────────────────────────────────────
// StackQueueView
// ─────────────────────────────────────────────────────────────────────────────
StackQueueView::StackQueueView(QWidget* parent) : QWidget(parent) {
    m_staticStack   = new StaticStack(20);
    m_dynamicStack  = new DynamicStack();
    m_simpleQueue   = new SimpleQueue(20);
    m_circularQueue = new CircularQueue(20);
    m_priorityQueue = new PriorityQueue();
    m_deque         = new Deque();

    QVBoxLayout* vl = new QVBoxLayout(this);
    vl->setContentsMargins(0,0,0,0);
    vl->setSpacing(0);

    // Type selector bar
    QWidget* typeBar = new QWidget(this);
    typeBar->setStyleSheet("background:#1a1a2e; border-bottom:1px solid #2a2a3e;");
    typeBar->setFixedHeight(44);
    QHBoxLayout* tbl = new QHBoxLayout(typeBar);
    tbl->setContentsMargins(16,0,16,0);
    QLabel* typeLbl = new QLabel("Structure:", typeBar);
    typeLbl->setStyleSheet("color:#8888aa; font-size:13px;");
    m_typeCombo = new QComboBox(typeBar);
    m_typeCombo->addItem("Static Stack");
    m_typeCombo->addItem("Dynamic Stack");
    m_typeCombo->addItem("Simple Queue");
    m_typeCombo->addItem("Circular Queue");
    m_typeCombo->addItem("Priority Queue");
    m_typeCombo->addItem("Deque");
    m_typeCombo->setStyleSheet(R"(
        QComboBox { background:#1e1e2e; color:#e8e8f0; border:1px solid #2a2a3e;
                    border-radius:6px; padding:4px 10px; font-size:13px; min-width:200px; }
        QComboBox::drop-down { border:none; }
        QComboBox QAbstractItemView { background:#1e1e2e; color:#e8e8f0; selection-background-color:#252540; }
    )");
    tbl->addWidget(typeLbl);
    tbl->addWidget(m_typeCombo);
    tbl->addStretch();
    vl->addWidget(typeBar);

    // Panel
    m_panel = new ModulePanel("Stack", "#FFB74D", this);
    vl->addWidget(m_panel, 1);

    // Canvases (both live in the same canvas area, toggled)
    m_stackCanvas = new StackCanvas(m_panel->canvasArea());
    m_queueCanvas = new QueueCanvas(m_panel->canvasArea());
    m_queueCanvas->hide();

    QVBoxLayout* cl = new QVBoxLayout(m_panel->canvasArea());
    cl->setContentsMargins(24, 24, 24, 24);
    cl->addWidget(m_stackCanvas, 1);
    cl->addWidget(m_queueCanvas, 1);

    setupStackOps();

    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged,   m_panel, &ModulePanel::logStep);
    connect(notifier, &GlobalGuiNotifier::resultLogged, m_panel, &ModulePanel::logResult);
    connect(notifier, &GlobalGuiNotifier::errorLogged,  m_panel, &ModulePanel::logError);
    connect(notifier, &GlobalGuiNotifier::headerLogged, m_panel, &ModulePanel::logHeader);
    connect(notifier, &GlobalGuiNotifier::stateChanged, this, [this]() {
        // Refresh canvas on every step
        refreshCanvas();
    });

    connect(m_panel, &ModulePanel::runRequested,   this, &StackQueueView::onRun);
    connect(m_panel, &ModulePanel::resetRequested, this, &StackQueueView::onReset);
    connect(m_panel->operationList(), &QListWidget::currentRowChanged, this, &StackQueueView::onOpSelected);
    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &StackQueueView::onDSTypeChanged);
}

void StackQueueView::refreshCanvas() {
    int buf[50];
    QVector<int> vals;

    if (m_dsIndex == 0) {
        int n = m_staticStack->getSnapshot(buf, 50);
        for (int i = 0; i < n; i++) vals.append(buf[i]);
        m_stackCanvas->updateState(vals);
    } else if (m_dsIndex == 1) {
        int n = m_dynamicStack->getSnapshot(buf, 50);
        for (int i = 0; i < n; i++) vals.append(buf[i]);
        m_stackCanvas->updateState(vals);
    } else if (m_dsIndex == 2) {
        int n = m_simpleQueue->getSnapshot(buf, 50);
        for (int i = 0; i < n; i++) vals.append(buf[i]);
        m_queueCanvas->updateState(vals);
    } else if (m_dsIndex == 3) {
        int n = m_circularQueue->getSnapshot(buf, 50);
        for (int i = 0; i < n; i++) vals.append(buf[i]);
        m_queueCanvas->updateState(vals);
    }
}

void StackQueueView::setupStackOps() {
    m_panel->operationList()->clear();
    m_panel->operationList()->addItem("Push");
    m_panel->operationList()->addItem("Pop");
    m_panel->operationList()->addItem("Peek");
    m_panel->operationList()->addItem("Display");
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1Label()->setText("Value:");
    m_panel->input1()->setPlaceholderText("e.g. 42");
    m_panel->input2()->hide();
    m_panel->input2Label()->hide();
}

void StackQueueView::setupQueueOps() {
    m_panel->operationList()->clear();
    if (m_dsIndex == 4) { // Priority Queue
        m_panel->operationList()->addItem("Enqueue (with priority)");
        m_panel->operationList()->addItem("Dequeue");
        m_panel->operationList()->addItem("Peek");
        m_panel->operationList()->addItem("Display");
        m_panel->input1Label()->setText("Value:");
        m_panel->input2Label()->setText("Priority:");
        m_panel->input2()->setPlaceholderText("higher = served first");
        m_panel->input2()->show();
        m_panel->input2Label()->show();
    } else if (m_dsIndex == 5) { // Deque
        m_panel->operationList()->addItem("Insert Front");
        m_panel->operationList()->addItem("Insert Rear");
        m_panel->operationList()->addItem("Delete Front");
        m_panel->operationList()->addItem("Delete Rear");
        m_panel->operationList()->addItem("Display");
        m_panel->input1Label()->setText("Value:");
        m_panel->input2()->hide();
        m_panel->input2Label()->hide();
    } else {
        m_panel->operationList()->addItem("Enqueue");
        m_panel->operationList()->addItem("Dequeue");
        m_panel->operationList()->addItem("Peek");
        m_panel->operationList()->addItem("Display");
        m_panel->input1Label()->setText("Value:");
        m_panel->input2()->hide();
        m_panel->input2Label()->hide();
    }
    m_panel->operationList()->setCurrentRow(0);
    m_panel->input1()->setPlaceholderText("e.g. 42");
}

void StackQueueView::onDSTypeChanged(int idx) {
    m_dsIndex = idx;
    m_panel->clearLog();
    bool isStack = (idx < 2);
    m_stackCanvas->setVisible(isStack);
    m_queueCanvas->setVisible(!isStack);

    if (isStack) {
        m_panel->setStyleSheet(""); // reset accent
        setupStackOps();
    } else {
        setupQueueOps();
    }
    m_stackCanvas->clear();
    m_queueCanvas->clear();
    refreshCanvas();
}

void StackQueueView::onOpSelected(int row) {
    bool needsValue = true;
    if (m_dsIndex < 2) needsValue = (row == 0); // only Push needs value
    else if (m_dsIndex == 5) needsValue = (row <= 1); // Insert ops need value
    else needsValue = (row == 0); // only Enqueue needs value
    m_panel->input1()->setVisible(needsValue);
    m_panel->input1Label()->setVisible(needsValue);
}

void StackQueueView::onRun() {
    int row = m_panel->operationList()->currentRow();
    bool ok = true;
    int v1 = 0, v2 = 0;
    if (m_panel->input1()->isVisible()) v1 = m_panel->input1()->text().toInt(&ok);
    if (m_panel->input2()->isVisible()) v2 = m_panel->input2()->text().toInt(&ok);
    if (!ok) { m_panel->logError("Invalid input."); return; }

    m_panel->clearLog();
    setRunning(true);

    QObject* worker = nullptr;
    QThread* thread = new QThread(this);

    if (m_dsIndex == 0) { // Static Stack
        auto* w = new StackWorker(m_staticStack, StackWorker::StaticT, static_cast<StackWorker::Op>(row), v1);
        w->moveToThread(thread);
        connect(thread, &QThread::started,  w, &StackWorker::run);
        connect(w, &StackWorker::finished, this, &StackQueueView::onWorkerFinished, Qt::QueuedConnection);
        connect(w, &StackWorker::finished, thread, &QThread::quit);
        worker = w;
    } else if (m_dsIndex == 1) { // Dynamic Stack
        auto* w = new StackWorker(m_dynamicStack, StackWorker::DynamicT, static_cast<StackWorker::Op>(row), v1);
        w->moveToThread(thread);
        connect(thread, &QThread::started,  w, &StackWorker::run);
        connect(w, &StackWorker::finished, this, &StackQueueView::onWorkerFinished, Qt::QueuedConnection);
        connect(w, &StackWorker::finished, thread, &QThread::quit);
        worker = w;
    } else if (m_dsIndex == 2) { // Simple Queue
        QueueWorker::Op op = static_cast<QueueWorker::Op>(row);
        auto* w = new QueueWorker(m_simpleQueue, QueueWorker::SimpleT, op, v1);
        w->moveToThread(thread);
        connect(thread, &QThread::started,  w, &QueueWorker::run);
        connect(w, &QueueWorker::finished, this, &StackQueueView::onWorkerFinished, Qt::QueuedConnection);
        connect(w, &QueueWorker::finished, thread, &QThread::quit);
        worker = w;
    } else if (m_dsIndex == 3) { // Circular Queue
        QueueWorker::Op op = static_cast<QueueWorker::Op>(row);
        auto* w = new QueueWorker(m_circularQueue, QueueWorker::CircularT, op, v1);
        w->moveToThread(thread);
        connect(thread, &QThread::started,  w, &QueueWorker::run);
        connect(w, &QueueWorker::finished, this, &StackQueueView::onWorkerFinished, Qt::QueuedConnection);
        connect(w, &QueueWorker::finished, thread, &QThread::quit);
        worker = w;
    } else if (m_dsIndex == 4) { // Priority Queue
        QueueWorker::Op op = static_cast<QueueWorker::Op>(row);
        auto* w = new QueueWorker(m_priorityQueue, QueueWorker::PriorityT, op, v1, v2);
        w->moveToThread(thread);
        connect(thread, &QThread::started,  w, &QueueWorker::run);
        connect(w, &QueueWorker::finished, this, &StackQueueView::onWorkerFinished, Qt::QueuedConnection);
        connect(w, &QueueWorker::finished, thread, &QThread::quit);
        worker = w;
    } else { // Deque
        static const QueueWorker::Op dequeOps[] = {
            QueueWorker::InsertFront, QueueWorker::InsertRear,
            QueueWorker::DeleteFront, QueueWorker::DeleteRear, QueueWorker::Display
        };
        auto* w = new QueueWorker(m_deque, QueueWorker::DequeT, dequeOps[row], v1);
        w->moveToThread(thread);
        connect(thread, &QThread::started,  w, &QueueWorker::run);
        connect(w, &QueueWorker::finished, this, &StackQueueView::onWorkerFinished, Qt::QueuedConnection);
        connect(w, &QueueWorker::finished, thread, &QThread::quit);
        worker = w;
    }

    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    if (worker) connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    m_thread = thread;
    thread->start();
}

void StackQueueView::onReset() {
    delete m_staticStack;   m_staticStack   = new StaticStack(20);
    delete m_dynamicStack;  m_dynamicStack  = new DynamicStack();
    delete m_simpleQueue;   m_simpleQueue   = new SimpleQueue(20);
    delete m_circularQueue; m_circularQueue = new CircularQueue(20);
    delete m_priorityQueue; m_priorityQueue = new PriorityQueue();
    delete m_deque;         m_deque         = new Deque();
    m_stackCanvas->clear();
    m_queueCanvas->clear();
    m_panel->clearLog();
    m_panel->logResult("Structure cleared.");
    setRunning(false);
}

void StackQueueView::onWorkerFinished() {
    refreshCanvas();
    setRunning(false);
}

void StackQueueView::setRunning(bool r) {
    m_panel->runButton()->setEnabled(!r);
    m_panel->statusLabel()->setText(r ? "\xe2\x9a\x99 Running..." : "");
}
