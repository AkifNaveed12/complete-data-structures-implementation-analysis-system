#include "GraphView.h"

GraphView::GraphView(QWidget* parent) : ModulePanel("Graph", "#E57373", parent) {
    m_graph = new Graph(10); // Default 10 vertices
    
    QLabel* info = new QLabel("Visual canvas not required for advanced algorithms.<br>Execution logs will be shown in the right panel.", canvasArea());
    info->setStyleSheet("color: #8888aa; font-size: 16px;");
    info->setAlignment(Qt::AlignCenter);
    QVBoxLayout* vl = new QVBoxLayout(canvasArea());
    vl->addWidget(info);
    canvasArea()->setLayout(vl);
    
    operationList()->addItems({"Add Edge", "BFS", "DFS", "Dijkstra", "MST Kruskal", "MST Prim", "Display Matrix", "Display List"});
    operationList()->setCurrentRow(0);
    
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged, this, &GraphView::onStep, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::resultLogged, this, &GraphView::onResult, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::errorLogged, this, &GraphView::onError, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::headerLogged, this, &GraphView::onHeader, Qt::QueuedConnection);
    
    connect(this, &ModulePanel::runRequested, this, &GraphView::onRun);
    connect(this, &ModulePanel::resetRequested, this, &GraphView::onReset);
    connect(operationList(), &QListWidget::currentRowChanged, this, &GraphView::onOpSelected);
}

void GraphView::onOpSelected(int row) {
    input1()->show(); input1Label()->show();
    input2()->hide(); input2Label()->hide();
    
    if (row == 0) { // Add Edge
        input1Label()->setText("From:"); input1()->setPlaceholderText("0");
        input2Label()->setText("To:"); input2()->setPlaceholderText("1");
        input2()->show(); input2Label()->show();
    } else if (row >= 1 && row <= 3) { // BFS, DFS, Dijkstra
        input1Label()->setText("Start Node:"); input1()->setPlaceholderText("0");
    } else {
        input1()->hide(); input1Label()->hide();
    }
}

void GraphView::onRun() {
    int row = operationList()->currentRow();
    int v1 = 0, v2 = 0; bool ok;
    
    if (row == 0) {
        v1 = input1()->text().toInt(&ok); v2 = input2()->text().toInt();
    } else if (row >= 1 && row <= 3) {
        v1 = input1()->text().toInt(&ok);
    }
    
    clearLog();
    runButton()->setEnabled(false);
    
    m_thread = new QThread(this);
    m_worker = new GraphWorker(m_graph, static_cast<GraphWorker::Op>(row), v1, v2);
    m_worker->moveToThread(m_thread);
    
    connect(m_thread, &QThread::started, m_worker, &GraphWorker::run);
    connect(m_worker, &GraphWorker::finished, this, &GraphView::onWorkerFinished, Qt::QueuedConnection);
    connect(m_worker, &GraphWorker::finished, m_thread, &QThread::quit);
    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    connect(m_thread, &QThread::finished, m_worker, &GraphWorker::deleteLater);
    
    m_thread->start();
}

void GraphView::onWorkerFinished() {
    runButton()->setEnabled(true);
}

void GraphView::onReset() {
    delete m_graph;
    m_graph = new Graph(10);
    clearLog();
    logResult("Graph cleared.");
}
