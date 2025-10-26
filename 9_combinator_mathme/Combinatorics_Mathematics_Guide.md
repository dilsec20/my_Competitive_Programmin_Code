# Combinatorics & Advanced Mathematics for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Combinatorics](#combinatorics)
3. [Advanced Number Theory](#advanced-number-theory)
4. [Linear Algebra](#linear-algebra)
5. [Probability & Statistics](#probability--statistics)
6. [Practice Problems](#practice-problems)
7. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Mathematics is fundamental in competitive programming. This guide covers combinatorics, advanced number theory, linear algebra, and probability - essential topics for solving complex problems.

### What You'll Learn:
- Combinatorics: permutations, combinations, Catalan numbers
- Advanced number theory: GCD, LCM, modular arithmetic
- Linear algebra: matrix operations, determinants
- Probability and statistics
- Game theory basics

---

## Combinatorics

### 1. Basic Formulas

#### Factorial
```cpp
long long factorial(int n, int mod = 1e9+7) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % mod;
    }
    return result;
}
```

#### Permutations: P(n, r)
```cpp
// Ways to arrange r objects from n distinct objects
long long permutation(int n, int r, int mod = 1e9+7) {
    if (r > n) return 0;
    long long result = 1;
    for (int i = n; i > n - r; i--) {
        result = (result * i) % mod;
    }
    return result;
}
```

#### Combinations: C(n, r) = n! / (r! × (n-r)!)
```cpp
// Precompute factorials
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

long long nCr(int n, int r, int mod) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n-r] % mod;
}
```

### 2. Catalan Numbers

```cpp
// Catalan(n) = C(2n, n) / (n + 1)
long long catalan(int n, int mod) {
    return nCr(2 * n, n, mod) * modInverse(n + 1, mod) % mod;
}

// Applications:
// - Number of valid parentheses
// - Number of binary trees
// - Number of paths that don't cross diagonal
```

### 3. Stirling Numbers

#### Stirling Numbers of the Second Kind
```cpp
// S(n, k) = ways to partition n objects into k non-empty subsets
long long stirling2(int n, int k, int mod) {
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) {
            dp[i][j] = (dp[i-1][j-1] + j * dp[i-1][j] % mod) % mod;
        }
    }
    
    return dp[n][k];
}
```

### 4. Derangements

```cpp
// D(n) = (n-1) × (D(n-1) + D(n-2))
long long derangement(int n, int mod) {
    if (n <= 1) return (n == 0);
    
    long long prev2 = 1, prev1 = 0;
    for (int i = 2; i <= n; i++) {
        long long current = (i - 1) * (prev1 + prev2) % mod;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}
```

### 5. Inclusion-Exclusion Principle

```cpp
// Count elements in at least one set
long long inclusionExclusion(vector<int>& sets, int n, int mod) {
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
```

---

## Advanced Number Theory

### 1. Extended GCD

```cpp
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

// Modular inverse
int modInverse(int a, int mod) {
    int x, y;
    int g = extendedGcd(a, mod, x, y);
    if (g != 1) return -1;
    return (x % mod + mod) % mod;
}
```

### 2. Chinese Remainder Theorem

```cpp
int chineseRemainder(vector<int>& a, vector<int>& m) {
    int n = a.size();
    int M = 1;
    for (int i = 0; i < n; i++) M *= m[i];
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        int Mi = M / m[i];
        int Mi_inv = modInverse(Mi, m[i]);
        result = (result + (long long)a[i] * Mi % M * Mi_inv % M) % M;
    }
    return result;
}
```

### 3. Lucas' Theorem

```cpp
// C(n, r) mod p where p is prime
long long lucas(int n, int r, int p) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    
    return (lucas(n / p, r / p, p) * 
            nCr(n % p, r % p, p)) % p;
}
```

---

## Linear Algebra

### 1. Matrix Multiplication

```cpp
vector<vector<long long>> matrixMultiply(vector<vector<long long>>& a, 
                                          vector<vector<long long>>& b, 
                                          int mod) {
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
```

### 2. Matrix Exponentiation

```cpp
vector<vector<long long>> matrixPower(vector<vector<long long>> base, 
                                      long long exp, int mod) {
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
```

### 3. Determinant

```cpp
long long determinant(vector<vector<long long>>& matrix, int mod) {
    int n = matrix.size();
    long long det = 1;
    
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 0) {
            // Find non-zero element and swap rows
            for (int j = i + 1; j < n; j++) {
                if (matrix[j][i] != 0) {
                    swap(matrix[i], matrix[j]);
                    det = (det * (mod - 1)) % mod;
                    break;
                }
            }
            if (matrix[i][i] == 0) return 0;
        }
        
        long long inv = modInverse(matrix[i][i], mod);
        
        for (int j = i + 1; j < n; j++) {
            long long factor = (matrix[j][i] * inv) % mod;
            for (int k = i; k < n; k++) {
                matrix[j][k] = (matrix[j][k] - (factor * matrix[i][k]) % mod + mod) % mod;
            }
        }
        
        det = (det * matrix[i][i]) % mod;
    }
    
    return det;
}
```

---

## Probability & Statistics

### 1. Expected Value

```cpp
// E[X] = Σ(x × P(X = x))
long long expectedValue(vector<pair<int, int>>& outcomes, int mod) {
    long long result = 0;
    
    for (auto& [value, probability] : outcomes) {
        result = (result + (long long)value * probability) % mod;
    }
    
    return result;
}
```

### 2. Binomial Distribution

```cpp
// P(X = k) in n trials with probability p
long long binomialProbability(int n, int k, int p, int mod) {
    long long C = nCr(n, k, mod);
    long long prob_k = power(p, k, mod);
    long long prob_n_minus_k = power(mod + 1 - p, n - k, mod);
    return (C * prob_k % mod) * prob_n_minus_k % mod;
}
```

### 3. Geometric Distribution

```cpp
// Expected value of first success
long long geometricExpected(int p, int mod) {
    // E = 1 / p
    return modInverse(p, mod);
}
```

---

## Practice Problems

### Easy Level (800-1200)
1. Basic Combinatorics
2. Binomial Coefficients
3. Catalan Numbers
4. Simple Probability
5. Matrix Addition

### Medium Level (1200-1800)
1. Advanced Combinatorics
2. Lucas' Theorem
3. Matrix Exponentiation
4. Expected Value Problems
5. Inclusion-Exclusion

### Hard Level (1800+)
1. Advanced Probability
2. Complex Combinatorial Problems
3. Matrix Determinant
4. Game Theory
5. Research-level Mathematics

---

## Tips for Competitive Programming

### 1. Common Formulas to Memorize
- nCr = n! / (r! × (n-r)!)
- Catalan(n) = C(2n, n) / (n+1)
- Derangement(n) = (n-1) × (D(n-1) + D(n-2))
- Stirling2(n, k) = k×S(n-1, k) + S(n-1, k-1)

### 2. When to Use
- **Combinatorics**: Counting problems, arrangements
- **Number Theory**: GCD, LCM, modular arithmetic
- **Linear Algebra**: Recurrence relations, transformations
- **Probability**: Expected value, random processes

### 3. Common Mistakes
- Integer overflow (use long long)
- Wrong formula application
- Not handling mod properly
- Off-by-one errors

---

## Conclusion

Master these mathematical concepts by:
1. Understanding formulas and their proofs
2. Practicing implementation
3. Recognizing problem patterns
4. Handling edge cases
5. Optimizing with precomputation

Good luck with your competitive programming journey!

