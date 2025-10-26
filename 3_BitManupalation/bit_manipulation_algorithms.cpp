#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BASIC BIT OPERATIONS
// ============================================================================

// Check if bit at position 'pos' is set (0-indexed)
bool isSet(int n, int pos) {
    return (n & (1 << pos)) != 0;
}

// Set bit at position 'pos'
int setBit(int n, int pos) {
    return n | (1 << pos);
}

// Clear bit at position 'pos'
int clearBit(int n, int pos) {
    return n & ~(1 << pos);
}

// Toggle bit at position 'pos'
int toggleBit(int n, int pos) {
    return n ^ (1 << pos);
}

// Update bit at position 'pos' with value 'val'
int updateBit(int n, int pos, int val) {
    int mask = ~(1 << pos);
    return (n & mask) | (val << pos);
}

// Clear all bits from LSB to i-th bit
int clearLSBtoI(int n, int i) {
    int mask = ~((1 << (i + 1)) - 1);
    return n & mask;
}

// Clear all bits from MSB to i-th bit
int clearMSBtoI(int n, int i) {
    int mask = (1 << i) - 1;
    return n & mask;
}

// ============================================================================
// COMMON BIT TRICKS
// ============================================================================

// Check if number is power of 2
bool isPowerOfTwo(int n) {
    return n && !(n & (n - 1));
}

// Get the position of MSB (Most Significant Bit)
int getMSB(int n) {
    int pos = 0;
    while (n >>= 1) {
        pos++;
    }
    return pos;
}

// Count set bits (Brian Kernighan's Algorithm)
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count++;
        n &= (n - 1);  // Clear the rightmost set bit
    }
    return count;
}

// Get the rightmost set bit
int getRightmostSetBit(int n) {
    return n & (-n);
}

// Get position of rightmost set bit
int getRightmostSetBitPos(int n) {
    if (n == 0) return -1;
    return log2(n & (-n));
}

// Toggle all bits in a number
int toggleAll(int n) {
    return ~n;
}

// Reverse bits in a number
unsigned int reverseBits(unsigned int n) {
    unsigned int result = 0;
    for (int i = 0; i < 32; i++) {
        if (n & (1 << i)) {
            result |= (1 << (31 - i));
        }
    }
    return result;
}

// Swap two bits in a number
int swapBits(int n, int p1, int p2) {
    int bit1 = (n >> p1) & 1;
    int bit2 = (n >> p2) & 1;
    
    if (bit1 != bit2) {
        n ^= (1 << p1);
        n ^= (1 << p2);
    }
    
    return n;
}

// Rotate bits left
unsigned int rotateLeft(unsigned int n, int d) {
    return (n << d) | (n >> (32 - d));
}

// Rotate bits right
unsigned int rotateRight(unsigned int n, int d) {
    return (n >> d) | (n << (32 - d));
}

// Swap even and odd bits
unsigned int swapEvenOdd(unsigned int n) {
    return ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
}

// ============================================================================
// ARITHMETIC OPERATIONS
// ============================================================================

// Add two numbers using bitwise operators
int add(int a, int b) {
    while (b != 0) {
        int carry = a & b;  // Common set bits
        a = a ^ b;          // Sum without carry
        b = carry << 1;     // Shift carry
    }
    return a;
}

// Multiply by power of 2
int multiplyByPowerOf2(int n, int power) {
    return n << power;
}

// Divide by power of 2
int divideByPowerOf2(int n, int power) {
    return n >> power;
}

// Check if two numbers have opposite signs
bool oppositeSigns(int x, int y) {
    return ((x ^ y) < 0);
}

// Get absolute value
int absValue(int n) {
    int mask = n >> (sizeof(int) * 8 - 1);
    return (n + mask) ^ mask;
}

// ============================================================================
// SUBSET GENERATION
// ============================================================================

// Generate all subsets using bitmasks
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

// Find subset with given sum
bool subsetSum(vector<int>& arr, int target) {
    int n = arr.size();
    int total = 1 << n;
    
    for (int mask = 0; mask < total; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }
        if (sum == target) {
            return true;
        }
    }
    return false;
}

// Count subsets with given sum
int countSubsetsWithSum(vector<int>& arr, int target) {
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
        if (sum == target) {
            count++;
        }
    }
    return count;
}

// Find maximum subset sum
int maxSubsetSum(vector<int>& arr) {
    int n = arr.size();
    int total = 1 << n;
    int maxSum = INT_MIN;
    
    for (int mask = 0; mask < total; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}

// ============================================================================
// XOR OPERATIONS
// ============================================================================

// Find single non-repeating number
int singleNumber(vector<int>& arr) {
    int result = 0;
    for (int num : arr) {
        result ^= num;
    }
    return result;
}

// Find two non-repeating numbers
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

// Find maximum XOR of two numbers
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

// Find XOR of all subsets
int XORofAllSubsets(vector<int>& arr) {
    // XOR of all subsets is always 0
    return 0;
}

// ============================================================================
// GRAY CODE
// ============================================================================

vector<int> grayCode(int n) {
    vector<int> result(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        result[i] = i ^ (i >> 1);
    }
    return result;
}

// ============================================================================
// COUNTING SET BITS IN RANGE
// ============================================================================

// Count total set bits from 1 to n
long long countSetBitsRange(int n) {
    if (n <= 0) return 0;
    
    long long ans = 0;
    long long powerOf2 = 1;
    
    while (powerOf2 <= n) {
        int pairs = (n + 1) / (2 * powerOf2);
        ans += (long long)pairs * powerOf2;
        
        int remaining = (n + 1) % (2 * powerOf2);
        ans += max(0, remaining - (int)powerOf2);
        
        powerOf2 <<= 1;
    }
    
    return ans;
}

// ============================================================================
// DYNAMIC PROGRAMMING WITH BITMASKS
// ============================================================================

// TSP using bitmask DP
const int INF = 1e9;

int tsp(vector<vector<int>>& dist, int n) {
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    
    // Starting from city 0
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }
    
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;
            
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                
                int newMask = mask | (1 << j);
                dp[newMask][j] = min(dp[newMask][j], dp[mask][i] + dist[i][j]);
            }
        }
    }
    
    int result = INF;
    int fullMask = (1 << n) - 1;
    
    for (int i = 0; i < n; i++) {
        result = min(result, dp[fullMask][i] + dist[i][0]);
    }
    
    return result;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testBasicOperations() {
    cout << "Testing Basic Operations:" << endl;
    
    int num = 5;  // 0101
    
    cout << "Original number: " << num << " (binary: " << bitset<8>(num) << ")" << endl;
    cout << "Bit 0 is set: " << isSet(num, 0) << endl;
    cout << "Bit 1 is set: " << isSet(num, 1) << endl;
    cout << "Bit 2 is set: " << isSet(num, 2) << endl;
    
    cout << "Set bit 1: " << setBit(num, 1) << endl;
    cout << "Clear bit 0: " << clearBit(num, 0) << endl;
    cout << "Toggle bit 2: " << toggleBit(num, 2) << endl;
    
    cout << "Is power of 2 (8): " << isPowerOfTwo(8) << endl;
    cout << "Is power of 2 (5): " << isPowerOfTwo(5) << endl;
    
    cout << "Count set bits in 15: " << countSetBits(15) << endl;
    
    cout << endl;
}

void testSubsets() {
    cout << "Testing Subset Generation:" << endl;
    
    vector<int> arr = {1, 2, 3};
    cout << "All subsets of [1, 2, 3]:" << endl;
    printSubsets(arr);
    
    cout << "Has subset with sum 5: " << subsetSum(arr, 5) << endl;
    cout << "Count subsets with sum 3: " << countSubsetsWithSum(arr, 3) << endl;
    
    cout << endl;
}

void testXOR() {
    cout << "Testing XOR Operations:" << endl;
    
    vector<int> arr1 = {1, 2, 2, 1, 3};
    cout << "Single non-repeating in [1,2,2,1,3]: " << singleNumber(arr1) << endl;
    
    vector<int> arr2 = {1, 2, 3, 2, 3, 4};
    auto result = twoNonRepeating(arr2);
    cout << "Two non-repeating in [1,2,3,2,3,4]: " << result.first << " " << result.second << endl;
    
    vector<int> arr3 = {1, 2, 3, 4};
    cout << "Max XOR in [1,2,3,4]: " << maxXOR(arr3) << endl;
    
    cout << endl;
}

void testGrayCode() {
    cout << "Testing Gray Code:" << endl;
    
    vector<int> gray = grayCode(3);
    cout << "Gray code for n=3: ";
    for (int x : gray) {
        cout << x << " ";
    }
    cout << endl << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Bit Manipulation Algorithms Test Suite" << endl;
    cout << "=====================================" << endl << endl;
    
    testBasicOperations();
    testSubsets();
    testXOR();
    testGrayCode();
    
    cout << "Using built-in functions:" << endl;
    int n = 15;
    cout << "Popcount of " << n << ": " << __builtin_popcount(n) << endl;
    cout << "Trailing zeros: " << __builtin_ctz(n) << endl;
    cout << "Leading zeros: " << __builtin_clz(n) << endl;
    
    return 0;
}

