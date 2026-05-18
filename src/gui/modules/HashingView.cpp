#include "HashingView.h"

HashingView::HashingView(QWidget* parent) : ModulePanel("Hashing", "#4DB6AC", parent) {
    m_hc = new HashChaining();
    m_hp = new HashLinearProbe();
    
    QLabel* info = new QLabel("Hash Table Size: 10<br>See the log panel for collisions and probing steps.", canvasArea());
    info->setStyleSheet("color: #8888aa; font-size: 16px;");
    info->setAlignment(Qt::AlignCenter);
    QVBoxLayout* vl = new QVBoxLayout(canvasArea());
    vl->addWidget(info);
    canvasArea()->setLayout(vl);
    
    operationList()->addItems({"Insert (Chaining)", "Display (Chaining)", "Insert (Linear Probing)", "Display (Linear Probing)"});
    operationList()->setCurrentRow(0);
    
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged, this, &HashingView::onStep, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::resultLogged, this, &HashingView::onResult, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::errorLogged, this, &HashingView::onError, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::headerLogged, this, &HashingView::onHeader, Qt::QueuedConnection);
    
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
}

void HashingView::onRun() {
    int row = operationList()->currentRow();
    int key = 0; bool ok;
    if (row == 0 || row == 2) key = input1()->text().toInt(&ok);
    
    clearLog();
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

void HashingView::onWorkerFinished() {
    runButton()->setEnabled(true);
}

void HashingView::onReset() {
    delete m_hc; delete m_hp;
    m_hc = new HashChaining();
    m_hp = new HashLinearProbe();
    clearLog();
    logResult("Hash tables cleared.");
}
