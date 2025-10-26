# Two Pointers & Sliding Window Quick Reference

## Quick Tips & Patterns

### Two Pointers - Opposite Ends
```cpp
// Find pairs in sorted array
int left = 0, right = n - 1;
while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == target) return {left, right};
    else if (sum < target) left++;
    else right--;
}
```

### Two Pointers - Both Forward (Fast & Slow)
```cpp
// Remove duplicates
int slow = 0;
for (int fast = 1; fast < n; fast++) {
    if (arr[fast] != arr[slow]) {
        arr[++slow] = arr[fast];
    }
}
return slow + 1;
```

### Fixed Size Sliding Window
```cpp
// Max sum of size k
int windowSum = 0;
for (int i = 0; i < k; i++) windowSum += arr[i];

int maxSum = windowSum;
for (int i = k; i < n; i++) {
    windowSum = windowSum - arr[i-k] + arr[i];
    maxSum = max(maxSum, windowSum);
}
return maxSum;
```

### Variable Size Sliding Window
```cpp
// Minimum size with sum >= target
int left = 0, minLen = INT_MAX, sum = 0;
for (int right = 0; right < n; right++) {
    sum += arr[right];
    while (sum >= target) {
        minLen = min(minLen, right - left + 1);
        sum -= arr[left++];
    }
}
return minLen == INT_MAX ? 0 : minLen;
```

### Sliding Window with Deque (Max in Window)
```cpp
// Maximum in each window of size k
deque<int> dq;
vector<int> result;

for (int i = 0; i < n; i++) {
    // Remove out of window
    while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    
    // Remove smaller elements
    while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
    
    dq.push_back(i);
    if (i >= k - 1) result.push_back(arr[dq.front()]);
}
return result;
```

## Common Patterns

### Pattern 1: Longest Substring Without Repeating
```cpp
unordered_map<char, int> map;
int left = 0, maxLen = 0;

for (int right = 0; right < s.length(); right++) {
    if (map.find(s[right]) != map.end()) {
        left = max(left, map[s[right]] + 1);
    }
    map[s[right]] = right;
    maxLen = max(maxLen, right - left + 1);
}
```

### Pattern 2: Subarray with At Most K Distinct
```cpp
unordered_map<int, int> count;
int left = 0, result = 0;

for (int right = 0; right < n; right++) {
    count[arr[right]]++;
    
    while (count.size() > k) {
        count[arr[left]]--;
        if (count[arr[left]] == 0) count.erase(arr[left]);
        left++;
    }
    
    result += right - left + 1;
}
```

### Pattern 3: Three Sum
```cpp
sort(arr.begin(), arr.end());

for (int i = 0; i < n - 2; i++) {
    if (i > 0 && arr[i] == arr[i-1]) continue;
    
    int left = i + 1, right = n - 1;
    while (left < right) {
        int sum = arr[i] + arr[left] + arr[right];
        if (sum == 0) {
            result.push_back({arr[i], arr[left], arr[right]});
            while (left < right && arr[left] == arr[left+1]) left++;
            while (left < right && arr[right] == arr[right-1]) right--;
            left++; right--;
        } else if (sum < 0) left++;
        else right--;
    }
}
```

## Quick Tricks

### When to Use Which?

| Technique | Use When |
|-----------|----------|
| Two Pointers (ends) | Sorted array, palindrome, pairs |
| Two Pointers (forward) | Remove duplicates, partition |
| Fixed Window | Fixed size subarray (k elements) |
| Variable Window | Min/max length subarray |
| Deque Window | Need min/max in window |

### Time Complexity
- Two Pointers: O(n)
- Sliding Window: O(n)
- With sorting: O(n log n)

### Common Mistakes
1. Not updating pointers correctly
2. Forgetting to check window condition
3. Index out of bounds
4. Not handling empty arrays

## See Also
- [Two_Pointer_Sliding_Window_Guide.md](Two_Pointer_Sliding_Window_Guide.md) - Complete guide
- [two_pointer_sliding_window_algorithms.cpp](two_pointer_sliding_window_algorithms.cpp) - Code implementations
- [practice_problems_list.md](practice_problems_list.md) - Problem lists

