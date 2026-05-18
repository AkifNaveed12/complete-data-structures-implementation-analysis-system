#include "graph.h"

using namespace std;

Graph::Graph(int v, bool directed) {
    if (v > MAX_VERTICES) v = MAX_VERTICES;
    numVertices = v;
    isDirected = directed;
    for (int i = 0; i < numVertices; i++) {
        listSizes[i] = 0;
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
            adjList[i][j] = -1;
            adjListWeights[i][j] = 0;
        }
    }
}

void Graph::addEdge(int u, int v, int weight) {
    if (u >= numVertices || v >= numVertices || u < 0 || v < 0) {
        printError("Invalid vertices");
        return;
    }
    
    adjMatrix[u][v] = weight;
    adjList[u][listSizes[u]] = v;
    adjListWeights[u][listSizes[u]] = weight;
    listSizes[u]++;
    
    if (!isDirected && u != v) {
        adjMatrix[v][u] = weight;
        adjList[v][listSizes[v]] = u;
        adjListWeights[v][listSizes[v]] = weight;
        listSizes[v]++;
    }
}

void Graph::displayMatrix() {
    printHeader("Graph", "Display Matrix");
    printStep(1, "BEFORE: Matrix state");
    
    for (int i = 0; i < numVertices; i++) {
        string row = "Row " + to_string(i) + ": [ ";
        for (int j = 0; j < numVertices; j++) {
            row += to_string(adjMatrix[i][j]);
            if (j < numVertices - 1) row += ", ";
        }
        row += " ]";
        printStep(2, row);
    }
    
    printResult("AFTER: Displayed adjacency matrix");
    Performance::log("Graph", "DisplayMatrix", numVertices * numVertices, 0);
}

void Graph::displayList() {
    printHeader("Graph", "Display List");
    printStep(1, "BEFORE: List state");
    
    for (int i = 0; i < numVertices; i++) {
        string row = to_string(i) + " -> ";
        for (int j = 0; j < listSizes[i]; j++) {
            row += to_string(adjList[i][j]);
            if (adjListWeights[i][j] != 1) {
                row += "(w:" + to_string(adjListWeights[i][j]) + ")";
            }
            if (j < listSizes[i] - 1) row += ", ";
        }
        printStep(2, row);
    }
    
    printResult("AFTER: Displayed adjacency list");
    Performance::log("Graph", "DisplayList", numVertices, 0);
}

void Graph::bfs(int start) {
    printHeader("Graph", "BFS");
    if (start < 0 || start >= numVertices) {
        printError("Invalid start vertex");
        return;
    }
    
    string beforeState = "BEFORE: Starting BFS from " + to_string(start);
    printStep(1, beforeState);
    
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    
    queue[rear++] = start;
    visited[start] = true;
    
    int steps = 0;
    int comps = 0;
    string resultPath = "";
    
    while (front < rear) {
        int curr = queue[front++];
        resultPath += to_string(curr) + " ";
        printStep(steps + 2, "Visiting " + highlight(curr));
        sleep_ms(300);
        steps++;
        
        for (int i = 0; i < listSizes[curr]; i++) {
            int adj = adjList[curr][i];
            comps++;
            if (!visited[adj]) {
                visited[adj] = true;
                queue[rear++] = adj;
            }
        }
    }
    
    printResult("AFTER: BFS Path: " + resultPath);
    Performance::log("Graph", "BFS", steps, comps);
}

void Graph::dfsRecursive(int curr, bool visited[], int& steps) {
    visited[curr] = true;
    printStep(steps + 2, "Visiting " + highlight(curr));
    sleep_ms(300);
    steps++;
    
    for (int i = 0; i < listSizes[curr]; i++) {
        int adj = adjList[curr][i];
        if (!visited[adj]) {
            dfsRecursive(adj, visited, steps);
        }
    }
    printStep(steps + 2, "Backtrack from " + to_string(curr));
}

void Graph::dfs(int start) {
    printHeader("Graph", "DFS");
    if (start < 0 || start >= numVertices) {
        printError("Invalid start vertex");
        return;
    }
    
    string beforeState = "BEFORE: Starting DFS from " + to_string(start);
    printStep(1, beforeState);
    
    bool visited[MAX_VERTICES] = {false};
    int steps = 0;
    
    dfsRecursive(start, visited, steps);
    
    printResult("AFTER: DFS Complete");
    Performance::log("Graph", "DFS", steps, 0);
}

void Graph::dijkstra(int src) {
    printHeader("Graph", "Dijkstra");
    if (src < 0 || src >= numVertices) {
        printError("Invalid start vertex");
        return;
    }
    
    printStep(1, "BEFORE: Starting Dijkstra from " + to_string(src));
    
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];
    
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }
    dist[src] = 0;
    
    int steps = 0;
    int comps = 0;
    
    for (int count = 0; count < numVertices - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < numVertices; v++) {
            comps++;
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        sptSet[u] = true;
        steps++;
        
        printStep(steps + 1, "Selected vertex " + highlight(u) + " with distance " + to_string(dist[u]));
        sleep_ms(300);
        
        for (int v = 0; v < numVertices; v++) {
            comps++;
            if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                printStep(steps + 2, "Relaxed edge " + to_string(u) + "->" + to_string(v) + ", new distance=" + to_string(dist[v]));
            }
        }
    }
    
    string res = "";
    for(int i=0; i<numVertices; i++) {
        res += "[" + to_string(i) + ":" + (dist[i] == INF ? "INF" : to_string(dist[i])) + "] ";
    }
    
    printResult("AFTER: Distances: " + res);
    Performance::log("Graph", "Dijkstra", steps, comps);
}

void Graph::sortEdges(int edges[][3], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j][2] > edges[j + 1][2]) {
                int t0 = edges[j][0], t1 = edges[j][1], t2 = edges[j][2];
                edges[j][0] = edges[j + 1][0]; edges[j][1] = edges[j + 1][1]; edges[j][2] = edges[j + 1][2];
                edges[j + 1][0] = t0; edges[j + 1][1] = t1; edges[j + 1][2] = t2;
            }
        }
    }
}

void Graph::mstKruskal() {
    printHeader("Graph", "MST Kruskal");
    printStep(1, "BEFORE: Starting Kruskal's MST");
    
    int edges[MAX_VERTICES * MAX_VERTICES][3];
    int E = 0;
    
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (adjMatrix[i][j]) {
                edges[E][0] = i;
                edges[E][1] = j;
                edges[E][2] = adjMatrix[i][j];
                E++;
            }
        }
    }
    
    sortEdges(edges, E);
    printStep(2, "Sorted edges by weight");
    
    int parent[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) parent[i] = i;
    
    int mstWeight = 0;
    int steps = 0;
    
    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1];
        
        int rootU = u, rootV = v;
        while (parent[rootU] != rootU) rootU = parent[rootU];
        while (parent[rootV] != rootV) rootV = parent[rootV];
        
        if (rootU != rootV) {
            parent[rootU] = rootV;
            mstWeight += edges[i][2];
            printStep(steps + 3, "Added edge " + highlight(u) + "-" + highlight(v) + " (w:" + to_string(edges[i][2]) + ")");
            sleep_ms(300);
            steps++;
        } else {
            printStep(steps + 3, "Rejected edge " + to_string(u) + "-" + to_string(v) + " (creates cycle)");
        }
    }
    
    printResult("AFTER: MST Kruskal Total Weight: " + to_string(mstWeight));
    Performance::log("Graph", "MST_Kruskal", steps, E);
}

void Graph::mstPrim() {
    printHeader("Graph", "MST Prim");
    printStep(1, "BEFORE: Starting Prim's MST from vertex 0");
    
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];
    
    for (int i = 0; i < numVertices; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    int steps = 0;
    int mstWeight = 0;
    
    for (int count = 0; count < numVertices - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < numVertices; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        mstSet[u] = true;
        
        if (parent[u] != -1) {
            printStep(steps + 2, "Added edge " + highlight(parent[u]) + "-" + highlight(u) + " (w:" + to_string(adjMatrix[u][parent[u]]) + ")");
            mstWeight += adjMatrix[u][parent[u]];
            sleep_ms(300);
            steps++;
        }
        
        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }
    
    printResult("AFTER: MST Prim Total Weight: " + to_string(mstWeight));
    Performance::log("Graph", "MST_Prim", steps, 0);
}
