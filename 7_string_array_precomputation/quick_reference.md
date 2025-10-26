# Precomputation Quick Reference

## Array Precomputation

### Prefix Sum
```cpp
vector<int> prefixSum(vector<int>& arr) {
    vector<int> prefix(arr.size());
    prefix[0] = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        prefix[i] = prefix[i-1] + arr[i];
    }
    return prefix;
}

// Query sum from l to r: O(1)
int querySum(vector<int>& prefix, int l, int r) {
    return prefix[r] - (l > 0 ? prefix[l-1] : 0);
}
```

### Suffix Sum
```cpp
vector<int> suffixSum(vector<int>& arr) {
    int n = arr.size();
    vector<int> suffix(n);
    suffix[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffix[i] = suffix[i+1] + arr[i];
    }
    return suffix;
}
```

### Prefix Min/Max
```cpp
vector<int> prefixMin(vector<int>& arr) {
    vector<int> prefix(arr.size());
    prefix[0] = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        prefix[i] = min(prefix[i-1], arr[i]);
    }
    return prefix;
}
```

### Difference Array
```cpp
vector<int> diffArray(vector<int>& arr) {
    int n = arr.size();
    vector<int> diff(n);
    diff[0] = arr[0];
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i-1];
    }
    return diff;
}

// Range update [l, r] by val: O(1)
void updateRange(vector<int>& diff, int l, int r, int val) {
    diff[l] += val;
    if (r+1 < diff.size()) diff[r+1] -= val;
}

// Recover array: O(n)
vector<int> recover(vector<int>& diff) {
    vector<int> arr(diff.size());
    arr[0] = diff[0];
    for (int i = 1; i < diff.size(); i++) {
        arr[i] = arr[i-1] + diff[i];
    }
    return arr;
}
```

### 2D Prefix Sum
```cpp
vector<vector<int>> prefix2D(vector<vector<int>>& mat) {
    int r = mat.size(), c = mat[0].size();
    vector<vector<int>> prefix(r+1, vector<int>(c+1, 0));
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            prefix[i+1][j+1] = mat[i][j] + 
                               prefix[i][j+1] + 
                               prefix[i+1][j] - 
                               prefix[i][j];
        }
    }
    return prefix;
}

// Query sum from (r1,c1) to (r2,c2): O(1)
int query2D(vector<vector<int>>& prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2+1][c2+1] - prefix[r1][c2+1] - 
           prefix[r2+1][c1] + prefix[r1][c1];
}
```

## String Precomputation

### Rolling Hash
```cpp
class RollingHash {
    int base = 131, mod = 1e9+7;
    vector<long long> pow, prefixHash;
public:
    RollingHash(string& s) {
        int n = s.length();
        pow.resize(n+1);
        prefixHash.resize(n+1);
        pow[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow[i] = (pow[i-1] * base) % mod;
        }
        for (int i = 0; i < n; i++) {
            prefixHash[i+1] = (prefixHash[i] * base + s[i]) % mod;
        }
    }
    
    long long getHash(int l, int r) {
        return (prefixHash[r+1] - prefixHash[l] * pow[r-l+1] % mod + mod) % mod;
    }
};
```

### Palindrome Precomputation
```cpp
vector<vector<bool>> precomputePalindrome(string& s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // Single char
    for (int i = 0; i < n; i++) dp[i][i] = true;
    
    // Two chars
    for (int i = 0; i < n-1; i++) {
        if (s[i] == s[i+1]) dp[i][i+1] = true;
    }
    
    // 3+ chars
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i+1][j-1]) {
                dp[i][j] = true;
            }
        }
    }
    return dp;
}
```

### Character Frequency
```cpp
vector<vector<int>> charFreq(string& s) {
    int n = s.length();
    vector<vector<int>> freq(n+1, vector<int>(26, 0));
    for (int i = 0; i < n; i++) {
        freq[i+1] = freq[i];
        freq[i+1][s[i]-'a']++;
    }
    return freq;
}

// Query frequency of char c in [l, r]
int queryFreq(vector<vector<int>>& freq, int l, int r, char c) {
    return freq[r+1][c-'a'] - freq[l][c-'a'];
}
```

### KMP Prefix Function
```cpp
vector<int> kmpPrefix(string& pattern) {
    int n = pattern.length();
    vector<int> prefix(n, 0);
    for (int i = 1; i < n; i++) {
        int j = prefix[i-1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefix[j-1];
        }
        if (pattern[i] == pattern[j]) j++;
        prefix[i] = j;
    }
    return prefix;
}
```

## Advanced Techniques

### Sparse Table
```cpp
class SparseTable {
    vector<vector<int>> table;
    vector<int> logTable;
public:
    SparseTable(vector<int>& arr) {
        int n = arr.size();
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
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i/2] + 1;
        }
    }
    
    int query(int l, int r) {
        int k = logTable[r-l+1];
        return min(table[l][k], table[r-(1<<k)+1][k]);
    }
};
```

## Time Complexity Reference

| Technique | Precomputation | Query | Space |
|-----------|----------------|-------|-------|
| Prefix Sum | O(n) | O(1) | O(n) |
| Suffix Array | O(n) | O(1) | O(n) |
| 2D Prefix Sum | O(nm) | O(1) | O(nm) |
| Rolling Hash | O(n) | O(1) | O(n) |
| Palindrome Table | O(n²) | O(1) | O(n²) |
| Char Frequency | O(n) | O(1) | O(n×26) |
| Sparse Table | O(n log n) | O(1) | O(n log n) |
| KMP | O(m) | O(n) | O(m) |

## When to Use Which?

### Array Techniques:
- **Prefix Sum** - Range sum queries
- **Prefix Min/Max** - Range min/max queries
- **Difference Array** - Range updates
- **2D Prefix Sum** - 2D range sum queries

### String Techniques:
- **Rolling Hash** - Fast substring comparison
- **Palindrome Table** - Fast palindrome check
- **KMP** - Pattern matching
- **Char Frequency** - Count characters in range

### Advanced:
- **Sparse Table** - Range min/max/gcd
- **Suffix Array** - String suffix operations
- **Factorial Precomputation** - Combinatorics

## Common Patterns

### Pattern 1: Range Sum
```cpp
// Precompute prefix
vector<int> prefix = prefixSum(arr);

// Query multiple times in O(1)
for (auto& query : queries) {
    int sum = querySum(prefix, query[0], query[1]);
}
```

### Pattern 2: String Matching
```cpp
// Precompute hash
RollingHash rh(text);

// Fast substring comparison
for (auto& substring : substrings) {
    long long hash = rh.getHash(substring[0], substring[1]);
    // Compare hashes
}
```

### Pattern 3: Range Update
```cpp
// Use difference array for range updates
vector<int> diff = diffArray(arr);

// Update range [l, r] by val in O(1)
updateRange(diff, l, r, val);

// Get final array
vector<int> result = recover(diff);
```

## Tips & Tricks

### 1. Memory Optimization
- Use `int` instead of `long long` when possible
- Consider space-time tradeoff
- Release precomputed data if not needed

### 2. Overflow Prevention
```cpp
// Use modulo for large numbers
const int mod = 1e9 + 7;
long long product = (long long)a * b % mod;

// Check bounds before multiplying
if (a > INT_MAX / b) // Overflow
```

### 3. One-Based vs Zero-Based
- **One-based**: Easier calculations for some problems
- **Zero-based**: C++ standard, easier indexing
- Choose consistently

### 4. Edge Cases
- Empty array/string
- Single element
- All zeros/ones
- All same values

## Common Mistakes

1. ❌ Off-by-one errors in indexing
2. ❌ Integer overflow in products
3. ❌ Wrong modulo in rolling hash
4. ❌ Not handling empty inputs
5. ❌ Using wrong data structure

## See Also
- [Precomputation_Guide.md](Precomputation_Guide.md) - Complete guide
- [precomputation_algorithms.cpp](precomputation_algorithms.cpp) - Code implementations
- [practice_problems_list.md](practice_problems_list.md) - Problem lists

