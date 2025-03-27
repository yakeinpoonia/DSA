#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int spanningTree(int v, vector<pair<int, int>> adj[]) {
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        vector<bool> isMST(v, false);
        vector<int> parent(v, -1);
        int cost = 0;

        pq.push({0, {0, -1}}); // Start from node 0

        while (!pq.empty()) {
            int wt = pq.top().first;
            int node = pq.top().second.first;
            int par = pq.top().second.second;
            pq.pop();

            if (!isMST[node]) {
                isMST[node] = true;
                cost += wt;
                parent[node] = par;

                for (auto &edge : adj[node]) {
                    int adjNode = edge.first;
                    int edgeWeight = edge.second;
                    if (!isMST[adjNode]) {
                        pq.push({edgeWeight, {adjNode, node}});
                    }
                }
            }
        }

        // Print the edges in the Minimum Spanning Tree
        cout << "Edges in MST:" << endl;
        for (int i = 1; i < v; i++) { // Start from 1 since 0 has no parent
            cout << parent[i] << " - " << i << endl;
        }

        return cost;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<pair<int, int>> adj[V];
    cout << "Enter edges in format (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Since the graph is undirected
    }

    Solution sol;
    cout << "Minimum Spanning Tree Cost: " << sol.spanningTree(V, adj) << endl;

    return 0;
}
