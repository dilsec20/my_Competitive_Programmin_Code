#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ============================================================================
// COMBINATORICS
// ============================================================================

// Factorial
long long factorial(int n, int mod = MOD) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % mod;
    }
    return result;
}

// Permutation: P(n, r) = n! / (n-r)!
long long permutation(int n, int r, int mod = MOD) {
    if (r > n) return 0;
    long long result = 1;
    for (int i = n; i > n - r; i--) {
        result = (result * i) % mod;
    }
    return result;
}

// Precompute factorials and inverse factorials
vector<long long> fact, invFact;

void precomputeFactorials(int n, int mod) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    
    invFact[n] = modInverse(fact[n], mod);
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i+1] * (i + 1)) % mod;
    }
}

// Combination: C(n, r) = n! / (r! × (n-r)!)
long long nCr(int n, int r, int mod = MOD) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n-r] % mod;
}

// ============================================================================
// CATALAN NUMBERS
// ============================================================================

long long catalan(int n, int mod = MOD) {
    return nCr(2 * n, n, mod) * modInverse(n + 1, mod) % mod;
}

// Direct calculation
long long catalanDirect(int n, int mod = MOD) {
    long long c = 1;
    for (int i = 1; i <= n; i++) {
        c = (c * (4 * i - 2) % mod) * modInverse(i + 1, mod) % mod;
    }
    return c;
}

// ============================================================================
// STIRLING NUMBERS
// ============================================================================

// Stirling Numbers of the Second Kind
long long stirling2(int n, int k, int mod = MOD) {
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) {
            dp[i][j] = (dp[i-1][j-1] + (long long)j * dp[i-1][j] % mod) % mod;
        }
    }
    
    return dp[n][k];
}

// Stirling Numbers of the First Kind (unsigned)
long long stirling1(int n, int k, int mod = MOD) {
    if (k == 0) return (n == 0);
    if (n == 0) return 0;
    if (k > n) return 0;
    
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) {
            dp[i][j] = ((long long)(i-1) * dp[i-1][j] % mod + dp[i-1][j-1]) % mod;
        }
    }
    
    return dp[n][k];
}

// ============================================================================
// DERANGEMENTS
// ============================================================================

long long derangement(int n, int mod = MOD) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    
    long long prev2 = 1, prev1 = 0;
    for (int i = 2; i <= n; i++) {
        long long current = (i - 1) * (prev1 + prev2) % mod;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

// ============================================================================
// MODULAR ARITHMETIC
// ============================================================================

long long modInverse(long long a, int mod = MOD) {
    return power(a, mod - 2, mod);
}

long long power(long long base, long long exp, int mod = MOD) {
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

// Extended GCD
int extendedGcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    int x1, y1;
    int g = extendedGcd(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return g;
}

int modInverseExtended(int a, int mod = MOD) {
    int x, y;
    int g = extendedGcd(a, mod, x, y);
    if (g != 1) return -1;
    return (x % mod + mod) % mod;
}

// ============================================================================
// GCD AND LCM
// ============================================================================

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long lcm(int a, int b) {
    return (long long)a * b / gcd(a, b);
}

// ============================================================================
// CHINESE REMAINDER THEOREM
// ============================================================================

int chineseRemainder(vector<int>& a, vector<int>& m) {
    int n = a.size();
    int M = 1;
    for (int i = 0; i < n; i++) M *= m[i];
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        int Mi = M / m[i];
        int Mi_inv = modInverseExtended(Mi, m[i]);
        result = (result + (long long)a[i] * Mi % M * Mi_inv % M) % M;
    }
    return result;
}

// ============================================================================
// MATRIX OPERATIONS
// ============================================================================

vector<vector<long long>> matrixMultiply(vector<vector<long long>>& a, 
                                          vector<vector<long long>>& b, 
                                          int mod = MOD) {
    int n = a.size();
    int m = b[0].size();
    int p = b.size();
    
    vector<vector<long long>> result(n, vector<long long>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    
    return result;
}

vector<vector<long long>> matrixPower(vector<vector<long long>> base, 
                                      long long exp, int mod = MOD) {
    int n = base.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    
    // Identity matrix
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            result = matrixMultiply(result, base, mod);
        }
        base = matrixMultiply(base, base, mod);
        exp >>= 1;
    }
    
    return result;
}

// Fibonacci using matrix exponentiation
long long fibonacci(long long n, int mod = MOD) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    vector<vector<long long>> base = {{1, 1}, {1, 0}};
    vector<vector<long long>> result = matrixPower(base, n - 1, mod);
    return result[0][0];
}

// ============================================================================
// PROBABILITY AND STATISTICS
// ============================================================================

long long expectedValue(vector<pair<int, int>>& outcomes, int mod = MOD) {
    long long result = 0;
    
    for (auto& [value, probability] : outcomes) {
        result = (result + (long long)value * probability % mod) % mod;
    }
    
    return result;
}

long long binomialProbability(int n, int k, int p, int mod = MOD) {
    long long C = nCr(n, k, mod);
    long long prob_k = power(p, k, mod);
    long long prob_n_minus_k = power(mod + 1 - p, n - k, mod);
    return (C * prob_k % mod) * prob_n_minus_k % mod;
}

long long geometricExpected(int p, int mod = MOD) {
    return modInverse(p, mod);
}

// ============================================================================
// LUCAS THEOREM
// ============================================================================

long long lucas(int n, int r, int p) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    
    return (lucas(n / p, r / p, p) * 
            nCr(n % p, r % p, p)) % p;
}

// ============================================================================
// INCLUSION-EXCLUSION PRINCIPLE
// ============================================================================

long long inclusionExclusion(vector<int>& sets, int n, int mod = MOD) {
    long long result = 0;
    
    for (int mask = 1; mask < (1 << sets.size()); mask++) {
        long long intersection = n;
        int bits = __builtin_popcount(mask);
        
        for (int i = 0; i < sets.size(); i++) {
            if (mask & (1 << i)) {
                intersection /= sets[i];
            }
        }
        
        if (bits % 2 == 1) {
            result = (result + intersection) % mod;
        } else {
            result = (result - intersection + mod) % mod;
        }
    }
    
    return result;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testCombinatorics() {
    cout << "Testing Combinatorics:" << endl;
    
    int n = 10, r = 3;
    precomputeFactorials(n, MOD);
    
    cout << "C(10,3): " << nCr(10, 3, MOD) << endl;
    cout << "P(10,3): " << permutation(10, 3, MOD) << endl;
    cout << "Catalan(5): " << catalan(5, MOD) << endl;
    cout << "Derangement(5): " << derangement(5, MOD) << endl;
    
    cout << endl;
}

void testStirling() {
    cout << "Testing Stirling Numbers:" << endl;
    
    int n = 5, k = 3;
    cout << "Stirling2(5,3): " << stirling2(n, k, MOD) << endl;
    cout << "Stirling1(5,3): " << stirling1(n, k, MOD) << endl;
    
    cout << endl;
}

void testMatrixOperations() {
    cout << "Testing Matrix Operations:" << endl;
    
    vector<vector<long long>> matrix = {{1, 1}, {1, 0}};
    long long n = 10;
    
    cout << "Fibonacci(10): " << fibonacci(n, MOD) << endl;
    
    cout << endl;
}

void testProbability() {
    cout << "Testing Probability:" << endl;
    
    // Example: Expected value of die roll
    vector<pair<int, int>> outcomes = {{1, 1}, {2, 1}, {3, 1}, 
                                       {4, 1}, {5, 1}, {6, 1}};
    long long expected = expectedValue(outcomes, MOD);
    cout << "Expected value of die: " << (expected * modInverse(6, MOD)) % MOD << endl;
    
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Combinatorics & Mathematics Test Suite" << endl;
    cout << "======================================" << endl << endl;
    
    testCombinatorics();
    testStirling();
    testMatrixOperations();
    testProbability();
    
    return 0;
}

