# Bit Manipulation Quick Reference

## Quick Tips & Shortcuts

### Common Operations
```cpp
// Check if bit is set
bool isSet(int n, int pos) { return n & (1 << pos); }

// Set a bit
int setBit(int n, int pos) { return n | (1 << pos); }

// Clear a bit  
int clearBit(int n, int pos) { return n & ~(1 << pos); }

// Toggle a bit
int toggleBit(int n, int pos) { return n ^ (1 << pos); }

// Check power of 2
bool isPowerOf2(int n) { return n && !(n & (n - 1)); }

// Count set bits
int countSetBits(int n) {
    int count = 0;
    while (n) { count++; n &= (n - 1); }
    return count;
}

// Get rightmost set bit
int getLSB(int n) { return n & (-n); }
```

### XOR Tricks
```cpp
// Swap numbers
void swap(int &a, int &b) { a ^= b; b ^= a; a ^= b; }

// Find single non-repeating number
int singleNumber(vector<int>& arr) {
    int result = 0;
    for (int x : arr) result ^= x;
    return result;
}

// Check opposite signs
bool oppositeSigns(int x, int y) { return (x ^ y) < 0; }
```

### Subset Generation
```cpp
// Generate all subsets
void subsets(vector<int>& arr) {
    int n = arr.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                // arr[i] is in subset
            }
        }
    }
}
```

### Built-in Functions (GCC)
```cpp
__builtin_popcount(n)      // Count set bits
__builtin_clz(n)           // Count leading zeros  
__builtin_ctz(n)           // Count trailing zeros
__builtin_parity(n)        // Parity (odd/even)
```

## See Also
- [Bit_Manipulation_Guide.md](Bit_Manipulation_Guide.md) - Complete guide
- [bit_manipulation_algorithms.cpp](bit_manipulation_algorithms.cpp) - Code implementations
- [practice_problems_list.md](practice_problems_list.md) - Problem lists

