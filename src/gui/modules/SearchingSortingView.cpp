#include "SearchingSortingView.h"

SearchingSortingView::SearchingSortingView(QWidget* parent) : ModulePanel("Search/Sort", "#CE93D8", parent) {
    QLabel* info = new QLabel("Using predefined array: [64, 34, 25, 12, 22, 11, 90, 88, 45, 33]", canvasArea());
    info->setStyleSheet("color: #8888aa; font-size: 16px;");
    info->setAlignment(Qt::AlignCenter);
    QVBoxLayout* vl = new QVBoxLayout(canvasArea());
    vl->addWidget(info);
    canvasArea()->setLayout(vl);
    
    operationList()->addItems({"Linear Search", "Binary Search", "Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort"});
    operationList()->setCurrentRow(0);
    
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged, this, &SearchingSortingView::onStep, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::resultLogged, this, &SearchingSortingView::onResult, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::errorLogged, this, &SearchingSortingView::onError, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::headerLogged, this, &SearchingSortingView::onHeader, Qt::QueuedConnection);
    
    connect(this, &ModulePanel::runRequested, this, &SearchingSortingView::onRun);
    connect(this, &ModulePanel::resetRequested, this, &SearchingSortingView::onReset);
    connect(operationList(), &QListWidget::currentRowChanged, this, &SearchingSortingView::onOpSelected);
}

void SearchingSortingView::onOpSelected(int row) {
    if (row <= 1) { // Searching
        input1()->show(); input1Label()->show();
        input1Label()->setText("Search Key:");
        input1()->setPlaceholderText("e.g. 25");
    } else { // Sorting
        input1()->hide(); input1Label()->hide();
    }
    input2()->hide(); input2Label()->hide();
}

void SearchingSortingView::onRun() {
    int row = operationList()->currentRow();
    int key = 0; bool ok;
    if (row <= 1) key = input1()->text().toInt(&ok);
    
    clearLog();
    runButton()->setEnabled(false);
    
    m_thread = new QThread(this);
    m_worker = new SSWorker(static_cast<SSWorker::Op>(row), key);
    m_worker->moveToThread(m_thread);
    
    connect(m_thread, &QThread::started, m_worker, &SSWorker::run);
    connect(m_worker, &SSWorker::finished, this, &SearchingSortingView::onWorkerFinished, Qt::QueuedConnection);
    connect(m_worker, &SSWorker::finished, m_thread, &QThread::quit);
    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    connect(m_thread, &QThread::finished, m_worker, &SSWorker::deleteLater);
    
    m_thread->start();
}

void SearchingSortingView::onWorkerFinished() {
    runButton()->setEnabled(true);
}
