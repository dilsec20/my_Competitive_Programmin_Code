# Range Query Quick Reference

## Segment Tree Template

```cpp
class SegmentTree {
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
            if (idx <= mid) update(2*node, start, mid, idx, val);
            else update(2*node+1, mid+1, end, idx, val);
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

## Lazy Segment Tree (Range Update)

```cpp
class LazySegmentTree {
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
        push(2*node, start, mid);
        push(2*node+1, mid+1, end);
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
};
```

## Fenwick Tree

```cpp
class FenwickTree {
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
        int oldVal = rangeSum(idx, idx);
        update(idx + 1, val - oldVal);
    }
};
```

## Sparse Table

```cpp
class SparseTable {
    vector<vector<int>> table;
    vector<int> logTable;
    int n;
    
public:
    SparseTable(vector<int>& arr) {
        n = arr.size();
        int logn = log2(n) + 1;
        table.resize(n, vector<int>(logn));
        
        for (int i = 0; i < n; i++) table[i][0] = arr[i];
        
        for (int j = 1; (1<<j) <= n; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                table[i][j] = min(table[i][j-1], 
                                 table[i+(1<<(j-1))][j-1]);
            }
        }
        
        logTable.resize(n+1);
        for (int i = 2; i <= n; i++) logTable[i] = logTable[i/2] + 1;
    }
    
    int rangeMin(int l, int r) {
        int k = logTable[r-l+1];
        return min(table[l][k], table[r-(1<<k)+1][k]);
    }
};
```

## Sqrt Decomposition

```cpp
class SqrtDecomposition {
    vector<int> arr, block;
    int blockSize;
    
public:
    SqrtDecomposition(vector<int>& data) {
        arr = data;
        blockSize = sqrt(arr.size()) + 1;
        block.resize(blockSize);
        
        for (int i = 0; i < arr.size(); i++) {
            block[i / blockSize] += arr[i];
        }
    }
    
    int rangeSum(int l, int r) {
        int sum = 0;
        
        while (l < r && l % blockSize != 0) {
            sum += arr[l++];
        }
        
        while (l + blockSize <= r) {
            sum += block[l / blockSize];
            l += blockSize;
        }
        
        while (l <= r) {
            sum += arr[l++];
        }
        
        return sum;
    }
    
    void updateElement(int idx, int val) {
        block[idx / blockSize] += val - arr[idx];
        arr[idx] = val;
    }
};
```

## Quick Comparison

| DS | Query | Update | Space | Use When |
|----|-------|--------|-------|----------|
| **Segment Tree** | O(log n) | O(log n) | O(n) | General purpose |
| **Fenwick Tree** | O(log n) | O(log n) | O(n) | Sum only |
| **Sparse Table** | O(1) | - | O(n log n) | Static |
| **Sqrt Dec** | O(√n) | O(√n) | O(n) | Simple |
| **Mo's** | O(n√n) | - | O(n) | Offline |

## Common Modifications

### Min Segment Tree
```cpp
// Change merge function
tree[node] = min(tree[2*node], tree[2*node+1]);
```

### Max Segment Tree
```cpp
// Change merge function
tree[node] = max(tree[2*node], tree[2*node+1]);
```

### XOR Segment Tree
```cpp
// Change merge function
tree[node] = tree[2*node] ^ tree[2*node+1];
```

## Tips & Tricks

### 1. Memory Optimization
- Use 4*n size for tree
- Release memory when done
- Use int instead of long long when possible

### 2. Indexing
- **1-indexed**: Easier math
- **0-indexed**: Standard C++
- Choose consistently

### 3. Common Mistakes
- ❌ Off-by-one in ranges
- ❌ Forgetting lazy propagation
- ❌ Wrong merge function
- ❌ Index out of bounds
- ❌ Not handling n=0

### 4. Debugging
```cpp
// Print tree for debugging
void printTree() {
    for (int i = 1; i < tree.size(); i++) {
        cout << tree[i] << " ";
        if (__builtin_popcount(i+1) == 1) cout << endl;
    }
}
```

## Problem Types

### Type 1: Point Update, Range Query
```cpp
SegmentTree st(arr);
st.updateElement(i, val);
int result = st.rangeSum(l, r);
```

### Type 2: Range Update, Range Query
```cpp
LazySegmentTree lst(arr);
lst.updateRange(l, r, val);
int result = lst.rangeSum(l, r);
```

### Type 3: Static Queries
```cpp
SparseTable st(arr);
int result = st.rangeMin(l, r);  // O(1)
```

### Type 4: Offline Queries
```cpp
MoAlgorithm mo;
vector<int> results = mo.processQueries(arr, queries);
```

## See Also
- [Range_Query_Guide.md](Range_Query_Guide.md) - Complete guide
- [range_query_algorithms.cpp](range_query_algorithms.cpp) - Implementations
- [practice_problems_list.md](practice_problems_list.md) - Problem lists

