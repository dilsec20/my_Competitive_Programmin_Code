# Tree & Graph Algorithms Quick Reference

## Graph Traversal

### DFS
```cpp
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}
```

### BFS
```cpp
void bfs(int start, vector<vector<int>>& adj) {
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
```

## Shortest Path Algorithms

### Dijkstra (Single Source)
- Time: O((V + E) log V)
- Use: Non-negative weights

### Floyd-Warshall (All Pairs)
- Time: O(V³)
- Use: Small graphs, all pairs

## MST Algorithms

### Kruskal
- Time: O(E log E)
- Use: Sparser graphs

### Prim
- Time: O(E log V)
- Use: Denser graphs

## See Also
- [Tree_Graph_Algorithm_Guide.md](Tree_Graph_Algorithm_Guide.md)
- [tree_graph_algorithms.cpp](tree_graph_algorithms.cpp)
- [practice_problems_list.md](practice_problems_list.md)

