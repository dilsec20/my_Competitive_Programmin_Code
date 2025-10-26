# Combinatorics & Mathematics Quick Reference

## Key Formulas

### Combinatorics
```cpp
// nCr
C(n, r) = n! / (r! × (n-r)!)

// Catalan
Catalan(n) = C(2n, n) / (n+1)

// Permutation
P(n, r) = n! / (n-r)!

// Derangement
D(n) = (n-1) × (D(n-1) + D(n-2))
```

### Modular Arithmetic
```cpp
// Modulo operations
(a + b) % mod = ((a % mod) + (b % mod)) % mod
(a × b) % mod = ((a % mod) × (b % mod)) % mod

// Modular inverse
inv(a) = a^(mod-2) mod (prime mod)
```

### Matrix Operations
```cpp
// Matrix multiplication: O(n³)
result = A × B

// Matrix exponentiation: O(n³ log n)
A^k = power(A, k)
```

## Common Patterns

### Pattern 1: Precompute Factorials
```cpp
precomputeFactorials(maxN, MOD);
long long result = nCr(n, r, MOD);
```

### Pattern 2: Matrix Exponentiation
```cpp
vector<vector<long long>> result = matrixPower(base, exponent, MOD);
```

### Pattern 3: Chinese Remainder
```cpp
int result = chineseRemainder(a, m);
```

## See Also
- [Combinatorics_Mathematics_Guide.md](Combinatorics_Mathematics_Guide.md)
- [combinatorics_mathematics.cpp](combinatorics_mathematics.cpp)

