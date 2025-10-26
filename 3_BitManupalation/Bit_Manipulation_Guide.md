# Bit Manipulation in C++ for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Basic Bit Operations](#basic-bit-operations)
3. [Common Bit Tricks](#common-bit-tricks)
4. [Advanced Techniques](#advanced-techniques)
5. [Practice Problems](#practice-problems)
6. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Bit manipulation is the act of algorithmically manipulating bits or binary data. It is fundamental in competitive programming and system programming for optimizing memory usage and improving performance.

### What You'll Learn:
- Basic bitwise operations (AND, OR, XOR, NOT, Shift)
- Common bit manipulation tricks and shortcuts
- Finding set bits, toggling bits, clearing bits
- Subset generation using bitmasks
- Bit manipulation in DP and optimization
- Advanced techniques for competitive programming

---

## Basic Bit Operations

### Basic Operators

```cpp
// AND (&) - Both bits must be 1
int a = 5;  // 0101
int b = 3;  // 0011
int result = a & b;  // 0001 = 1

// OR (|) - At least one bit must be 1
result = a | b;  // 0111 = 7

// XOR (^) - Bits differ
result = a ^ b;  // 0110 = 6

// NOT (~) - Flip all bits
result = ~a;  // Depends on data type size

// Left Shift (<<) - Multiply by 2
result = a << 1;  // 1010 = 10 (5 * 2)

// Right Shift (>>) - Divide by 2
result = a >> 1;  // 0010 = 2 (5 / 2)
```

### Checking if a Bit is Set

```cpp
bool isSet(int n, int pos) {
    return (n & (1 << pos)) != 0;
}

// Example: Check if 3rd bit (0-indexed) is set in 13 (1101)
// isSet(13, 2) returns true
```

### Setting a Bit

```cpp
int setBit(int n, int pos) {
    return n | (1 << pos);
}

// Example: Set 2nd bit in 5 (0101)
// setBit(5, 2) returns 7 (0111)
```

### Clearing a Bit

```cpp
int clearBit(int n, int pos) {
    return n & ~(1 << pos);
}

// Example: Clear 0th bit in 7 (0111)
// clearBit(7, 0) returns 6 (0110)
```

### Toggling a Bit

```cpp
int toggleBit(int n, int pos) {
    return n ^ (1 << pos);
}

// Example: Toggle 1st bit in 5 (0101)
// toggleBit(5, 1) returns 7 (0111)
```

---

## Common Bit Tricks

### Check if Power of 2

```cpp
bool isPowerOfTwo(int n) {
    return n && !(n & (n - 1));
}

// Logic: Power of 2 has only one set bit
// Example: 8 (1000) & 7 (0111) = 0
```

### Count Set Bits (Brian Kernighan's Algorithm)

```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count++;
        n &= (n - 1);  // Clear the rightmost set bit
    }
    return count;
}

// Time Complexity: O(number of set bits)
```

### Find Log Base 2

```cpp
int log2(int n) {
    int pos = 0;
    while (n >>= 1) {
        pos++;
    }
    return pos;
}
```

### Get the Rightmost Set Bit

```cpp
int getRightmostSetBit(int n) {
    return n & (-n);
}

// Alternative
int getRightmostSetBitPos(int n) {
    return log2(n & (-n));
}
```

### Clear All Bits from LSB to i-th Bit

```cpp
int clearLSBtoI(int n, int i) {
    int mask = ~((1 << (i + 1)) - 1);
    return n & mask;
}

// Example: Clear bits 0-2 in 15 (1111)
// Returns 8 (1000)
```

### Clear All Bits from MSB to i-th Bit

```cpp
int clearMSBtoI(int n, int i) {
    int mask = (1 << i) - 1;
    return n & mask;
}

// Example: Clear bits 3-2 in 15 (1111)
// Returns 3 (0011)
```

### Divide by Power of 2

```cpp
int divideByPowerOf2(int n, int power) {
    return n >> power;
}

// Example: divideByPowerOf2(16, 2) = 16 >> 2 = 4
```

### Multiply by Power of 2

```cpp
int multiplyByPowerOf2(int n, int power) {
    return n << power;
}

// Example: multiplyByPowerOf2(4, 2) = 4 << 2 = 16
```

### Swap Two Numbers

```cpp
void swap(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    b = a ^ b;
}
```

### Check if Two Numbers Have Opposite Signs

```cpp
bool oppositeSigns(int x, int y) {
    return ((x ^ y) < 0);
}
```

### Get Absolute Value

```cpp
int absValue(int n) {
    int mask = n >> (sizeof(int) * 8 - 1);
    return (n + mask) ^ mask;
}
```

---

## Advanced Techniques

### Generating All Subsets Using Bitmasks

```cpp
void printSubsets(vector<int>& arr) {
    int n = arr.size();
    int total = 1 << n;  // 2^n
    
    for (int mask = 0; mask < total; mask++) {
        cout << "{ ";
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                cout << arr[i] << " ";
            }
        }
        cout << "}\n";
    }
}

// Example: arr = [1, 2, 3]
// Output: {}, {1}, {2}, {1,2}, {3}, {1,3}, {2,3}, {1,2,3}
```

### Find All Subsets with Given Sum

```cpp
int subsetsWithSum(vector<int>& arr, int target) {
    int n = arr.size();
    int total = 1 << n;
    int count = 0;
    
    for (int mask = 0; mask < total; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }
        if (sum == target) count++;
    }
    return count;
}
```

### Find Maximum XOR of Two Numbers in Array

```cpp
int maxXOR(vector<int>& arr) {
    int maxXOR = 0;
    int n = arr.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            maxXOR = max(maxXOR, arr[i] ^ arr[j]);
        }
    }
    return maxXOR;
}
```

### Find Single Number (All appear twice except one)

```cpp
int singleNumber(vector<int>& arr) {
    int result = 0;
    for (int num : arr) {
        result ^= num;
    }
    return result;
}

// XOR properties:
// a ^ a = 0
// a ^ 0 = a
// All pairs cancel out, leaving the single number
```

### Find Two Non-Repeating Numbers

```cpp
pair<int, int> twoNonRepeating(vector<int>& arr) {
    int XOR = 0;
    for (int num : arr) {
        XOR ^= num;
    }
    
    // Get rightmost set bit
    int rightmost = XOR & (-XOR);
    
    int x = 0, y = 0;
    for (int num : arr) {
        if (num & rightmost) {
            x ^= num;
        } else {
            y ^= num;
        }
    }
    
    return {min(x, y), max(x, y)};
}
```

### Gray Code

```cpp
vector<int> grayCode(int n) {
    vector<int> result(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        result[i] = i ^ (i >> 1);
    }
    return result;
}
```

### Count Total Set Bits from 1 to n

```cpp
int countSetBitsRange(int n) {
    if (n <= 0) return 0;
    
    int ans = 0;
    int powerOf2 = 1;
    
    while (powerOf2 <= n) {
        int pairs = (n + 1) / (2 * powerOf2);
        ans += pairs * powerOf2;
        
        int remaining = (n + 1) % (2 * powerOf2);
        ans += max(0, remaining - powerOf2);
        
        powerOf2 <<= 1;
    }
    
    return ans;
}
```

### Reverse Bits

```cpp
uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        if (n & (1 << i)) {
            result |= (1 << (31 - i));
        }
    }
    return result;
}
```

### Find XOR of All Subsets

```cpp
int XORofSubsets(vector<int>& arr) {
    // XOR of all subsets is always 0
    return 0;
}
```

### Swap Bits

```cpp
int swapBits(int n, int p1, int p2) {
    int bit1 = (n >> p1) & 1;
    int bit2 = (n >> p2) & 1;
    
    if (bit1 != bit2) {
        n ^= (1 << p1);
        n ^= (1 << p2);
    }
    
    return n;
}
```

---

## Bit Manipulation in Dynamic Programming

### Counting Ways with Bitmasks

```cpp
// Example: TSP (Traveling Salesman Problem)
int tsp(int mask, int pos, vector<vector<int>>& dist) {
    int n = dist.size();
    int VISITED_ALL = (1 << n) - 1;
    
    if (mask == VISITED_ALL) {
        return dist[pos][0];  // Return to starting city
    }
    
    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, dist);
            ans = min(ans, newAns);
        }
    }
    return ans;
}
```

### Subset Sum with Bitmask DP

```cpp
bool subsetSum(vector<int>& arr, int target) {
    int n = arr.size();
    vector<bool> dp(1 << n, false);
    dp[0] = true;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask]) {
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    int sum = 0;
                    for (int j = 0; j < n; j++) {
                        if (mask & (1 << j)) {
                            sum += arr[j];
                        }
                    }
                    if (sum + arr[i] <= target) {
                        dp[mask | (1 << i)] = true;
                    }
                }
            }
        }
    }
    
    return dp[(1 << n) - 1];
}
```

---

## Practice Problems

### Easy Level (800-1200)
1. Find XOR of array elements
2. Count set bits in a number
3. Check power of 2
4. Swap even and odd bits
5. Find missing number in array

### Medium Level (1200-1800)
1. Maximum XOR of two numbers
2. Gray code generation
3. Subset sum with constraints
4. Bit manipulation in strings
5. Finding single/double non-repeating numbers

### Hard Level (1800+)
1. TSP with bitmasks
2. Maximum AND value pair
3. Advanced subset problems
4. Bit DP optimization
5. Bit manipulation in trees/graphs

---

## Tips for Competitive Programming

### 1. Time Complexity Analysis
- **Count set bits**: O(number of set bits) - Brian Kernighan's
- **Subset generation**: O(n × 2^n) for n elements
- **Bit operations**: O(1) time complexity

### 2. Common Patterns
- **XOR trick**: XOR a number with itself gives 0
- **Power of 2**: Check with `n & (n-1) == 0`
- **Masking**: Use bitmasks for subset generation
- **DP with bitmasks**: Common in state space problems

### 3. Optimization Tips
- Use bitwise operations instead of arithmetic when possible
- Precompute masks for repeated operations
- Use `__builtin_popcount()` for set bit count (GCC)
- Use `__builtin_clz()` for leading zeros (GCC)
- Use `__builtin_ctz()` for trailing zeros (GCC)

### 4. Common Mistakes
- Forgetting to initialize bitmasks properly
- Off-by-one errors in bit positions
- Not considering integer overflow
- Confusing left/right shift directions

### 5. Debugging Tips
- Print binary representation: `bitset<32>(n)`
- Test with small examples first
- Verify edge cases (0, negative numbers)
- Use `__builtin_` functions for debugging

### 6. Useful Built-in Functions (GCC)

```cpp
// Count set bits
int count = __builtin_popcount(n);
int countLL = __builtin_popcountll(n);  // For long long

// Count leading zeros
int leadingZeros = __builtin_clz(n);

// Count trailing zeros
int trailingZeros = __builtin_ctz(n);

// Check parity
bool parity = __builtin_parity(n);
```

### 7. Quick Reference

| Operation | Code | Result |
|-----------|------|--------|
| Set bit | `n \| (1 << i)` | Set i-th bit |
| Clear bit | `n & ~(1 << i)` | Clear i-th bit |
| Toggle bit | `n ^ (1 << i)` | Toggle i-th bit |
| Check bit | `n & (1 << i)` | Check if i-th bit is set |
| Clear LSB | `n & (n - 1)` | Clear rightmost set bit |
| Get LSB | `n & (-n)` | Get rightmost set bit |
| Check power of 2 | `n && !(n & (n-1))` | True if power of 2 |

---

## Common Bit Manipulation Applications

### 1. Efficient Storage
- Store multiple boolean values in a single integer
- Represent subsets as integers
- Compress data structures

### 2. Fast Arithmetic
- Multiplication/division by powers of 2
- Checking even/odd with `n & 1`
- Finding multiples quickly

### 3. Optimization
- Reducing space complexity
- Speeding up operations
- Simplifying complex algorithms

### 4. State Representation
- TSP and similar problems
- DP with small state space
- Game theory problems

---

## Conclusion

Bit manipulation is essential for competitive programming. Master these concepts by:

1. **Understanding the fundamentals**: Basic operations and their properties
2. **Learning common tricks**: Power of 2, XOR properties, subset generation
3. **Practicing problems**: Start with easy problems, gradually increase difficulty
4. **Optimizing solutions**: Use bit operations instead of arithmetic when possible
5. **Applying in DP**: Learn to use bitmasks in dynamic programming

Remember: Practice makes perfect! Solve as many bit manipulation problems as possible.

---

## Additional Resources

- **Online Judges**: Codeforces, CodeChef, AtCoder
- **Practice**: Start with basic operations, then move to advanced techniques
- **Contests**: Participate in contests to apply these techniques
- **Books**: "Competitive Programming" by Steven & Felix Halim

Good luck with your competitive programming journey!

