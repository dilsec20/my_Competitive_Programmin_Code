# Range Query Techniques for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Segment Tree](#segment-tree)
3. [Fenwick Tree (Binary Indexed Tree)](#fenwick-tree)
4. [Sparse Table](#sparse-table)
5. [Sqrt Decomposition](#sqrt-decomposition)
6. [Mo's Algorithm](#mos-algorithm)
7. [Practice Problems](#practice-problems)
8. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Range queries are fundamental in competitive programming. They involve efficiently answering queries about data in specific ranges.

### Common Range Query Problems:
- **Range Sum/Min/Max Query**: Sum, minimum, maximum in range [l, r]
- **Range Update Query**: Update all elements in range [l, r]
- **Point Update**: Update a single element
- **Aggregate Operations**: GCD, LCM, OR, AND, XOR

### Data Structures for Range Queries:
1. **Segment Tree**: General purpose, O(log n) for both query and update
2. **Fenwick Tree**: Simpler, O(log n) for both, but limited operations
3. **Sparse Table**: O(1) query, O(n log n) precomputation, but no updates
4. **Sqrt Decomposition**: O(√n) operations, simpler implementation
5. **Mo's Algorithm**: Offline queries, O(n√n)

---

## Segment Tree

### Basic Concept

A segment tree is a binary tree where each node represents a segment of the array.

### 1. Segment Tree for Sum

```cpp
class SegmentTree {
private:
    vector<int> tree;
    int n;
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + 
               query(2*node+1, mid+1, end, l, r);
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2*node, start, mid, idx, val);
            } else {
                update(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n-1);
    }
    
    int rangeSum(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
    
    void updateElement(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }
};
```

### 2. Segment Tree for Range Update

```cpp
class LazySegmentTree {
private:
    vector<int> tree, lazy;
    int n;
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void updateRange(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (start > r || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, val);
        updateRange(2*node+1, mid+1, end, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    int query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > r || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + 
               query(2*node+1, mid+1, end, l, r);
    }
    
public:
    LazySegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        // Build tree (similar to basic segment tree)
    }
    
    void updateRange(int l, int r, int val) {
        updateRange(1, 0, n-1, l, r, val);
    }
    
    int rangeSum(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};
```

### 3. Segment Tree for Minimum/Maximum

```cpp
class MinSegmentTree {
private:
    vector<int> tree;
    int n;
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = min(tree[2*node], tree[2*node+1]);
        }
    }
    
    int queryMin(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return INT_MAX;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return min(queryMin(2*node, start, mid, l, r),
                  queryMin(2*node+1, mid+1, end, l, r));
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2*node, start, mid, idx, val);
            } else {
                update(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = min(tree[2*node], tree[2*node+1]);
        }
    }
    
public:
    MinSegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n-1);
    }
    
    int rangeMin(int l, int r) {
        return queryMin(1, 0, n-1, l, r);
    }
    
    void updateElement(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }
};
```

---

## Fenwick Tree (Binary Indexed Tree)

### Basic Concept

Fenwick Tree is simpler and more memory efficient than Segment Tree for range sum queries.

### Implementation

```cpp
class FenwickTree {
private:
    vector<int> tree;
    int n;
    
    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }
    
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
    
public:
    FenwickTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]);
        }
    }
    
    int rangeSum(int l, int r) {
        return query(r + 1) - query(l);
    }
    
    void updateElement(int idx, int val) {
        int oldVal = getValue(idx);
        update(idx + 1, val - oldVal);
    }
    
    int getValue(int idx) {
        return rangeSum(idx, idx);
    }
};
```

### Range Update with Fenwick Tree

```cpp
class FenwickTreeRangeUpdate {
private:
    vector<int> tree1, tree2;
    int n;
    
    void update(int idx, int delta, vector<int>& tree) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }
    
    int query(int idx, vector<int>& tree) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
    
public:
    FenwickTreeRangeUpdate(int size) {
        n = size;
        tree1.resize(n + 1, 0);
        tree2.resize(n + 1, 0);
    }
    
    void rangeUpdate(int l, int r, int val) {
        update(l + 1, val, tree1);
        update(r + 2, -val, tree1);
        update(l + 1, -val * l, tree2);
        update(r + 2, val * (r + 1), tree2);
    }
    
    int rangeSum(int l, int r) {
        int sum1 = query(r + 1, tree1) * (r + 1) + query(r + 1, tree2);
        int sum2 = query(l, tree1) * l + query(l, tree2);
        return sum1 - sum2;
    }
};
```

---

## Sparse Table

### Basic Concept

Sparse Table allows O(1) range queries for idempotent operations (min, max, GCD).

### Implementation

```cpp
class SparseTable {
private:
    vector<vector<int>> table;
    vector<int> logTable;
    int n;
    
    int operation(int a, int b) {
        return min(a, b);  // Can change to max, gcd, etc.
    }
    
public:
    SparseTable(vector<int>& arr) {
        n = arr.size();
        int logn = log2(n) + 1;
        table.resize(n, vector<int>(logn));
        
        // Base case
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }
        
        // Build table
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = operation(table[i][j-1], 
                                        table[i + (1 << (j-1))][j-1]);
            }
        }
        
        // Precompute logs
        logTable.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i/2] + 1;
        }
    }
    
    int rangeQuery(int l, int r) {
        int k = logTable[r - l + 1];
        return operation(table[l][k], 
                        table[r - (1 << k) + 1][k]);
    }
};
```

---

## Sqrt Decomposition

### Basic Concept

Sqrt Decomposition divides array into √n blocks and preprocesses them.

### Implementation

```cpp
class SqrtDecomposition {
private:
    vector<int> arr, block;
    int blockSize;
    
    void build(vector<int>& data) {
        arr = data;
        blockSize = sqrt(arr.size()) + 1;
        block.resize(blockSize);
        
        for (int i = 0; i < arr.size(); i++) {
            block[i / blockSize] += arr[i];
        }
    }
    
    int query(int l, int r) {
        int sum = 0;
        
        while (l < r && l % blockSize != 0) {
            sum += arr[l];
            l++;
        }
        
        while (l + blockSize <= r) {
            sum += block[l / blockSize];
            l += blockSize;
        }
        
        while (l <= r) {
            sum += arr[l];
            l++;
        }
        
        return sum;
    }
    
    void update(int idx, int val) {
        block[idx / blockSize] += val - arr[idx];
        arr[idx] = val;
    }
    
public:
    SqrtDecomposition(vector<int>& data) {
        build(data);
    }
    
    int rangeSum(int l, int r) {
        return query(l, r);
    }
    
    void updateElement(int idx, int val) {
        update(idx, val);
    }
};
```

---

## Mo's Algorithm

### Basic Concept

Mo's Algorithm is used for offline queries, grouping queries by block for efficiency.

### Implementation

```cpp
class MoAlgorithm {
private:
    int blockSize;
    
    struct Query {
        int l, r, idx;
        
        bool operator<(const Query& other) const {
            if (l / blockSize != other.l / blockSize) {
                return l / blockSize < other.l / blockSize;
            }
            return ((l / blockSize) & 1) ? r < other.r : r > other.r;
        }
    };
    
public:
    vector<int> processQueries(vector<int>& arr, 
                                vector<pair<int, int>>& queries) {
        int n = arr.size();
        blockSize = sqrt(n);
        
        vector<Query> q(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            q[i] = {queries[i].first, queries[i].second, i};
        }
        
        sort(q.begin(), q.end());
        
        vector<int> results(queries.size());
        int currentSum = 0;
        int l = 0, r = -1;
        
        for (auto& query : q) {
            while (l > query.l) {
                l--;
                currentSum += arr[l];
            }
            while (r < query.r) {
                r++;
                currentSum += arr[r];
            }
            while (l < query.l) {
                currentSum -= arr[l];
                l++;
            }
            while (r > query.r) {
                currentSum -= arr[r];
                r--;
            }
            results[query.idx] = currentSum;
        }
        
        return results;
    }
};
```

---

## Practice Problems

### Easy Level (800-1200)
1. Range Sum Query - Immutable
2. Range Sum Query - Mutable
3. Simple Range Sum Queries
4. Point Update Queries
5. Basic Segment Tree

### Medium Level (1200-1800)
1. Range Update with Lazy Propagation
2. Range Minimum Query
3. Count Distinct Elements in Range
4. Inversion Count
5. Range XOR Query

### Hard Level (1800+)
1. Advanced Segment Tree Problems
2. 2D Range Queries
3. Persistant Segment Trees
4. Heavy-Light Decomposition
5. Merge Sort Tree

---

## Tips for Competitive Programming

### 1. When to Use Which?

| Data Structure | Query Time | Update Time | Space | When to Use |
|----------------|------------|-------------|-------|-------------|
| Segment Tree | O(log n) | O(log n) | O(n) | General purpose |
| Fenwick Tree | O(log n) | O(log n) | O(n) | Sum queries only |
| Sparse Table | O(1) | - | O(n log n) | Static, idempotent |
| Sqrt Decomp | O(√n) | O(√n) | O(n) | Simple, offline |
| Mo's Algo | O(n√n) | - | O(n) | Offline range queries |

### 2. Common Mistakes
- Off-by-one errors
- Incorrect segment boundaries
- Forgetting lazy propagation
- Wrong merge function
- Index out of bounds

### 3. Debugging Tips
- Test with small arrays
- Verify with manual calculation
- Check segment boundaries
- Print tree structure
- Test edge cases

---

## Conclusion

Master Range Query Techniques by:

1. **Understanding trade-offs**: Time vs Space vs Simplicity
2. **Learning segment trees**: Most versatile
3. **Mastering lazy propagation**: For range updates
4. **Practicing problems**: Start with basic, move to advanced
5. **Knowing when to use which**: Choose based on problem requirements

Remember: Range queries are about choosing the right data structure. Segment Tree is the most versatile, but Fenwick Tree is simpler for sum queries!

Good luck with your competitive programming journey!

