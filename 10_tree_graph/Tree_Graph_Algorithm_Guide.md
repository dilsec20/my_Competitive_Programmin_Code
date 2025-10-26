# Tree & Graph Algorithms for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Graph Fundamentals](#graph-fundamentals)
3. [Tree Algorithms](#tree-algorithms)
4. [Graph Algorithms](#graph-algorithms)
5. [Practice Problems](#practice-problems)
6. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Graphs and trees are fundamental in competitive programming. This guide covers essential algorithms for solving graph and tree problems efficiently.

### What You'll Learn:
- Graph representation and traversal (DFS, BFS)
- Tree algorithms (LCA, diameter, centroid, heavy-light decomposition)
- Shortest path algorithms (Dijkstra, Floyd-Warshall, Bellman-Ford)
- Minimum spanning trees (Kruskal, Prim)
- Advanced techniques (topological sort, SCC, maximum flow)

---

## Graph Fundamentals

### 1. Graph Representation

```cpp
// Adjacency List (Most common)
vector<vector<int>> adj(n);

// Weighted Graph
vector<vector<pair<int, int>>> adjWeighted(n);

// Adjacency Matrix
vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

// Edge List
vector<vector<int>> edges;  // {u, v, weight}
```

### 2. Depth-First Search (DFS)

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

### 3. Breadth-First Search (BFS)

```cpp
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
```

---

## Tree Algorithms

### 1. Tree Diameter
Find longest path in tree using two BFS calls.

### 2. Lowest Common Ancestor (LCA)
Binary lifting technique for LCA queries.

### 3. Tree Centroid
Find tree centroid(s) for decomposition techniques.

---

## Graph Algorithms

### 1. Shortest Path Algorithms

#### Dijkstra's Algorithm
```cpp
vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& adj) {
    // Implementation here
}
```

#### Floyd-Warshall
```cpp
void floydWarshall(vector<vector<int>>& dist) {
    // Implementation here
}
```

#### Bellman-Ford
```cpp
vector<int> bellmanFord(int start, vector<vector<int>>& edges) {
    // Implementation here
}
```

### 2. Minimum Spanning Tree (MST)

#### Kruskal's Algorithm
```cpp
int kruskal(vector<vector<int>>& edges, int n) {
    // Implementation here
}
```

#### Prim's Algorithm
```cpp
int prim(vector<vector<pair<int, int>>>& adj) {
    // Implementation here
}
```

### 3. Advanced Techniques

#### Topological Sort
For Directed Acyclic Graphs (DAG).

#### Strongly Connected Components (SCC)
Using Tarjan's or Kosaraju's algorithm.

---

## Practice Problems

### Easy Level (800-1200)
- Graph Traversal
- Tree Height
- Connected Components
- Cycle Detection

### Medium Level (1200-1800)
- LCA Queries
- Shortest Path Problems
- MST Applications
- Topological Sort

### Hard Level (1800+)
- Heavy-Light Decomposition
- Advanced Graph Algorithms
- Flow Networks
- Dynamic Programming on Trees

---

## Tips for Competitive Programming

### 1. Graph Representation
- Adjacency List: Most common, space-efficient
- Adjacency Matrix: O(1) edge queries
- Edge List: Simple, good for MST

### 2. Algorithm Selection
- DFS: Path finding, cycle detection
- BFS: Shortest unweighted paths
- Dijkstra: Non-negative weights
- Floyd-Warshall: All-pairs shortest paths

### 3. Common Patterns
- Tree DP: Bottom-up processing
- Binary Lifting: LCA, kth ancestor
- Centroid: Decomposition
- HLD: Path queries

---

## Conclusion

Master Tree & Graph Algorithms by practicing and understanding when to use which algorithm!

Good luck!

