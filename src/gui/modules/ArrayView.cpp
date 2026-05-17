#include "ArrayView.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QInputDialog>
#include <QMessageBox>

// ============================================================
// ArrayCanvas — draws the array visualization
// ============================================================

ArrayCanvas::ArrayCanvas(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(160);
}

void ArrayCanvas::updateState(const int* arr, int size, int activeIndex) {
    m_values.clear();
    for (int i = 0; i < size && i < 20; i++) {
        m_values.append(arr[i]);
    }
    m_activeIndex = activeIndex;
    update(); // triggers paintEvent
}

void ArrayCanvas::clear() {
    m_values.clear();
    m_activeIndex = -1;
    update();
}

void ArrayCanvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int totalW = MARGIN * 2 + m_values.size() * CELL_W;
    int startX = (width() - totalW + MARGIN * 2) / 2;
    if (startX < MARGIN) startX = MARGIN;
    int startY = (height() - CELL_H) / 2;

    if (m_values.isEmpty()) {
        p.setPen(QColor("#444466"));
        p.setFont(QFont("Consolas", 14, QFont::Normal, true));
        p.drawText(rect(), Qt::AlignCenter, "[ Empty — no elements ]");
        return;
    }

    QFont dataFont("Consolas", 14, QFont::Medium);
    QFont idxFont("Segoe UI", 10);

    for (int i = 0; i < m_values.size(); i++) {
        int x = startX + i * CELL_W;
        QRect cellRect(x, startY, CELL_W - 4, CELL_H);
        bool isActive = (i == m_activeIndex);

        // Cell background
        if (isActive) {
            p.setBrush(QColor("#4FC3F7").lighter(120).darker(180));
            p.setPen(QPen(QColor("#4FC3F7"), 2));
        } else {
            p.setBrush(QColor("#1E1E2E"));
            p.setPen(QPen(QColor("#2A2A3E"), 1));
        }
        p.drawRoundedRect(cellRect, 6, 6);

        // Glow for active element
        if (isActive) {
            QPen glowPen(QColor("#4FC3F7"));
            glowPen.setWidth(2);
            p.setPen(glowPen);
            p.setBrush(Qt::NoBrush);
            p.drawRoundedRect(cellRect.adjusted(-2, -2, 2, 2), 8, 8);
        }

        // Value text
        p.setFont(dataFont);
        p.setPen(isActive ? QColor("#4FC3F7") : QColor("#A8E6CF"));
        QString txt = isActive ? QString("(%1)").arg(m_values[i]) : QString::number(m_values[i]);
        p.drawText(cellRect, Qt::AlignCenter, txt);

        // Index label below
        p.setFont(idxFont);
        p.setPen(QColor("#8888AA"));
        QRect idxRect(x, startY + CELL_H + 4, CELL_W - 4, 20);
        p.drawText(idxRect, Qt::AlignCenter, QString::number(i));
    }
}

// ============================================================
// ArrayWorker — runs core logic on background thread
// ============================================================
void ArrayWorker::run() {
    switch (m_op) {
        case InsertEnd: m_arr->insertEnd(m_v1); break;
        case InsertAt:  m_arr->insertAt(m_v1, m_v2); break;
        case DeleteAt:  m_arr->deleteAt(m_v1); break;
        case Search:    m_arr->search(m_v1); break;
        case Display:   m_arr->display(); break;
    }
    emit finished();
}

// ============================================================
// ArrayView — main view widget
// ============================================================
ArrayView::ArrayView(QWidget* parent)
    : ModulePanel("Array", "#4FC3F7", parent)
{
    // Create a capacity-20 array
    m_array = new Array(20);

    // Embed canvas inside the canvas area
    m_arrayCanvas = new ArrayCanvas(canvasArea());
    QVBoxLayout* canvasLayout = new QVBoxLayout(canvasArea());
    canvasLayout->setContentsMargins(24, 24, 24, 24);
    canvasLayout->addWidget(m_arrayCanvas, 1);
    canvasArea()->setLayout(canvasLayout);

    setupOps();

    // Hook into GlobalGuiNotifier signals
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::arrayStateChanged, this, &ArrayView::onArrayState, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::stepLogged,        this, &ArrayView::onStep,       Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::resultLogged,      this, &ArrayView::onResult,     Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::errorLogged,       this, &ArrayView::onError,      Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::headerLogged,      this, &ArrayView::onHeader,     Qt::QueuedConnection);

    connect(this, &ModulePanel::runRequested,   this, &ArrayView::onRun);
    connect(this, &ModulePanel::resetRequested, this, &ArrayView::onReset);
    connect(operationList(), &QListWidget::currentRowChanged, this, &ArrayView::onOpSelected);
}

void ArrayView::setupOps() {
    operationList()->addItem("Insert at End");
    operationList()->addItem("Insert at Index");
    operationList()->addItem("Delete at Index");
    operationList()->addItem("Search Value");
    operationList()->addItem("Display");
    operationList()->setCurrentRow(0);
}

void ArrayView::onOpSelected(int row) {
    bool needIndex = (row == 1 || row == 2);
    input2Label()->setVisible(needIndex);
    input2()->setVisible(needIndex);

    switch (row) {
        case 0: input1Label()->setText("Value:"); break;
        case 1: input1Label()->setText("Value:"); input2Label()->setText("Index:"); break;
        case 2: input1Label()->setText("Index:"); break;
        case 3: input1Label()->setText("Value:"); break;
        case 4: input1()->hide(); input1Label()->hide(); break;
    }
    if (row != 4) { input1()->show(); input1Label()->show(); }
}

void ArrayView::onRun() {
    int row = operationList()->currentRow();
    bool ok1 = true, ok2 = true;

    ArrayWorker::Op op;
    int v1 = 0, v2 = 0;

    switch (row) {
        case 0: op = ArrayWorker::InsertEnd; v1 = input1()->text().toInt(&ok1); break;
        case 1: op = ArrayWorker::InsertAt;  v1 = input1()->text().toInt(&ok1); v2 = input2()->text().toInt(&ok2); break;
        case 2: op = ArrayWorker::DeleteAt;  v1 = input1()->text().toInt(&ok1); break;
        case 3: op = ArrayWorker::Search;    v1 = input1()->text().toInt(&ok1); break;
        default: op = ArrayWorker::Display; break;
    }

    if (!ok1 || !ok2) {
        logError("Invalid input. Please enter valid integers.");
        return;
    }

    clearLog();
    setRunning(true);

    m_thread = new QThread(this);
    m_worker = new ArrayWorker(m_array, op, v1, v2);
    m_worker->moveToThread(m_thread);

    connect(m_thread, &QThread::started,  m_worker, &ArrayWorker::run);
    connect(m_worker, &ArrayWorker::finished, this, &ArrayView::onWorkerFinished, Qt::QueuedConnection);
    connect(m_worker, &ArrayWorker::finished, m_thread, &QThread::quit);
    connect(m_thread, &QThread::finished,  m_thread, &QThread::deleteLater);
    connect(m_thread, &QThread::finished,  m_worker, &ArrayWorker::deleteLater);

    m_thread->start();
}

void ArrayView::onReset() {
    delete m_array;
    m_array = new Array(20);
    m_arrayCanvas->clear();
    clearLog();
    logResult("Array cleared.");
    setRunning(false);
}

void ArrayView::onArrayState(const int* arr, int size, int activeIndex) {
    if (arr && size > 0) {
        m_arrayCanvas->updateState(arr, size, activeIndex);
    } else {
        m_arrayCanvas->clear();
    }
}

void ArrayView::onStep(int n, const QString& msg)         { logStep(n, msg); }
void ArrayView::onResult(const QString& msg)               { logResult(msg); }
void ArrayView::onError(const QString& msg)                { logError(msg); }
void ArrayView::onHeader(const QString& mod, const QString& op) { logHeader(mod, op); }

void ArrayView::onWorkerFinished() {
    setRunning(false);
    // Show final state
    onArrayState(m_array->getArray(), m_array->getSize(), -1);
}

void ArrayView::setRunning(bool running) {
    runButton()->setEnabled(!running);
    statusLabel()->setText(running ? "⚙ Running..." : "");
}
