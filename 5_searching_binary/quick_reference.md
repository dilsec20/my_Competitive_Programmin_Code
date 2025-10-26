# Binary Search Quick Reference

## Quick Templates

### Basic Binary Search
```cpp
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Prevent overflow
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

### Find First Occurrence
```cpp
int firstOccurrence(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Search left
        } else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}
```

### Find Last Occurrence
```cpp
int lastOccurrence(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Search right
        } else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}
```

### Lower Bound (First position where value >= target)
```cpp
int lowerBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}
```

### Upper Bound (First position where value > target)
```cpp
int upperBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) left = mid + 1;
        else right = mid;
    }
    return left;
}
```

## Advanced Patterns

### Search in Rotated Sorted Array
```cpp
int searchRotated(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return mid;
        
        if (arr[left] <= arr[mid]) {  // Left half sorted
            if (target >= arr[left] && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {  // Right half sorted
            if (target > arr[mid] && target <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}
```

### Binary Search on Answer
```cpp
int binarySearchOnAnswer(vector<int>& nums, int target) {
    int left = getMin(nums);
    int right = getMax(nums);
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (isValid(mid, target)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

bool isValid(int mid, int target) {
    // Your predicate function here
    return /* condition */;
}
```

### Find Minimum in Rotated Array
```cpp
int findMin(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[right]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return arr[left];
}
```

### Find Peak Element
```cpp
int findPeak(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}
```

### Square Root (Binary Search)
```cpp
int mySqrt(int x) {
    if (x < 2) return x;
    int left = 2, right = x / 2;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long num = (long) mid * mid;
        
        if (num == x) return mid;
        else if (num > x) right = mid - 1;
        else left = mid + 1;
    }
    return right;
}
```

## STL Functions

### Using Standard Library
```cpp
// Lower bound (first position >= target)
auto it = lower_bound(arr.begin(), arr.end(), target);
int index = it - arr.begin();

// Upper bound (first position > target)
auto it = upper_bound(arr.begin(), arr.end(), target);
int index = it - arr.begin();

// Binary search (returns true/false)
bool found = binary_search(arr.begin(), arr.end(), target);
```

## Quick Tips

### When to Use Which?
| Pattern | Use When |
|---------|----------|
| Standard BS | Find exact match in sorted array |
| First Occurrence | Need first position of target |
| Last Occurrence | Need last position of target |
| Lower Bound | Insertion position, count elements |
| Upper Bound | Upper limit, range count |
| BS on Answer | Optimization problems with monotonic property |

### Loop Variations
```cpp
// Type 1: Exact match (left <= right)
while (left <= right) {
    // Can return from inside loop
}

// Type 2: Range search (left < right)
while (left < right) {
    // Returns after loop ends
}
```

### Prevent Integer Overflow
```cpp
// Correct: Use left + (right - left) / 2
int mid = left + (right - left) / 2;

// Wrong: May overflow
int mid = (left + right) / 2;
```

### Common Mistakes
1. ❌ Forgetting to update left/right
2. ❌ Using wrong comparison operators
3. ❌ Integer overflow with (left + right) / 2
4. ❌ Infinite loops (same mid repeatedly)
5. ❌ Wrong boundaries (inclusive vs exclusive)

## Time Complexity
- **Basic search**: O(log n)
- **Multiple passes**: O(log n × passes)
- **With predicate**: O(log range × predicate_cost)

## See Also
- [Binary_Search_Guide.md](Binary_Search_Guide.md) - Complete guide
- [binary_search_algorithms.cpp](binary_search_algorithms.cpp) - Code implementations
- [practice_problems_list.md](practice_problems_list.md) - Problem lists

