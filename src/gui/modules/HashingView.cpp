#include "HashingView.h"
#include <QPainter>
#include <QRegularExpression>

// ─────────────────────────────────────────────────────────────────────────────
// HashCanvas
// ─────────────────────────────────────────────────────────────────────────────
HashCanvas::HashCanvas(QWidget* parent) : QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(450);
}

void HashCanvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Dark background
    p.fillRect(rect(), QColor("#0d0d0d"));

    int startX = 40;
    int startY = 20;
    int slotH = 34;
    int slotW = 70;
    int gapY = 6;

    p.setFont(QFont("Consolas", 10, QFont::Bold));

    if (m_isChaining) {
        if (!m_hc) return;
        HashNode* const* table = m_hc->getTable();
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            int y = startY + i * (slotH + gapY);
            bool isActive = (i == m_activeIndex);

            // Draw index slot
            if (isActive) {
                p.setBrush(QColor("#FF7043").darker(150));
                p.setPen(QPen(QColor("#FF7043"), 2));
            } else {
                p.setBrush(QColor("#1e1e2e"));
                p.setPen(QPen(QColor("#80CBC4"), 1));
            }
            p.drawRoundedRect(startX, y, slotW, slotH, 4, 4);

            p.setPen(Qt::white);
            p.drawText(QRect(startX, y, slotW, slotH), Qt::AlignCenter, QString("[%1]").arg(i));

            // Draw chain
            HashNode* temp = table[i];
            int currX = startX + slotW + 20;
            while (temp) {
                // Draw Arrow
                p.setPen(QPen(QColor("#80CBC4"), 1.5));
                p.drawLine(currX - 15, y + slotH/2, currX - 2, y + slotH/2);
                p.drawLine(currX - 6, y + slotH/2 - 4, currX - 2, y + slotH/2);
                p.drawLine(currX - 6, y + slotH/2 + 4, currX - 2, y + slotH/2);

                // Draw Node
                p.setBrush(QColor("#1A237E"));
                p.setPen(QPen(QColor("#80CBC4"), 1));
                p.drawRoundedRect(currX, y, slotW, slotH, 4, 4);

                p.setPen(QColor("#E0F2F1"));
                p.drawText(QRect(currX, y, slotW, slotH), Qt::AlignCenter, QString::number(temp->key));

                currX += slotW + 20;
                temp = temp->next;
            }
        }
    } else {
        if (!m_hp) return;
        const int* table = m_hp->getTable();

        for (int i = 0; i < TABLE_SIZE; i++) {
            int y = startY + i * (slotH + gapY);
            bool isActive = (i == m_activeIndex);
            int val = table[i];

            // Draw index slot
            p.setBrush(QColor("#263238"));
            p.setPen(QPen(QColor("#4db6ac"), 1));
            p.drawRoundedRect(startX, y, 40, slotH, 4, 4);
            p.setPen(Qt::white);
            p.drawText(QRect(startX, y, 40, slotH), Qt::AlignCenter, QString("[%1]").arg(i));

            // Draw value box
            int valX = startX + 50;
            if (isActive) {
                p.setBrush(QColor("#FF7043"));
                p.setPen(QPen(QColor("#FFCCBC"), 2));
            } else {
                p.setBrush(QColor("#1e1e2e"));
                p.setPen(QPen(QColor("#80CBC4"), 1));
            }
            p.drawRoundedRect(valX, y, 100, slotH, 4, 4);

            p.setPen(isActive ? Qt::white : (val == -1 ? QColor("#444466") : QColor("#E0F2F1")));
            p.drawText(QRect(valX, y, 100, slotH), Qt::AlignCenter, val == -1 ? "(empty)" : QString::number(val));
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// HashingView
// ─────────────────────────────────────────────────────────────────────────────
HashingView::HashingView(QWidget* parent) : ModulePanel("Hashing", "#4DB6AC", parent) {
    m_hc = new HashChaining();
    m_hp = new HashLinearProbe();
    
    m_canvas = new HashCanvas(canvasArea());
    m_canvas->setChaining(m_hc);
    
    QVBoxLayout* vl = new QVBoxLayout(canvasArea());
    vl->setContentsMargins(16, 16, 16, 16);
    vl->addWidget(m_canvas, 1);
    canvasArea()->setLayout(vl);
    
    operationList()->addItems({"Insert (Chaining)", "Display (Chaining)", "Insert (Linear Probing)", "Display (Linear Probing)"});
    operationList()->setCurrentRow(0);
    
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged, this, &HashingView::onStep, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::resultLogged, this, &HashingView::onResult, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::errorLogged, this, &HashingView::onError, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::headerLogged, this, &HashingView::onHeader, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::stateChanged, this, &HashingView::onStateChanged, Qt::QueuedConnection);
    
    connect(this, &ModulePanel::runRequested, this, &HashingView::onRun);
    connect(this, &ModulePanel::resetRequested, this, &HashingView::onReset);
    connect(operationList(), &QListWidget::currentRowChanged, this, &HashingView::onOpSelected);
}

void HashingView::onOpSelected(int row) {
    if (row == 0 || row == 2) { // Insert
        input1()->show(); input1Label()->show();
        input1Label()->setText("Key:");
        input1()->setPlaceholderText("e.g. 42");
    } else { // Display
        input1()->hide(); input1Label()->hide();
    }
    input2()->hide(); input2Label()->hide();
    
    if (row <= 1) {
        m_canvas->setChaining(m_hc);
    } else {
        m_canvas->setProbing(m_hp);
    }
}

void HashingView::onRun() {
    int row = operationList()->currentRow();
    int key = 0; bool ok;
    if (row == 0 || row == 2) key = input1()->text().toInt(&ok);
    
    clearLog();
    m_canvas->clearActive();
    runButton()->setEnabled(false);
    
    HashWorker::Op op;
    if(row == 0) op = HashWorker::InsertChaining;
    else if(row == 1) op = HashWorker::DisplayChaining;
    else if(row == 2) op = HashWorker::InsertProbing;
    else op = HashWorker::DisplayProbing;
    
    m_thread = new QThread(this);
    m_worker = new HashWorker(m_hc, m_hp, op, key);
    m_worker->moveToThread(m_thread);
    
    connect(m_thread, &QThread::started, m_worker, &HashWorker::run);
    connect(m_worker, &HashWorker::finished, this, &HashingView::onWorkerFinished, Qt::QueuedConnection);
    connect(m_worker, &HashWorker::finished, m_thread, &QThread::quit);
    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    connect(m_thread, &QThread::finished, m_worker, &HashWorker::deleteLater);
    
    m_thread->start();
}

void HashingView::onStep(int n, const QString& msg) {
    logStep(n, msg);
    
    // Parse active index being searched, inserted or probed
    QRegularExpression re("\\[(\\d+)\\]");
    QRegularExpressionMatch match = re.match(msg);
    if (match.hasMatch()) {
        m_canvas->setActiveIndex(match.captured(1).toInt());
    } else {
        QRegularExpression re2("index (\\d+)");
        QRegularExpressionMatch match2 = re2.match(msg);
        if (match2.hasMatch()) {
            m_canvas->setActiveIndex(match2.captured(1).toInt());
        }
    }
}

void HashingView::onWorkerFinished() {
    runButton()->setEnabled(true);
    m_canvas->update();
}

void HashingView::onReset() {
    delete m_hc; delete m_hp;
    m_hc = new HashChaining();
    m_hp = new HashLinearProbe();
    
    int row = operationList()->currentRow();
    if (row <= 1) {
        m_canvas->setChaining(m_hc);
    } else {
        m_canvas->setProbing(m_hp);
    }
    m_canvas->clearActive();
    clearLog();
    logResult("Hash tables cleared.");
}

void HashingView::onStateChanged() {
    m_canvas->update();
}
