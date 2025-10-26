#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// GRAPH REPRESENTATION
// ============================================================================

// Adjacency List
vector<vector<int>> adjList(int n, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto& [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // For undirected
    }
    return adj;
}

// Weighted Graph
vector<vector<pair<int, int>>> adjWeighted(int n, 
                                            vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // For undirected
    }
    return adj;
}

// ============================================================================
// DFS - DEPTH FIRST SEARCH
// ============================================================================

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

// DFS with discovery time and finishing time
int time = 0;
void dfsWithTimes(int node, vector<vector<int>>& adj, 
                  vector<int>& disc, vector<int>& fin) {
    disc[node] = ++time;
    
    for (int neighbor : adj[node]) {
        if (disc[neighbor] == -1) {
            dfsWithTimes(neighbor, adj, disc, fin);
        }
    }
    
    fin[node] = ++time;
}

// ============================================================================
// BFS - BREADTH FIRST SEARCH
// ============================================================================

void bfs(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// BFS with distances
vector<int> bfsDistance(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
    
    return dist;
}

// ============================================================================
// DIJKSTRA'S SHORTEST PATH
// ============================================================================

vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& [v, weight] : adj[u]) {
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// ============================================================================
// FLOYD-WARSHALL (ALL PAIRS SHORTEST PATH)
// ============================================================================

void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

// ============================================================================
// BELLMAN-FORD (DETECT NEGATIVE CYCLES)
// ============================================================================

vector<int> bellmanFord(int start, int n, vector<vector<int>>& edges) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Check for negative cycles
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
            return {};  // Negative cycle detected
        }
    }
    
    return dist;
}

// ============================================================================
// UNION-FIND (FOR MST)
// ============================================================================

class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// ============================================================================
// KRUSKAL'S MST
// ============================================================================

int kruskal(vector<vector<int>>& edges, int n) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int mstWeight = 0;
    
    for (auto& edge : edges) {
        int weight = edge[0], u = edge[1], v = edge[2];
        if (uf.unite(u, v)) {
            mstWeight += weight;
        }
    }
    
    return mstWeight;
}

// ============================================================================
// PRIM'S MST
// ============================================================================

int prim(vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;
    
    pq.push({0, 0});
    int mstWeight = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();
        
        if (inMST[u]) continue;
        inMST[u] = true;
        mstWeight += w;
        
        for (auto& [v, weight] : adj[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }
    
    return mstWeight;
}

// ============================================================================
// TOPOLOGICAL SORT
// ============================================================================

vector<int> topologicalSort(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> inDegree(n, 0);
    
    for (int i = 0; i < n; i++) {
        for (int neighbor : adj[i]) {
            inDegree[neighbor]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        
        for (int neighbor : adj[node]) {
            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return result;
}

// ============================================================================
// TREE DIAMETER
// ============================================================================

pair<int, int> bfsFarthest(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
    
    int farthest = max_element(dist.begin(), dist.end()) - dist.begin();
    return {farthest, dist[farthest]};
}

int treeDiameter(vector<vector<int>>& adj) {
    auto [u, _] = bfsFarthest(0, adj);
    auto [v, diameter] = bfsFarthest(u, adj);
    return diameter;
}

// ============================================================================
// CYCLE DETECTION
// ============================================================================

bool hasCycleUndirected(int node, int parent, 
                        vector<vector<int>>& adj, 
                        vector<bool>& visited) {
    visited[node] = true;
    
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (hasCycleUndirected(neighbor, node, adj, visited)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    
    return false;
}

bool hasCycleDirected(int node, vector<vector<int>>& adj,
                      vector<int>& color) {
    color[node] = 1;  // Gray
    
    for (int neighbor : adj[node]) {
        if (color[neighbor] == 1) {
            return true;  // Back edge found
        }
        if (color[neighbor] == 0 && hasCycleDirected(neighbor, adj, color)) {
            return true;
        }
    }
    
    color[node] = 2;  // Black
    return false;
}

// ============================================================================
// CONNECTED COMPONENTS
// ============================================================================

int connectedComponents(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited);
            count++;
        }
    }
    
    return count;
}

// ============================================================================
// BIPARTITE CHECK
// ============================================================================

bool isBipartite(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> color(n, -1);
    queue<int> q;
    
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);
            
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                
                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testGraphTraversal() {
    cout << "Testing Graph Traversal:" << endl;
    
    int n = 5;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 4}};
    vector<vector<int>> adj = adjList(n, edges);
    
    vector<bool> visited(n, false);
    cout << "DFS: ";
    dfs(0, adj, visited);
    cout << endl;
    
    cout << "BFS: ";
    bfs(0, adj);
    cout << endl << endl;
}

void testShortestPaths() {
    cout << "Testing Shortest Paths:" << endl;
    
    int n = 4;
    vector<vector<int>> edgeList = {
        {0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {1, 3, 5}, {2, 3, 1}
    };
    vector<vector<pair<int, int>>> adj = adjWeighted(n, edgeList);
    
    vector<int> dist = dijkstra(0, adj);
    cout << "Dijkstra distances: ";
    for (int d : dist) {
        if (d == INT_MAX) cout << "INF ";
        else cout << d << " ";
    }
    cout << endl << endl;
}

void testMST() {
    cout << "Testing MST:" << endl;
    
    int n = 4;
    vector<vector<int>> edges = {
        {1, 0, 1}, {4, 0, 2}, {2, 1, 2}, {5, 1, 3}, {1, 2, 3}
    };
    
    int mst = kruskal(edges, n);
    cout << "MST weight: " << mst << endl << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Tree & Graph Algorithms Test Suite" << endl;
    cout << "==================================" << endl << endl;
    
    testGraphTraversal();
    testShortestPaths();
    testMST();
    
    return 0;
}

