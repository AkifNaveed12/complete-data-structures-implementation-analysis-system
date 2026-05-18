#ifndef GRAPH_H
#define GRAPH_H

#include "../../analysis/visual.h"
#include "../../analysis/performance.h"
#include <string>

#define MAX_VERTICES 20
#define INF 999999

class Graph {
private:
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int adjList[MAX_VERTICES][MAX_VERTICES]; // Stores target vertex
    int adjListWeights[MAX_VERTICES][MAX_VERTICES]; // Stores edge weights
    int listSizes[MAX_VERTICES];
    int numVertices;
    bool isDirected;

    void sortEdges(int edges[][3], int E);
    void dfsRecursive(int curr, bool visited[], int& steps);

public:
    Graph(int v, bool directed = false);
    void addEdge(int u, int v, int weight = 1);
    void displayMatrix();
    void displayList();
    
    void bfs(int start);
    void dfs(int start);
    void dijkstra(int src);
    void mstKruskal();
    void mstPrim();
    int getNumVertices() const { return numVertices; }
    int getWeight(int u, int v) const { return (u >= 0 && u < numVertices && v >= 0 && v < numVertices) ? adjMatrix[u][v] : 0; }
    bool directed() const { return isDirected; }
};

#endif
