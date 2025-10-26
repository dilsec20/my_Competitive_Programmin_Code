#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// SEGMENT TREE
// ============================================================================

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

// ============================================================================
// LAZY PROPAGATION SEGMENT TREE
// ============================================================================

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
    
public:
    LazySegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n-1);
    }
    
    void updateRange(int l, int r, int val) {
        updateRange(1, 0, n-1, l, r, val);
    }
    
    int rangeSum(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};

// ============================================================================
// FENWICK TREE
// ============================================================================

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
        int oldVal = rangeSum(idx, idx);
        update(idx + 1, val - oldVal);
    }
};

// ============================================================================
// SPARSE TABLE
// ============================================================================

class SparseTable {
private:
    vector<vector<int>> table;
    vector<int> logTable;
    int n;
    
public:
    SparseTable(vector<int>& arr) {
        n = arr.size();
        int logn = log2(n) + 1;
        table.resize(n, vector<int>(logn));
        
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }
        
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = min(table[i][j-1], 
                                 table[i + (1 << (j-1))][j-1]);
            }
        }
        
        logTable.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i/2] + 1;
        }
    }
    
    int rangeMin(int l, int r) {
        int k = logTable[r - l + 1];
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

// ============================================================================
// SQRT DECOMPOSITION
// ============================================================================

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

// ============================================================================
// MO'S ALGORITHM
// ============================================================================

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

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testSegmentTree() {
    cout << "Testing Segment Tree:" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree st(arr);
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Sum [0,2]: " << st.rangeSum(0, 2) << endl;
    cout << "Sum [1,4]: " << st.rangeSum(1, 4) << endl;
    
    st.updateElement(2, 10);
    cout << "After updating index 2 to 10:" << endl;
    cout << "Sum [0,2]: " << st.rangeSum(0, 2) << endl;
    
    cout << endl;
}

void testLazySegmentTree() {
    cout << "Testing Lazy Segment Tree:" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    LazySegmentTree lst(arr);
    
    cout << "Range sum [1,3]: " << lst.rangeSum(1, 3) << endl;
    
    cout << "Update range [1,3] by adding 2" << endl;
    lst.updateRange(1, 3, 2);
    
    cout << "Range sum [1,3]: " << lst.rangeSum(1, 3) << endl;
    cout << endl;
}

void testFenwickTree() {
    cout << "Testing Fenwick Tree:" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    FenwickTree ft(arr);
    
    cout << "Range sum [0,2]: " << ft.rangeSum(0, 2) << endl;
    cout << "Range sum [1,4]: " << ft.rangeSum(1, 4) << endl;
    
    cout << "Update index 2 to 10" << endl;
    ft.updateElement(2, 10);
    
    cout << "Range sum [0,2]: " << ft.rangeSum(0, 2) << endl;
    cout << endl;
}

void testSparseTable() {
    cout << "Testing Sparse Table:" << endl;
    
    vector<int> arr = {4, 2, 1, 3, 5, 2, 1};
    SparseTable st(arr);
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Min in [0,3]: " << st.rangeMin(0, 3) << endl;
    cout << "Min in [2,5]: " << st.rangeMin(2, 5) << endl;
    cout << endl;
}

void testSqrtDecomposition() {
    cout << "Testing Sqrt Decomposition:" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SqrtDecomposition sd(arr);
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Sum [2,7]: " << sd.rangeSum(2, 7) << endl;
    cout << "Sum [0,8]: " << sd.rangeSum(0, 8) << endl;
    
    cout << "Update index 4 to 50" << endl;
    sd.updateElement(4, 50);
    
    cout << "Sum [2,7]: " << sd.rangeSum(2, 7) << endl;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Range Query Techniques Test Suite" << endl;
    cout << "=================================" << endl << endl;
    
    testSegmentTree();
    testLazySegmentTree();
    testFenwickTree();
    testSparseTable();
    testSqrtDecomposition();
    
    return 0;
}

