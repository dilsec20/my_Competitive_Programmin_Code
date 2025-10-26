#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// PREFIX SUM ON ARRAYS
// ============================================================================

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

vector<int> suffixSum(vector<int>& arr) {
    int n = arr.size();
    vector<int> suffix(n);
    
    suffix[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffix[i] = suffix[i+1] + arr[i];
    }
    
    return suffix;
}

// ============================================================================
// PREFIX MIN/MAX
// ============================================================================

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

// ============================================================================
// PREFIX PRODUCT
// ============================================================================

vector<long long> prefixProduct(vector<int>& arr, int mod = 1e9 + 7) {
    int n = arr.size();
    vector<long long> prefix(n);
    
    prefix[0] = arr[0] % mod;
    for (int i = 1; i < n; i++) {
        prefix[i] = (prefix[i-1] * arr[i]) % mod;
    }
    
    return prefix;
}

long long queryProduct(vector<long long>& prefix, int i, int j, int mod = 1e9 + 7) {
    if (i == 0) return prefix[j];
    
    // Compute modular inverse
    long long inv = modInverse(prefix[i-1], mod);
    return (prefix[j] * inv) % mod;
}

long long modInverse(long long a, int mod) {
    return power(a, mod - 2, mod);
}

long long power(long long base, long long exp, int mod) {
    long long result = 1;
    base %= mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    
    return result;
}

// ============================================================================
// CUMULATIVE FREQUENCY
// ============================================================================

vector<int> cumulativeFrequency(vector<int>& arr, int maxVal) {
    vector<int> freq(maxVal + 1, 0);
    
    for (int num : arr) {
        freq[num]++;
    }
    
    for (int i = 1; i <= maxVal; i++) {
        freq[i] += freq[i-1];
    }
    
    return freq;
}

int queryCumulative(vector<int>& freq, int x) {
    return freq[x];
}

// ============================================================================
// 2D PREFIX SUM
// ============================================================================

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

int querySum2D(vector<vector<int>>& prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2+1][c2+1] - 
           prefix[r1][c2+1] - 
           prefix[r2+1][c1] + 
           prefix[r1][c1];
}

// ============================================================================
// DIFFERENCE ARRAY
// ============================================================================

vector<int> differenceArray(vector<int>& arr) {
    int n = arr.size();
    vector<int> diff(n, 0);
    
    diff[0] = arr[0];
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i-1];
    }
    
    return diff;
}

void updateRange(vector<int>& diff, int l, int r, int val) {
    diff[l] += val;
    if (r + 1 < diff.size()) {
        diff[r+1] -= val;
    }
}

vector<int> recoverArray(vector<int>& diff) {
    vector<int> arr(diff.size());
    arr[0] = diff[0];
    
    for (int i = 1; i < diff.size(); i++) {
        arr[i] = arr[i-1] + diff[i];
    }
    
    return arr;
}

// ============================================================================
// ROLLING HASH FOR STRINGS
// ============================================================================

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
        long long result = (prefixHash[r+1] - 
                           prefixHash[l] * pow[r-l+1] % mod + 
                           mod) % mod;
        return result;
    }
};

// ============================================================================
// PALINDROME PRECOMPUTATION
// ============================================================================

vector<vector<bool>> isPalindrome(string& s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // Single characters
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    // Length 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i+1]) {
            dp[i][i+1] = true;
        }
    }
    
    // Length >= 3
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

bool queryPalindrome(vector<vector<bool>>& dp, int i, int j) {
    return dp[i][j];
}

// ============================================================================
// CHARACTER FREQUENCY PRECOMPUTATION
// ============================================================================

vector<vector<int>> characterFrequency(string& s) {
    int n = s.length();
    vector<vector<int>> freq(n + 1, vector<int>(26, 0));
    
    for (int i = 0; i < n; i++) {
        freq[i+1] = freq[i];
        freq[i+1][s[i] - 'a']++;
    }
    
    return freq;
}

int queryFrequency(vector<vector<int>>& freq, int l, int r, char c) {
    return freq[r+1][c - 'a'] - freq[l][c - 'a'];
}

// ============================================================================
// LCP (LONGEST COMMON PREFIX) ARRAY
// ============================================================================

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

// ============================================================================
// PREFIX FUNCTION (KMP)
// ============================================================================

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

vector<int> kmpSearch(string& text, string& pattern) {
    vector<int> prefix = buildPrefixFunction(pattern);
    vector<int> result;
    
    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = prefix[j-1];
        }
        
        if (text[i] == pattern[j]) {
            j++;
        }
        
        if (j == pattern.length()) {
            result.push_back(i - pattern.length() + 1);
            j = prefix[j-1];
        }
    }
    
    return result;
}

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
    
    int query(int l, int r) {
        int k = logTable[r - l + 1];
        return min(table[l][k], 
                  table[r - (1 << k) + 1][k]);
    }
};

// ============================================================================
// FACTORIAL PRECOMPUTATION
// ============================================================================

vector<long long> factorialPrecompute(int n, int mod) {
    vector<long long> fact(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    
    return fact;
}

vector<long long> inverseFactorialPrecompute(vector<long long>& fact, int mod) {
    int n = fact.size() - 1;
    vector<long long> invFact(n + 1);
    
    invFact[n] = modInverse(fact[n], mod);
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i+1] * (i+1)) % mod;
    }
    
    return invFact;
}

// ============================================================================
// RANGE UPDATE WITH DIFFERENCE ARRAY
// ============================================================================

vector<int> rangeUpdate(vector<int>& arr, vector<vector<int>>& updates) {
    int n = arr.size();
    vector<int> diff(n + 1, 0);
    
    for (auto& update : updates) {
        int l = update[0], r = update[1], val = update[2];
        diff[l] += val;
        diff[r+1] -= val;
    }
    
    for (int i = 1; i < n; i++) {
        diff[i] += diff[i-1];
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] += diff[i];
    }
    
    return arr;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testPrefixSum() {
    cout << "Testing Prefix Sum:" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    vector<int> prefix = prefixSum(arr);
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Prefix Sum: ";
    for (int x : prefix) cout << x << " ";
    cout << endl;
    
    cout << "Sum [1,3]: " << querySum(prefix, 1, 3) << endl;
    cout << endl;
}

void testPalindromePrecomputation() {
    cout << "Testing Palindrome Precomputation:" << endl;
    
    string s = "abaaba";
    vector<vector<bool>> dp = isPalindrome(s);
    
    cout << "String: " << s << endl;
    cout << "Is 'abaaba' palindrome? " << queryPalindrome(dp, 0, 5) << endl;
    cout << "Is 'baab' palindrome? " << queryPalindrome(dp, 1, 4) << endl;
    cout << endl;
}

void testRollingHash() {
    cout << "Testing Rolling Hash:" << endl;
    
    string s = "abcabc";
    RollingHash rh(s);
    
    cout << "String: " << s << endl;
    cout << "Hash [0,2]: " << rh.getHash(0, 2) << endl;
    cout << "Hash [3,5]: " << rh.getHash(3, 5) << endl;
    cout << "Are they equal? " << (rh.getHash(0, 2) == rh.getHash(3, 5)) << endl;
    cout << endl;
}

void test2DPrefixSum() {
    cout << "Testing 2D Prefix Sum:" << endl;
    
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    vector<vector<int>> prefix = prefixSum2D(matrix);
    cout << "Sum of submatrix [1,1] to [2,2]: " 
         << querySum2D(prefix, 1, 1, 2, 2) << endl;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Precomputation Techniques Test Suite" << endl;
    cout << "====================================" << endl << endl;
    
    testPrefixSum();
    testPalindromePrecomputation();
    testRollingHash();
    test2DPrefixSum();
    
    return 0;
}

