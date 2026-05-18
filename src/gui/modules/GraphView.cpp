#include "GraphView.h"
#include <QPainter>
#include <QPainterPath>
#include <QRegularExpression>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// GraphCanvas
// ─────────────────────────────────────────────────────────────────────────────
GraphCanvas::GraphCanvas(QWidget* parent) : QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void GraphCanvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Dark background
    p.fillRect(rect(), QColor("#0d0d0d"));

    if (!m_graph) return;

    int N = m_graph->getNumVertices();
    if (N <= 0) return;

    // Calculate positions
    int cx = width() / 2;
    int cy = height() / 2;
    int r = qMin(width(), height()) / 2 - 50;
    if (r < 50) r = 50;

    QVector<QPoint> pts(N);
    const double PI = 3.141592653589793;
    for (int i = 0; i < N; i++) {
        double angle = i * 2.0 * PI / N - PI / 2.0; // Start at top
        pts[i] = QPoint(cx + r * std::cos(angle), cy + r * std::sin(angle));
    }

    // 1. Draw Edges
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            int w = m_graph->getWeight(u, v);
            if (w <= 0 || w == INF) continue;

            // To prevent duplicate lines for undirected graphs:
            if (!m_graph->directed() && u > v) continue;

            QPoint p1 = pts[u];
            QPoint p2 = pts[v];

            // Check if MST edge
            bool isMst = false;
            for (auto& edge : m_mstEdges) {
                if ((edge.first == u && edge.second == v) || (!m_graph->directed() && edge.first == v && edge.second == u)) {
                    isMst = true;
                    break;
                }
            }

            QPen pen;
            if (isMst) {
                pen = QPen(QColor("#69F0AE"), 4); // Glowing green
            } else {
                pen = QPen(QColor("#2a2a3e"), 1.5); // Sleek dark edge
            }
            p.setPen(pen);
            p.drawLine(p1, p2);

            // Draw arrow if directed
            if (m_graph->directed()) {
                double angle = std::atan2(p2.y() - p1.y(), p2.x() - p1.x());
                int nodeR = 20;
                QPoint arrowHead(p2.x() - nodeR * std::cos(angle), p2.y() - nodeR * std::sin(angle));
                double arrowSize = 10;
                QPoint arrowP1(arrowHead.x() - arrowSize * std::cos(angle - PI/6), arrowHead.y() - arrowSize * std::sin(angle - PI/6));
                QPoint arrowP2(arrowHead.x() - arrowSize * std::cos(angle + PI/6), arrowHead.y() - arrowSize * std::sin(angle + PI/6));
                p.setBrush(QColor(isMst ? "#69F0AE" : "#2a2a3e"));
                p.drawPolygon(QPolygon() << arrowHead << arrowP1 << arrowP2);
            }

            // Draw Weight
            QPoint mid = (p1 + p2) / 2;
            p.setPen(QColor("#8888aa"));
            p.setFont(QFont("Consolas", 10));
            p.drawText(mid + QPoint(5, -5), QString::number(w));
        }
    }

    // 2. Draw Vertices
    int nodeR = 20;
    for (int i = 0; i < N; i++) {
        QPoint pt = pts[i];
        bool isActive = (i == m_activeNode);

        if (isActive) {
            p.setBrush(QColor("#FF7043"));
            p.setPen(QPen(QColor("#FFCCBC"), 3));
        } else {
            p.setBrush(QColor("#1a1a2e"));
            p.setPen(QPen(QColor("#E57373"), 1.5));
        }

        p.drawEllipse(pt, nodeR, nodeR);

        p.setPen(Qt::white);
        p.setFont(QFont("Segoe UI", 10, QFont::Bold));
        p.drawText(QRect(pt.x() - nodeR, pt.y() - nodeR, nodeR * 2, nodeR * 2), Qt::AlignCenter, QString::number(i));
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// GraphView
// ─────────────────────────────────────────────────────────────────────────────
GraphView::GraphView(QWidget* parent) : ModulePanel("Graph", "#E57373", parent) {
    m_graph = new Graph(10); // Default 10 vertices
    
    // Create visual canvas
    m_canvas = new GraphCanvas(canvasArea());
    m_canvas->setGraph(m_graph);
    
    QVBoxLayout* vl = new QVBoxLayout(canvasArea());
    vl->setContentsMargins(0, 0, 0, 0);
    vl->addWidget(m_canvas);
    canvasArea()->setLayout(vl);
    
    operationList()->addItems({"Add Edge", "BFS", "DFS", "Dijkstra", "MST Kruskal", "MST Prim", "Display Matrix", "Display List"});
    operationList()->setCurrentRow(0);
    
    auto* notifier = GlobalGuiNotifier::instance();
    connect(notifier, &GlobalGuiNotifier::stepLogged,   this, &GraphView::onStep, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::resultLogged, this, &GraphView::onResult, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::errorLogged,  this, &GraphView::onError, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::headerLogged, this, &GraphView::onHeader, Qt::QueuedConnection);
    connect(notifier, &GlobalGuiNotifier::stateChanged, this, &GraphView::onStateChanged, Qt::QueuedConnection);
    
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
    m_canvas->clearActive();
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

void GraphView::onStep(int n, const QString& msg) {
    logStep(n, msg);

    // Parse active node (e.g. "Visiting (3)" or "Selected vertex (3)")
    QRegularExpression re("\\((\\d+)\\)");
    QRegularExpressionMatch match = re.match(msg);
    if (match.hasMatch()) {
        m_canvas->setActiveNode(match.captured(1).toInt());
    }

    // Parse MST edges (e.g. "Added edge (3)-(4)")
    QRegularExpression mstRe("Added edge \\((\\d+)\\)-\\((\\d+)\\)");
    QRegularExpressionMatch mstMatch = mstRe.match(msg);
    if (mstMatch.hasMatch()) {
        int u = mstMatch.captured(1).toInt();
        int v = mstMatch.captured(2).toInt();
        m_canvas->addMstEdge(u, v);
    }
}

void GraphView::onWorkerFinished() {
    runButton()->setEnabled(true);
}

void GraphView::onReset() {
    delete m_graph;
    m_graph = new Graph(10);
    m_canvas->setGraph(m_graph);
    m_canvas->clearActive();
    clearLog();
    logResult("Graph cleared.");
}

void GraphView::onStateChanged() {
    m_canvas->update();
}
