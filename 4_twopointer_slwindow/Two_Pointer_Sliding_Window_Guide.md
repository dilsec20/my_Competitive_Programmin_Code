# Two Pointers and Sliding Window Technique in C++ for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Two Pointers Technique](#two-pointers-technique)
3. [Sliding Window Technique](#sliding-window-technique)
4. [Common Patterns](#common-patterns)
5. [Advanced Techniques](#advanced-techniques)
6. [Practice Problems](#practice-problems)
7. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Two Pointers and Sliding Window are essential techniques for solving array and string problems efficiently. They help reduce time complexity from O(n²) to O(n) by intelligently traversing data structures.

### What You'll Learn:
- Two pointers technique for array problems
- Sliding window for subarray/substring problems
- Fast and slow pointers pattern
- Window size optimization
- Deque-based sliding window
- Common patterns and optimizations

---

## Two Pointers Technique

### Basic Concept

The two pointers technique uses two pointers (or indices) to traverse an array/string from different positions, often from both ends or both moving in the same direction.

### Types of Two Pointers

#### 1. Opposite Ends (Start and End)
Used for sorted arrays, palindrome checking, and finding pairs.

```cpp
void oppositeEnds(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            // Found pair
            return;
        } else if (sum < target) {
            left++;  // Need larger sum
        } else {
            right--;  // Need smaller sum
        }
    }
}
```

#### 2. Both Forward (Fast and Slow)
Used for cycle detection, removing duplicates, and partition problems.

```cpp
void bothForward(vector<int>& arr) {
    int slow = 0;
    for (int fast = 0; fast < arr.size(); fast++) {
        if (condition) {
            arr[slow++] = arr[fast];
        }
    }
}
```

#### 3. Three Pointers
Used for problems like Dutch National Flag, three sum, etc.

```cpp
void threePointers(vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;
    
    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low++], arr[mid++]);
        } else if (arr[mid] == 1) {
            mid++;
        } else {
            swap(arr[mid], arr[high--]);
        }
    }
}
```

---

## Common Two Pointer Patterns

### 1. Two Sum (Sorted Array)

```cpp
pair<int, int> twoSum(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {-1, -1};
}
```

### 2. Remove Duplicates from Sorted Array

```cpp
int removeDuplicates(vector<int>& arr) {
    if (arr.empty()) return 0;
    
    int writeIndex = 1;
    for (int readIndex = 1; readIndex < arr.size(); readIndex++) {
        if (arr[readIndex] != arr[readIndex - 1]) {
            arr[writeIndex++] = arr[readIndex];
        }
    }
    return writeIndex;
}
```

### 3. Container With Most Water

```cpp
int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        int width = right - left;
        int minHeight = min(height[left], height[right]);
        maxWater = max(maxWater, width * minHeight);
        
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxWater;
}
```

### 4. Trapping Rain Water

```cpp
int trapWater(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxLeft = 0, maxRight = 0;
    int water = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= maxLeft) {
                maxLeft = height[left];
            } else {
                water += maxLeft - height[left];
            }
            left++;
        } else {
            if (height[right] >= maxRight) {
                maxRight = height[right];
            } else {
                water += maxRight - height[right];
            }
            right--;
        }
    }
    return water;
}
```

### 5. Three Sum

```cpp
vector<vector<int>> threeSum(vector<int>& arr) {
    vector<vector<int>> result;
    int n = arr.size();
    sort(arr.begin(), arr.end());
    
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == 0) {
                result.push_back({arr[i], arr[left], arr[right]});
                while (left < right && arr[left] == arr[left + 1]) left++;
                while (left < right && arr[right] == arr[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}
```

### 6. Palindrome Checking

```cpp
bool isPalindrome(string s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        // Skip non-alphanumeric
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

---

## Sliding Window Technique

### Basic Concept

Sliding Window technique maintains a window of elements and slides it to find optimal solutions for subarray/substring problems.

### Types of Sliding Window

#### 1. Fixed Size Window
Window size is fixed (k).

```cpp
int fixedWindow(vector<int>& arr, int k) {
    int windowSum = 0;
    
    // Calculate first window
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    int maxSum = windowSum;
    
    // Slide the window
    for (int i = k; i < arr.size(); i++) {
        windowSum = windowSum - arr[i - k] + arr[i];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

#### 2. Variable Size Window
Window size varies based on condition.

```cpp
int variableWindow(vector<int>& arr, int target) {
    int left = 0;
    int sum = 0;
    int minLen = INT_MAX;
    
    for (int right = 0; right < arr.size(); right++) {
        sum += arr[right];
        
        while (sum >= target) {
            minLen = min(minLen, right - left + 1);
            sum -= arr[left++];
        }
    }
    
    return (minLen == INT_MAX) ? 0 : minLen;
}
```

#### 3. At Most/At Least Pattern
Window with "at most k" or "at least k" constraint.

```cpp
int atMostK(vector<int>& arr, int k) {
    int left = 0;
    int result = 0;
    unordered_map<int, int> count;
    
    for (int right = 0; right < arr.size(); right++) {
        count[arr[right]]++;
        
        // Shrink window if > k unique elements
        while (count.size() > k) {
            count[arr[left]]--;
            if (count[arr[left]] == 0) {
                count.erase(arr[left]);
            }
            left++;
        }
        
        result += right - left + 1;
    }
    return result;
}
```

---

## Common Sliding Window Patterns

### 1. Maximum Sum Subarray of Size K

```cpp
int maxSumK(vector<int>& arr, int k) {
    int windowSum = 0;
    
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    
    int maxSum = windowSum;
    for (int i = k; i < arr.size(); i++) {
        windowSum = windowSum - arr[i - k] + arr[i];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

### 2. Longest Substring Without Repeating Characters

```cpp
int longestUniqueSubstring(string s) {
    unordered_map<char, int> charMap;
    int left = 0;
    int maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        if (charMap.find(s[right]) != charMap.end()) {
            left = max(left, charMap[s[right]] + 1);
        }
        charMap[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

### 3. Minimum Window Substring

```cpp
string minWindow(string s, string t) {
    unordered_map<char, int> need, have;
    for (char c : t) need[c]++;
    
    int left = 0;
    int minLen = INT_MAX;
    int start = 0;
    int haveCount = 0;
    
    for (int right = 0; right < s.length(); right++) {
        if (need.find(s[right]) != need.end()) {
            have[s[right]]++;
            if (have[s[right]] == need[s[right]]) {
                haveCount++;
            }
        }
        
        while (haveCount == need.size()) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }
            
            if (need.find(s[left]) != need.end()) {
                if (have[s[left]] == need[s[left]]) {
                    haveCount--;
                }
                have[s[left]]--;
            }
            left++;
        }
    }
    
    return (minLen == INT_MAX) ? "" : s.substr(start, minLen);
}
```

### 4. Sliding Window Maximum

```cpp
vector<int> slidingWindowMax(vector<int>& arr, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < arr.size(); i++) {
        // Remove indices outside window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove elements smaller than current
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    
    return result;
}
```

### 5. Number of Subarrays with At Most K Distinct Elements

```cpp
int subarraysWithAtMostK(vector<int>& arr, int k) {
    int left = 0;
    int result = 0;
    unordered_map<int, int> count;
    
    for (int right = 0; right < arr.size(); right++) {
        count[arr[right]]++;
        
        while (count.size() > k) {
            count[arr[left]]--;
            if (count[arr[left]] == 0) {
                count.erase(arr[left]);
            }
            left++;
        }
        
        result += right - left + 1;
    }
    
    return result;
}
```

### 6. Longest Substring with K Distinct Characters

```cpp
int longestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> charMap;
    int left = 0;
    int maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        charMap[s[right]]++;
        
        while (charMap.size() > k) {
            charMap[s[left]]--;
            if (charMap[s[left]] == 0) {
                charMap.erase(s[left]);
            }
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

---

## Advanced Techniques

### 1. Deque-Based Sliding Window

```cpp
// Monotonic Deque for range queries
class MonotonicDeque {
public:
    deque<pair<int, int>> dq;  // {value, index}
    
    void push(int val, int idx) {
        while (!dq.empty() && dq.back().first <= val) {
            dq.pop_back();
        }
        dq.push_back({val, idx});
    }
    
    void pop(int idx) {
        if (!dq.empty() && dq.front().second == idx) {
            dq.pop_front();
        }
    }
    
    int max() {
        return dq.front().first;
    }
};
```

### 2. Two Pass Sliding Window

```cpp
int twoPassSlidingWindow(vector<int>& arr) {
    // First pass: expand window
    int left = 0;
    int maxLen = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        // Expand window based on condition
        while (/* condition */) {
            // Process expanding window
        }
        maxLen = max(maxLen, right - left + 1);
    }
    
    // Second pass: contract window
    for (int i = 0; i < arr.size(); i++) {
        // Contract and process
    }
    
    return maxLen;
}
```

### 3. Prefix Sum with Sliding Window

```cpp
int subarraySum(vector<int>& arr, int target) {
    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0;
    int count = 0;
    
    for (int num : arr) {
        sum += num;
        if (prefixSum.find(sum - target) != prefixSum.end()) {
            count += prefixSum[sum - target];
        }
        prefixSum[sum]++;
    }
    
    return count;
}
```

### 4. Sliding Window with Heap

```cpp
vector<int> slidingWindowMedian(vector<int>& arr, int k) {
    multiset<int> window;
    vector<int> result;
    
    for (int i = 0; i < arr.size(); i++) {
        window.insert(arr[i]);
        
        if (i >= k - 1) {
            auto it = window.begin();
            advance(it, k / 2);
            result.push_back(*it);
            
            window.erase(window.lower_bound(arr[i - k + 1]));
        }
    }
    
    return result;
}
```

---

## Common Mistakes and Tips

### Common Mistakes

1. **Not resetting pointers correctly**
   - Always reset left pointer when window condition fails
   
2. **Forgetting to update result inside loop**
   - Check condition at every right pointer position
   
3. **Index out of bounds**
   - Check `left <= right` before accessing
   
4. **Not handling edge cases**
   - Empty array, single element, k = 0

### Tips for Success

1. **Use two pointers when:**
   - Array is sorted
   - Finding pairs/triplets
   - Palindrome problems
   - Matching elements from opposite ends

2. **Use sliding window when:**
   - Subarray/substring optimization
   - Minimum/maximum length problems
   - Frequency/character count problems
   - Need to maintain certain condition

3. **Pattern recognition:**
   - "Find subarray with condition" → Sliding window
   - "Find pairs" → Two pointers
   - "Longest/shortest subarray" → Variable window
   - "Fixed size subarray" → Fixed window

---

## Practice Problems

### Easy Level (800-1200)
1. Two Sum (sorted array)
2. Container With Most Water
3. Remove Duplicates
4. Valid Palindrome
5. Reverse String

### Medium Level (1200-1800)
1. Three Sum
2. Trapping Rain Water
3. Minimum Window Substring
4. Longest Substring Without Repeating Characters
5. Sliding Window Maximum

### Hard Level (1800+)
1. Substring with Concatenation
2. Minimum Operations to Reduce X to Zero
3. Maximize Distance to Closest Person
4. Longest Mountain in Array
5. Minimum Window Subsequence

---

## Tips for Competitive Programming

### 1. Time Complexity
- **Two Pointers**: Usually O(n)
- **Sliding Window**: Usually O(n)
- **With sorting**: O(n log n)

### 2. Space Complexity
- Usually O(1) for two pointers
- O(k) for sliding window where k is window size

### 3. When to Use

| Technique | Use When |
|----------|----------|
| Two Pointers (opposite ends) | Sorted array, palindrome, pairs |
| Two Pointers (both forward) | Remove duplicates, cycle detection |
| Fixed Window | Fixed size subarray problems |
| Variable Window | Subarray with condition (min/max length) |

### 4. Optimization Tips

1. **Sort when possible** - Makes two pointers easier
2. **Precompute values** - Avoid recalculation
3. **Use deque** - For maximum/minimum in window
4. **HashMap** - For frequency tracking
5. **Prefix sum** - For subarray sum problems

---

## Conclusion

Master Two Pointers and Sliding Window by:

1. **Understanding fundamentals**: Different pointer types and window types
2. **Learning patterns**: Recogn common problem patterns
3. **Practicing problems**: Start easy, gradually increase difficulty
4. **Optimizing solutions**: Reduce time and space complexity
5. **Handling edge cases**: Empty arrays, single elements, null inputs

Remember: These techniques are about finding patterns. Look for sorted arrays, subarray problems, or window constraints.

Good luck with your competitive programming journey!

