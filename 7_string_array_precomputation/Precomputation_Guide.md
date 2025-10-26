# Precomputation Techniques for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Precomputation on Arrays](#precomputation-on-arrays)
3. [Precomputation on Strings](#precomputation-on-strings)
4. [Prefix Sum Techniques](#prefix-sum-techniques)
5. [Suffix Sum Techniques](#suffix-sum-techniques)
6. [Advanced Precomputation](#advanced-precomputation)
7. [Practice Problems](#practice-problems)
8. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Precomputation is a technique where we compute and store frequently needed values before processing queries. This trades space for time, significantly improving query performance.

### Why Use Precomputation?
- **Reduce time complexity**: Answer queries in O(1) instead of O(n)
- **Speed up processing**: Precompute once, use many times
- **Optimize competitive programming**: Fast query response in contests
- **Common in DP problems**: Store computed states

### What You'll Learn:
- Prefix and suffix sums
- Precomputation on arrays (sum, product, max, min)
- String precomputation (substring, palindrome)
- Frequency counting and hashing
- Advanced techniques (2D prefix sum, rolling hash)

---

## Precomputation on Arrays

### 1. Prefix Sum

```cpp
vector<int> prefixSum(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + arr[i];
    }
    
    return prefix;
}

// Query: Sum from index i to j
int querySum(vector<int>& prefix, int i, int j) {
    if (i == 0) return prefix[j];
    return prefix[j] - prefix[i-1];
}
```

### 2. Suffix Sum

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

// Query: Sum from index i to end
int querySuffix(vector<int>& suffix, int i) {
    return suffix[i];
}
```

### 3. Prefix Minimum/Maximum

```cpp
vector<int> prefixMin(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = min(prefix[i-1], arr[i]);
    }
    
    return prefix;
}

vector<int> prefixMax(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = max(prefix[i-1], arr[i]);
    }
    
    return prefix;
}
```

### 4. Suffix Minimum/Maximum

```cpp
vector<int> suffixMin(vector<int>& arr) {
    int n = arr.size();
    vector<int> suffix(n);
    
    suffix[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffix[i] = min(suffix[i+1], arr[i]);
    }
    
    return suffix;
}

vector<int> suffixMax(vector<int>& arr) {
    int n = arr.size();
    vector<int> suffix(n);
    
    suffix[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffix[i] = max(suffix[i+1], arr[i]);
    }
    
    return suffix;
}
```

### 5. Prefix Product

```cpp
vector<long long> prefixProduct(vector<int>& arr) {
    int n = arr.size();
    vector<long long> prefix(n);
    
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] * arr[i];
    }
    
    return prefix;
}

// Query: Product from index i to j
long long queryProduct(vector<long long>& prefix, int i, int j) {
    if (i == 0) return prefix[j];
    return prefix[j] / prefix[i-1];
}
```

### 6. Cumulative Frequency

```cpp
vector<int> cumulativeFrequency(vector<int>& arr, int maxVal) {
    vector<int> freq(maxVal + 1, 0);
    
    for (int num : arr) {
        freq[num]++;
    }
    
    // Compute cumulative frequency
    for (int i = 1; i <= maxVal; i++) {
        freq[i] += freq[i-1];
    }
    
    return freq;
}

// Query: Count of elements <= x
int queryCumulative(vector<int>& freq, int x) {
    return freq[x];
}
```

---

## Precomputation on Strings

### 1. Prefix Hash (Rolling Hash)

```cpp
class RollingHash {
private:
    int base = 131;
    int mod = 1e9 + 7;
    vector<long long> pow, prefixHash;
    
public:
    RollingHash(string& s) {
        int n = s.length();
        pow.resize(n + 1);
        prefixHash.resize(n + 1);
        
        pow[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow[i] = (pow[i-1] * base) % mod;
        }
        
        for (int i = 0; i < n; i++) {
            prefixHash[i+1] = (prefixHash[i] * base + s[i]) % mod;
        }
    }
    
    long long getHash(int l, int r) {
        long long result = (prefixHash[r+1] - prefixHash[l] * pow[r-l+1] % mod + mod) % mod;
        return result;
    }
};
```

### 2. Precomputation for Palindrome Checking

```cpp
vector<vector<bool>> isPalindrome(string& s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // Single characters are palindromes
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    // Check for length 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i+1]) {
            dp[i][i+1] = true;
        }
    }
    
    // Check for length >= 3
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

// Query: Check if substring [i, j] is palindrome
bool queryPalindrome(vector<vector<bool>>& dp, int i, int j) {
    return dp[i][j];
}
```

### 3. Precompute Character Frequency

```cpp
vector<vector<int>> characterFrequency(string& s) {
    int n = s.length();
    vector<vector<int>> freq(n + 1, vector<int>(26, 0));
    
    for (int i = 0; i < n; i++) {
        freq[i+1] = freq[i];
        freq[i+1][s[i] - 'a']++;
    }
    
    return freq;
}

// Query: Count character c in range [l, r]
int queryFrequency(vector<vector<int>>& freq, int l, int r, char c) {
    return freq[r+1][c - 'a'] - freq[l][c - 'a'];
}
```

### 4. Longest Common Prefix (LCP) Array

```cpp
vector<int> computeLCP(string& s) {
    int n = s.length();
    vector<int> lcp(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = lcp[i-1];
        
        while (j > 0 && s[i] != s[j]) {
            j = lcp[j-1];
        }
        
        if (s[i] == s[j]) {
            j++;
        }
        
        lcp[i] = j;
    }
    
    return lcp;
}
```

### 5. Prefix Array for Pattern Matching

```cpp
vector<int> buildPrefixFunction(string& pattern) {
    int n = pattern.length();
    vector<int> prefix(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = prefix[i-1];
        
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefix[j-1];
        }
        
        if (pattern[i] == pattern[j]) {
            j++;
        }
        
        prefix[i] = j;
    }
    
    return prefix;
}
```

---

## Prefix Sum Techniques

### 1. 2D Prefix Sum

```cpp
vector<vector<int>> prefixSum2D(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    vector<vector<int>> prefix(rows + 1, vector<int>(cols + 1, 0));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            prefix[i+1][j+1] = matrix[i][j] + 
                              prefix[i][j+1] + 
                              prefix[i+1][j] - 
                              prefix[i][j];
        }
    }
    
    return prefix;
}

// Query: Sum of submatrix from (r1, c1) to (r2, c2)
int querySum2D(vector<vector<int>>& prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2+1][c2+1] - 
           prefix[r1][c2+1] - 
           prefix[r2+1][c1] + 
           prefix[r1][c1];
}
```

### 2. Range Update with Prefix Arrays

```cpp
vector<int> rangeUpdate(vector<int>& arr, vector<vector<int>>& updates) {
    int n = arr.size();
    vector<int> diff(n + 1, 0);
    
    // Mark updates
    for (auto& update : updates) {
        int l = update[0], r = update[1], val = update[2];
        diff[l] += val;
        diff[r+1] -= val;
    }
    
    // Apply updates
    for (int i = 1; i < n; i++) {
        diff[i] += diff[i-1];
    }
    
    // Add to original array
    for (int i = 0; i < n; i++) {
        arr[i] += diff[i];
    }
    
    return arr;
}
```

### 3. Difference Array

```cpp
vector<int> differenceArray(vector<int>& arr) {
    int n = arr.size();
    vector<int> diff(n, 0);
    
    diff[0] = arr[0];
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i-1];
    }
    
    return diff;
}

// Update range [l, r] by adding val
void updateRange(vector<int>& diff, int l, int r, int val) {
    diff[l] += val;
    if (r + 1 < diff.size()) {
        diff[r+1] -= val;
    }
}

// Recover original array from difference array
vector<int> recoverArray(vector<int>& diff) {
    vector<int> arr(diff.size());
    arr[0] = diff[0];
    
    for (int i = 1; i < diff.size(); i++) {
        arr[i] = arr[i-1] + diff[i];
    }
    
    return arr;
}
```

---

## Suffix Sum Techniques

### 1. Suffix Array for String

```cpp
vector<int> buildSuffixArray(string& s) {
    int n = s.length();
    vector<int> suffixArray(n);
    vector<pair<pair<int, int>, int>> v(n);
    
    // Initialize with single characters
    for (int i = 0; i < n; i++) {
        suffixArray[i] = i;
    }
    
    // Sort by 2^k length prefixes
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i++) {
            v[i] = {{s[i], (i+k < n ? s[i+k] : -1)}, i};
        }
        
        sort(v.begin(), v.end());
        
        int rank = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0 && v[i].first != v[i-1].first) {
                rank++;
            }
            suffixArray[v[i].second] = rank;
        }
    }
    
    return suffixArray;
}
```

### 2. Suffix Maximum/Minimum

```cpp
vector<int> suffixMax(vector<int>& arr) {
    int n = arr.size();
    vector<int> suffix(n);
    
    suffix[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffix[i] = max(suffix[i+1], arr[i]);
    }
    
    return suffix;
}

vector<int> suffixMin(vector<int>& arr) {
    int n = arr.size();
    vector<int> suffix(n);
    
    suffix[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffix[i] = min(suffix[i+1], arr[i]);
    }
    
    return suffix;
}
```

---

## Advanced Precomputation

### 1. Factorial Precomputation

```cpp
vector<long long> factorialPrecompute(int n, int mod) {
    vector<long long> fact(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    
    return fact;
}

// Inverse factorial
vector<long long> inverseFactorial(int n, int mod) {
    vector<long long> invFact(n + 1);
    
    invFact[n] = modInverse(factorial[n], mod);
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i+1] * (i+1)) % mod;
    }
    
    return invFact;
}
```

### 2. Prime Precomputation (Sieve)

```cpp
vector<bool> sieveEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

vector<int> getPrimes(int n) {
    vector<bool> isPrime = sieveEratosthenes(n);
    vector<int> primes;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}
```

### 3. Divisor Precomputation

```cpp
vector<vector<int>> divisorPrecompute(int n) {
    vector<vector<int>> divisors(n + 1);
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divisors[j].push_back(i);
        }
    }
    
    return divisors;
}
```

### 4. Sparse Table for Range Queries

```cpp
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
        
        // Base case: length 1
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }
        
        // Compute for powers of 2
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = min(table[i][j-1], 
                                 table[i + (1 << (j-1))][j-1]);
            }
        }
        
        // Precompute logs
        logTable.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i/2] + 1;
        }
    }
    
    int query(int l, int r) {
        int k = logTable[r - l + 1];
        return min(table[l][k], 
                  table[r - (1 << k) + 1][k]);
    }
};
```

---

## Practice Problems

### Easy Level (800-1200)
1. Range Sum Queries
2. Subarray Sum Equals K
3. Product of Array Except Self
4. Running Sum of 1D Array
5. Cumulative Sum

### Medium Level (1200-1800)
1. 2D Range Sum Queries
2. Palindrome Substrings
3. Longest Common Prefix
4. Substring Hash Queries
5. Frequency Range Queries

### Hard Level (1800+)
1. Advanced Sparse Tables
2. Heavy String Precomputation
3. Complex 2D Queries
4. Optimization with Precomputation
5. Multiple Query Types

---

## Tips for Competitive Programming

### 1. When to Use Precomputation
- **Multiple queries** on same data
- **Range queries** (sum, min, max)
- **Pattern matching** in strings
- **Static data** that doesn't change
- **Trade space for time**

### 2. Common Patterns
- **Prefix/Suffix arrays**: O(n) precomputation, O(1) query
- **Hash tables**: O(1) lookups
- **Sparse tables**: O(n log n) precomputation, O(1) range query
- **DP precomputation**: Store states

### 3. Time Complexity
- **Precomputation**: Usually O(n) or O(n log n)
- **Query**: Usually O(1) or O(log n)
- **Space**: O(n) or O(n log n)

### 4. Common Mistakes
- Not initializing properly
- Off-by-one errors
- Not handling edge cases (empty, single element)
- Overflow in prefix product
- Wrong mod in rolling hash

---

## Conclusion

Master precomputation by:

1. **Understanding trade-offs**: Space vs Time
2. **Learning patterns**: Prefix, suffix, hash
3. **Practicing problems**: Range queries, string matching
4. **Optimizing queries**: O(1) or O(log n) responses
5. **Handling edge cases**: Empty arrays, single elements

Remember: Precomputation is about preparing data for fast queries. Think about what queries you'll need and precompute those values!

Good luck with your competitive programming journey!

