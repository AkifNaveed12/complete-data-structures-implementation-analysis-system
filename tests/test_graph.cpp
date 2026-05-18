#include "../src/core/graph/graph.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Testing Graph Module ===\n";
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);
    
    g.displayMatrix();
    g.displayList();
    
    g.bfs(0);
    g.dfs(0);
    g.dijkstra(0);
    g.mstKruskal();
    g.mstPrim();
    
    Performance::display();
    return 0;
}
