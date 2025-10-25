# Number Theory in C++ for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Basic Number Theory Concepts](#basic-number-theory-concepts)
3. [Prime Numbers](#prime-numbers)
4. [GCD and LCM](#gcd-and-lcm)
5. [Modular Arithmetic](#modular-arithmetic)
6. [Euler's Totient Function](#eulers-totient-function)
7. [Chinese Remainder Theorem](#chinese-remainder-theorem)
8. [Combinatorics](#combinatorics)
9. [Advanced Topics](#advanced-topics)
10. [Practice Problems](#practice-problems)
11. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Number Theory is a fundamental branch of mathematics that deals with properties of integers. In competitive programming, number theory problems are very common and require efficient algorithms to solve within time constraints.

### What You'll Learn:
- Prime number algorithms (Sieve of Eratosthenes, Miller-Rabin)
- GCD/LCM calculations (Euclidean algorithm, Extended Euclidean)
- Modular arithmetic and exponentiation
- Euler's totient function and applications
- Chinese Remainder Theorem
- Combinatorics and counting problems
- Advanced topics like discrete logarithms

---

## Basic Number Theory Concepts

### Divisibility
A number `a` divides `b` (written as `a | b`) if there exists an integer `k` such that `b = a * k`.

```cpp
bool isDivisible(int a, int b) {
    return b % a == 0;
}
```

### Prime Numbers
A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.

```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
```

### Factorization
Finding all prime factors of a number.

```cpp
vector<int> getPrimeFactors(int n) {
    vector<int> factors;
    
    // Check for 2
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    
    // Check for odd numbers
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    
    // If n is still > 1, it's a prime factor
    if (n > 1) {
        factors.push_back(n);
    }
    
    return factors;
}
```

---

## Prime Numbers

### Sieve of Eratosthenes
Efficiently find all prime numbers up to a given limit.

```cpp
vector<bool> sieve(int n) {
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

// Get all primes up to n
vector<int> getPrimes(int n) {
    vector<bool> isPrime = sieve(n);
    vector<int> primes;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}
```

### Segmented Sieve
Find primes in a range [L, R] where R can be very large.

```cpp
vector<long long> segmentedSieve(long long L, long long R) {
    // Generate primes up to sqrt(R)
    long long limit = sqrt(R);
    vector<bool> isPrime = sieve(limit);
    vector<long long> primes = getPrimes(limit);
    
    // Create array for range [L, R]
    vector<bool> rangePrime(R - L + 1, true);
    
    for (long long p : primes) {
        long long start = max(p * p, (L + p - 1) / p * p);
        
        for (long long j = start; j <= R; j += p) {
            rangePrime[j - L] = false;
        }
    }
    
    vector<long long> result;
    for (long long i = L; i <= R; i++) {
        if (rangePrime[i - L]) {
            result.push_back(i);
        }
    }
    
    return result;
}
```

### Miller-Rabin Primality Test
Probabilistic test for large numbers.

```cpp
long long power(long long a, long long n, long long mod) {
    long long result = 1;
    a %= mod;
    
    while (n > 0) {
        if (n & 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        n >>= 1;
    }
    
    return result;
}

bool millerRabin(long long n, int k = 5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;
    
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        long long x = power(a, d, n);
        
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        for (int j = 0; j < d - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        
        if (composite) return false;
    }
    
    return true;
}
```

---

## GCD and LCM

### Euclidean Algorithm
Find the greatest common divisor efficiently.

```cpp
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Iterative version
int gcdIterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Built-in version
int gcdBuiltin(int a, int b) {
    return __gcd(a, b);
}
```

### Extended Euclidean Algorithm
Find GCD and coefficients x, y such that ax + by = gcd(a, b).

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
```

### LCM Calculation
Least Common Multiple using GCD.

```cpp
long long lcm(int a, int b) {
    return (long long)a * b / gcd(a, b);
}
```

### Applications
```cpp
// Check if two numbers are coprime
bool isCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

// Find modular inverse using Extended Euclidean
int modInverse(int a, int m) {
    int x, y;
    int g = extendedGcd(a, m, x, y);
    
    if (g != 1) {
        return -1; // Inverse doesn't exist
    }
    
    return (x % m + m) % m;
}
```

---

## Modular Arithmetic

### Basic Operations
```cpp
const int MOD = 1000000007;

int add(int a, int b) {
    return (a + b) % MOD;
}

int subtract(int a, int b) {
    return (a - b + MOD) % MOD;
}

int multiply(int a, int b) {
    return ((long long)a * b) % MOD;
}
```

### Modular Exponentiation
Fast exponentiation using binary method.

```cpp
long long power(long long base, long long exp, long long mod) {
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
```

### Modular Inverse
```cpp
// Using Fermat's Little Theorem (when mod is prime)
int modInverseFermat(int a, int mod) {
    return power(a, mod - 2, mod);
}

// Using Extended Euclidean Algorithm
int modInverseExtended(int a, int mod) {
    int x, y;
    int g = extendedGcd(a, mod, x, y);
    
    if (g != 1) return -1;
    
    return (x % mod + mod) % mod;
}
```

### Combinatorics with Modular Arithmetic
```cpp
// Precompute factorials and inverse factorials
vector<long long> fact, invFact;

void precomputeFactorials(int n, int mod) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    
    invFact[n] = modInverseFermat(fact[n], mod);
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

// nCr mod p
long long nCr(int n, int r, int mod) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}
```

---

## Euler's Totient Function

### Definition
φ(n) = number of integers from 1 to n that are coprime with n.

### Basic Implementation
```cpp
int eulerTotient(int n) {
    int result = n;
    
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}
```

### Using Sieve
```cpp
vector<int> eulerTotientSieve(int n) {
    vector<int> phi(n + 1);
    
    for (int i = 0; i <= n; i++) {
        phi[i] = i;
    }
    
    for (int p = 2; p <= n; p++) {
        if (phi[p] == p) { // p is prime
            for (int i = p; i <= n; i += p) {
                phi[i] -= phi[i] / p;
            }
        }
    }
    
    return phi;
}
```

### Applications
```cpp
// Euler's theorem: a^φ(n) ≡ 1 (mod n) when gcd(a, n) = 1
long long powerWithEuler(long long a, long long exp, long long mod) {
    if (gcd(a, mod) == 1) {
        exp = exp % eulerTotient(mod);
    }
    return power(a, exp, mod);
}
```

---

## Chinese Remainder Theorem

### Problem Statement
Given a system of congruences:
- x ≡ a₁ (mod m₁)
- x ≡ a₂ (mod m₂)
- ...
- x ≡ aₖ (mod mₖ)

Find x if m₁, m₂, ..., mₖ are pairwise coprime.

### Implementation
```cpp
int chineseRemainder(vector<int>& a, vector<int>& m) {
    int n = a.size();
    int M = 1;
    
    // Calculate M = m₁ * m₂ * ... * mₖ
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }
    
    int result = 0;
    
    for (int i = 0; i < n; i++) {
        int Mi = M / m[i];
        int Mi_inv = modInverseExtended(Mi, m[i]);
        
        result = (result + (long long)a[i] * Mi * Mi_inv) % M;
    }
    
    return result;
}
```

---

## Combinatorics

### Permutations and Combinations
```cpp
// Permutation: P(n, r) = n! / (n-r)!
long long permutation(int n, int r, int mod) {
    if (r > n) return 0;
    return (fact[n] * invFact[n - r]) % mod;
}

// Combination: C(n, r) = n! / (r! * (n-r)!)
long long combination(int n, int r, int mod) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}
```

### Catalan Numbers
```cpp
long long catalan(int n, int mod) {
    return combination(2 * n, n, mod) * modInverseFermat(n + 1, mod) % mod;
}
```

### Stirling Numbers
```cpp
// Stirling numbers of the second kind
vector<vector<long long>> stirling(int n, int k, int mod) {
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) {
            dp[i][j] = (dp[i - 1][j - 1] + j * dp[i - 1][j]) % mod;
        }
    }
    
    return dp;
}
```

---

## Advanced Topics

### Discrete Logarithm
Find x such that a^x ≡ b (mod m).

```cpp
int discreteLog(int a, int b, int m) {
    int n = sqrt(m) + 1;
    
    // Baby-step
    unordered_map<int, int> baby;
    int an = power(a, n, m);
    
    for (int p = 1, val = an; p <= n; p++) {
        if (baby.find(val) == baby.end()) {
            baby[val] = p;
        }
        val = (val * an) % m;
    }
    
    // Giant-step
    for (int q = 0, val = b; q <= n; q++) {
        if (baby.find(val) != baby.end()) {
            return baby[val] * n - q;
        }
        val = (val * a) % m;
    }
    
    return -1; // Not found
}
```

### Pollard's Rho Algorithm
Factor large numbers efficiently.

```cpp
long long pollardRho(long long n) {
    if (n == 1) return 1;
    if (n % 2 == 0) return 2;
    
    long long x = rand() % (n - 2) + 2;
    long long y = x;
    long long c = rand() % (n - 1) + 1;
    long long d = 1;
    
    while (d == 1) {
        x = (power(x, 2, n) + c) % n;
        y = (power(y, 2, n) + c) % n;
        y = (power(y, 2, n) + c) % n;
        d = gcd(abs(x - y), n);
    }
    
    return d;
}
```

---

## Practice Problems

### Easy Level:
1. Check if a number is prime
2. Find GCD of two numbers
3. Calculate LCM of two numbers
4. Find all divisors of a number
5. Count number of divisors

### Medium Level:
1. Sieve of Eratosthenes
2. Extended Euclidean Algorithm
3. Modular exponentiation
4. Euler's totient function
5. Chinese Remainder Theorem

### Hard Level:
1. Miller-Rabin primality test
2. Pollard's Rho factorization
3. Discrete logarithm
4. Advanced combinatorics
5. Number theory in cryptography

---

## Tips for Competitive Programming

### 1. Time Complexity Analysis
- **Sieve of Eratosthenes**: O(n log log n)
- **GCD (Euclidean)**: O(log min(a, b))
- **Modular Exponentiation**: O(log exp)
- **Prime Factorization**: O(√n)

### 2. Common Patterns
- **Prime checking**: Use trial division for small numbers, Miller-Rabin for large
- **GCD/LCM**: Always use Euclidean algorithm
- **Modular arithmetic**: Always use modular operations for large numbers
- **Combinatorics**: Precompute factorials for efficiency

### 3. Optimization Tips
- Use `__gcd()` built-in function when available
- Precompute factorials and inverse factorials
- Use bit manipulation for power of 2 operations
- Cache results for repeated calculations

### 4. Common Mistakes
- Integer overflow in modular arithmetic
- Forgetting to handle edge cases (n = 0, 1)
- Incorrect modular inverse calculation
- Not considering negative numbers in modular arithmetic

### 5. Debugging Tips
- Test with small examples first
- Verify results with known values
- Use modular arithmetic consistently
- Check for integer overflow

---

## Conclusion

Number Theory is essential for competitive programming. Master these concepts by:

1. **Understanding the fundamentals**: Divisibility, primes, GCD/LCM
2. **Learning efficient algorithms**: Sieve, Euclidean algorithm, modular exponentiation
3. **Practicing modular arithmetic**: Essential for handling large numbers
4. **Solving problems**: Start with basic problems and gradually increase difficulty
5. **Optimizing solutions**: Use precomputation and efficient algorithms

Remember: Practice makes perfect! Solve as many number theory problems as possible to internalize these concepts.

---

## Additional Resources

- **Online Judges**: Codeforces, CodeChef, AtCoder
- **Books**: "Introduction to Algorithms" by Cormen et al.
- **Practice**: Start with basic number theory, then move to advanced topics
- **Contests**: Participate in regular contests to apply these techniques

Good luck with your competitive programming journey!

