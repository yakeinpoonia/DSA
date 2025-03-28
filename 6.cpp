#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(v, vector<int>(v, 0)); // Initialize matrix with 0
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Since it's an undirected graph
    }

    void displayMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void DFS(int start, vector<bool>& visited) {
        cout << start << " ";
        visited[start] = true;

        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[start][i] == 1 && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    bool isConnected() {
        vector<bool> visited(vertices, false);
        DFS(0, visited); // Start DFS from node 0

        for (bool v : visited) {
            if (!v) return false; // If any node is unvisited, graph is not connected
        }
        return true;
    }

    int countConnectedComponents() {
        vector<bool> visited(vertices, false);
        int components = 0;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                cout << "Component " << (components + 1) << ": ";
                DFS(i, visited);
                cout << endl;
                components++;
            }
        }
        return components;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.displayMatrix();

    vector<bool> visited(V, false);
    cout << "DFS Traversal: ";
    g.DFS(0, visited);
    cout << endl;

    g.BFS(0);

    if (g.isConnected()) {
        cout << "The graph is connected.\n";
    } else {
        int components = g.countConnectedComponents();
        cout << "The graph is not connected and has " << components << " connected components.\n";
    }

    return 0;
}
