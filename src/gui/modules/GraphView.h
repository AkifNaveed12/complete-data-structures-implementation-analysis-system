#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include "ModulePanel.h"
#include "../../core/graph/graph.h"
#include "../../gui/GlobalGuiNotifier.h"
#include <QThread>
#include <QLabel>
#include <QVBoxLayout>

class GraphWorker : public QObject {
    Q_OBJECT
public:
    enum Op { AddEdge, BFS, DFS, Dijkstra, Kruskal, Prim, DisplayMatrix, DisplayList };
    GraphWorker(Graph* g, Op op, int v1=0, int v2=0, int w=1)
        : m_g(g), m_op(op), m_v1(v1), m_v2(v2), m_w(w) {}

public slots:
    void run() {
        switch (m_op) {
            case AddEdge: m_g->addEdge(m_v1, m_v2, m_w); break;
            case BFS: m_g->bfs(m_v1); break;
            case DFS: m_g->dfs(m_v1); break;
            case Dijkstra: m_g->dijkstra(m_v1); break;
            case Kruskal: m_g->mstKruskal(); break;
            case Prim: m_g->mstPrim(); break;
            case DisplayMatrix: m_g->displayMatrix(); break;
            case DisplayList: m_g->displayList(); break;
        }
        emit finished();
    }

signals:
    void finished();

private:
    Graph* m_g; Op m_op; int m_v1, m_v2, m_w;
};

class GraphCanvas : public QWidget {
    Q_OBJECT
private:
    Graph* m_graph = nullptr;
    int m_activeNode = -1;
    QVector<QPair<int, int>> m_mstEdges;

public:
    explicit GraphCanvas(QWidget* parent = nullptr);
    void setGraph(Graph* g) { m_graph = g; update(); }
    void setActiveNode(int node) { m_activeNode = node; update(); }
    void clearActive() { m_activeNode = -1; m_mstEdges.clear(); update(); }
    void addMstEdge(int u, int v) { m_mstEdges.append({u, v}); update(); }

protected:
    void paintEvent(QPaintEvent* event) override;
};

class GraphView : public ModulePanel {
    Q_OBJECT
public:
    explicit GraphView(QWidget* parent = nullptr);

private slots:
    void onRun();
    void onReset();
    void onStep(int n, const QString& msg);
    void onResult(const QString& msg) { logResult(msg); }
    void onError(const QString& msg) { logError(msg); }
    void onHeader(const QString& mod, const QString& op) { logHeader(mod, op); }
    void onWorkerFinished();
    void onOpSelected(int row);
    void onStateChanged();

private:
    Graph* m_graph;
    GraphCanvas* m_canvas;
    QThread* m_thread = nullptr;
    GraphWorker* m_worker = nullptr;
};

#endif
