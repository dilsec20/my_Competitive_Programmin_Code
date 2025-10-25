#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BASIC NUMBER THEORY FUNCTIONS
// ============================================================================

// Check if a number is prime
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

// Get all prime factors of a number
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

// ============================================================================
// SIEVE OF ERATOSTHENES
// ============================================================================

// Basic sieve - find all primes up to n
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

// Segmented sieve - find primes in range [L, R]
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

// ============================================================================
// GCD AND LCM
// ============================================================================

// Euclidean algorithm for GCD
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

// Extended Euclidean Algorithm
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

// LCM calculation
long long lcm(int a, int b) {
    return (long long)a * b / gcd(a, b);
}

// ============================================================================
// MODULAR ARITHMETIC
// ============================================================================

const int MOD = 1000000007;

// Modular addition
int add(int a, int b) {
    return (a + b) % MOD;
}

// Modular subtraction
int subtract(int a, int b) {
    return (a - b + MOD) % MOD;
}

// Modular multiplication
int multiply(int a, int b) {
    return ((long long)a * b) % MOD;
}

// Modular exponentiation (binary exponentiation)
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

// Modular inverse using Fermat's Little Theorem
int modInverseFermat(int a, int mod) {
    return power(a, mod - 2, mod);
}

// Modular inverse using Extended Euclidean Algorithm
int modInverseExtended(int a, int mod) {
    int x, y;
    int g = extendedGcd(a, mod, x, y);
    
    if (g != 1) return -1; // Inverse doesn't exist
    
    return (x % mod + mod) % mod;
}

// ============================================================================
// EULER'S TOTIENT FUNCTION
// ============================================================================

// Basic implementation
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

// Using sieve
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

// ============================================================================
// CHINESE REMAINDER THEOREM
// ============================================================================

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

// ============================================================================
// COMBINATORICS
// ============================================================================

vector<long long> fact, invFact;

// Precompute factorials and inverse factorials
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

// Permutation: P(n, r) = n! / (n-r)!
long long permutation(int n, int r, int mod) {
    if (r > n) return 0;
    return (fact[n] * invFact[n - r]) % mod;
}

// Catalan numbers
long long catalan(int n, int mod) {
    return nCr(2 * n, n, mod) * modInverseFermat(n + 1, mod) % mod;
}

// ============================================================================
// ADVANCED ALGORITHMS
// ============================================================================

// Miller-Rabin primality test
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

// Pollard's Rho algorithm for factorization
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

// Discrete logarithm using Baby-step Giant-step
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

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// Check if two numbers are coprime
bool isCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

// Count number of divisors
int countDivisors(int n) {
    int count = 1;
    vector<int> factors = getPrimeFactors(n);
    
    unordered_map<int, int> factorCount;
    for (int factor : factors) {
        factorCount[factor]++;
    }
    
    for (auto& p : factorCount) {
        count *= (p.second + 1);
    }
    
    return count;
}

// Sum of divisors
long long sumOfDivisors(int n) {
    long long sum = 1;
    vector<int> factors = getPrimeFactors(n);
    
    unordered_map<int, int> factorCount;
    for (int factor : factors) {
        factorCount[factor]++;
    }
    
    for (auto& p : factorCount) {
        long long term = 1;
        for (int i = 0; i <= p.second; i++) {
            term *= p.first;
        }
        sum *= (term - 1) / (p.first - 1);
    }
    
    return sum;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testBasicFunctions() {
    cout << "Testing Basic Functions:" << endl;
    
    // Test prime checking
    cout << "isPrime(17): " << isPrime(17) << endl;
    cout << "isPrime(15): " << isPrime(15) << endl;
    
    // Test prime factors
    vector<int> factors = getPrimeFactors(60);
    cout << "Prime factors of 60: ";
    for (int f : factors) cout << f << " ";
    cout << endl;
    
    // Test GCD
    cout << "GCD(48, 18): " << gcd(48, 18) << endl;
    
    // Test LCM
    cout << "LCM(12, 18): " << lcm(12, 18) << endl;
    
    // Test Euler's totient
    cout << "φ(12): " << eulerTotient(12) << endl;
    
    cout << endl;
}

void testSieve() {
    cout << "Testing Sieve:" << endl;
    
    vector<int> primes = getPrimes(50);
    cout << "Primes up to 50: ";
    for (int p : primes) cout << p << " ";
    cout << endl;
    
    cout << endl;
}

void testModularArithmetic() {
    cout << "Testing Modular Arithmetic:" << endl;
    
    // Test modular exponentiation
    cout << "2^10 mod 1000: " << power(2, 10, 1000) << endl;
    
    // Test modular inverse
    cout << "Inverse of 3 mod 7: " << modInverseExtended(3, 7) << endl;
    
    cout << endl;
}

void testCombinatorics() {
    cout << "Testing Combinatorics:" << endl;
    
    precomputeFactorials(10, MOD);
    
    // Test combinations
    cout << "C(5, 2): " << nCr(5, 2, MOD) << endl;
    
    // Test permutations
    cout << "P(5, 2): " << permutation(5, 2, MOD) << endl;
    
    // Test Catalan numbers
    cout << "Catalan(4): " << catalan(4, MOD) << endl;
    
    cout << endl;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Number Theory Algorithms Test Suite" << endl;
    cout << "===================================" << endl << endl;
    
    testBasicFunctions();
    testSieve();
    testModularArithmetic();
    testCombinatorics();
    
    return 0;
}
