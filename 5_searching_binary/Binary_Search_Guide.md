# Binary Search in C++ for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Basic Binary Search](#basic-binary-search)
3. [Variations of Binary Search](#variations-of-binary-search)
4. [Search in Rotated Arrays](#search-in-rotated-arrays)
5. [Search in 2D Arrays](#search-in-2d-arrays)
6. [Advanced Techniques](#advanced-techniques)
7. [Practice Problems](#practice-problems)
8. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Binary search is an efficient algorithm for finding an item in a sorted array. It reduces the search space by half at each step, making it incredibly fast with O(log n) time complexity.

### What You'll Learn:
- Basic binary search on sorted arrays
- Finding first/last occurrence
- Binary search on answer (predicate function)
- Search in rotated and sorted arrays
- Search in 2D matrices
- Advanced patterns and optimizations

---

## Basic Binary Search

### Standard Binary Search

```cpp
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;  // Not found
}
```

### Key Points
- **Sorted array required**: Binary search only works on sorted data
- **O(log n) time**: Much faster than linear search
- **Loop invariant**: `arr[left..right]` contains target

### Prevent Integer Overflow
```cpp
int mid = left + (right - left) / 2;
// Instead of: int mid = (left + right) / 2;
```

---

## Variations of Binary Search

### 1. Find First Occurrence

```cpp
int firstOccurrence(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching left
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}
```

### 2. Find Last Occurrence

```cpp
int lastOccurrence(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching right
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}
```

### 3. Find Insertion Position

```cpp
int findInsertionPosition(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;  // Insertion position
}
```

### 4. Count Occurrences

```cpp
int countOccurrences(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return 0;
    int last = lastOccurrence(arr, target);
    return last - first + 1;
}
```

---

## Search in Rotated Arrays

### Search in Rotated Sorted Array

```cpp
int searchRotated(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        // Left half is sorted
        if (arr[left] <= arr[mid]) {
            if (target >= arr[left] && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } 
        // Right half is sorted
        else {
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

### Find Minimum in Rotated Array

```cpp
int findMinRotated(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[right]) {
            // Right half is sorted, minimum is in left half
            right = mid;
        } else {
            // Left half is sorted, minimum is in right half
            left = mid + 1;
        }
    }
    return arr[left];
}
```

### Find Rotation Count

```cpp
int findRotationCount(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[right]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
```

---

## Search in 2D Arrays

### Search in Sorted Matrix

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row = 0;
    int col = matrix[0].size() - 1;
    
    while (row < matrix.size() && col >= 0) {
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] > target) {
            col--;  // Move left
        } else {
            row++;  // Move down
        }
    }
    return false;
}
```

### Search in Strictly Sorted Matrix

```cpp
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Binary search on rows
    int top = 0, bottom = rows - 1;
    while (top <= bottom) {
        int midRow = top + (bottom - top) / 2;
        
        if (matrix[midRow][0] <= target && 
            target <= matrix[midRow][cols - 1]) {
            // Binary search in this row
            int left = 0, right = cols - 1;
            while (left <= right) {
                int midCol = left + (right - left) / 2;
                if (matrix[midRow][midCol] == target) {
                    return true;
                } else if (matrix[midRow][midCol] < target) {
                    left = midCol + 1;
                } else {
                    right = midCol - 1;
                }
            }
            return false;
        } else if (matrix[midRow][0] > target) {
            bottom = midRow - 1;
        } else {
            top = midRow + 1;
        }
    }
    return false;
}
```

---

## Binary Search on Answer

### Concept

Binary search on answer is a powerful technique where:
- The answer lies in a searchable range [low, high]
- There's a predicate function that determines if a value is valid
- We binary search on the answer itself

### Example: Koko Eating Bananas

```cpp
int minEatingSpeed(vector<int>& piles, int h) {
    int left = 1;
    int right = *max_element(piles.begin(), piles.end());
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Predicate: Can she finish in h hours with speed mid?
        if (canFinish(piles, mid, h)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

bool canFinish(vector<int>& piles, int speed, int hours) {
    int totalHours = 0;
    for (int pile : piles) {
        totalHours += (pile + speed - 1) / speed;
    }
    return totalHours <= hours;
}
```

### Example: Square Root

```cpp
int mySqrt(int x) {
    if (x < 2) return x;
    
    int left = 2;
    int right = x / 2;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long num = (long) mid * mid;
        
        if (num == x) {
            return mid;
        } else if (num > x) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return right;
}
```

### Example: Split Array Largest Sum

```cpp
int splitArray(vector<int>& nums, int m) {
    int left = *max_element(nums.begin(), nums.end());
    int right = accumulate(nums.begin(), nums.end(), 0);
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Predicate: Can we split into m parts with max sum <= mid?
        if (canSplit(nums, mid, m)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

bool canSplit(vector<int>& nums, int maxSum, int m) {
    int count = 1;
    int sum = 0;
    
    for (int num : nums) {
        sum += num;
        if (sum > maxSum) {
            count++;
            sum = num;
            if (count > m) return false;
        }
    }
    return true;
}
```

---

## Advanced Techniques

### 1. Bitonic Search (Peak Finding)

```cpp
int findPeak(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[mid + 1]) {
            // Peak is in right half
            left = mid + 1;
        } else {
            // Peak is in left half
            right = mid;
        }
    }
    return left;
}
```

### 2. Infinite Array Search

```cpp
int searchInfinite(vector<int>& arr, int target) {
    int left = 0;
    int right = 1;
    
    // Find bounds
    while (arr[right] < target) {
        left = right;
        right *= 2;
    }
    
    // Normal binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
```

### 3. Nearly Sorted Array Search

```cpp
int searchNearlySorted(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        // Check adjacent elements
        if (mid > left && arr[mid - 1] == target) {
            return mid - 1;
        }
        if (mid < right && arr[mid + 1] == target) {
            return mid + 1;
        }
        
        if (arr[mid] < target) {
            left = mid + 2;
        } else {
            right = mid - 2;
        }
    }
    return -1;
}
```

### 4. Search in Descending Sorted Array

```cpp
int searchDescending(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            // Target is in right half
            right = mid - 1;
        } else {
            // Target is in left half
            left = mid + 1;
        }
    }
    return -1;
}
```

### 5. Exponential Search

```cpp
int exponentialSearch(vector<int>& arr, int target) {
    int n = arr.size();
    
    if (arr[0] == target) return 0;
    
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }
    
    // Binary search in the found range
    int left = i / 2;
    int right = min(i, n - 1);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
```

---

## Common Patterns

### Pattern 1: Find Boundary

```cpp
int findBoundary(vector<bool>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    int boundary = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid]) {
            boundary = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return boundary;
}
```

### Pattern 2: Search in Range

```cpp
vector<int> searchRange(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return {-1, -1};
    int last = lastOccurrence(arr, target);
    return {first, last};
}
```

### Pattern 3: Find Upper/Lower Bound

```cpp
int lowerBound(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int upperBound(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}
```

---

## Practice Problems

### Easy Level (800-1200)
1. Binary Search
2. First Bad Version
3. Search Insert Position
4. Sqrt(x)
5. Valid Perfect Square

### Medium Level (1200-1800)
1. Search in Rotated Sorted Array
2. Find First and Last Position
3. Search in 2D Matrix
4. Koko Eating Bananas
5. Minimum in Rotated Sorted Array

### Hard Level (1800+)
1. Split Array Largest Sum
2. Median of Two Sorted Arrays
3. Divide Chocolate
4. Capacity To Ship Packages
5. Kth Smallest in Multiplication Table

---

## Tips for Competitive Programming

### 1. Time Complexity
- **Standard binary search**: O(log n)
- **Binary search on answer**: O(log range)
- **With predicate**: O(log range × cost of predicate)

### 2. When to Use
- **Sorted data**: Always prefer binary search for sorted arrays
- **Optimization problems**: Binary search on answer
- **Range queries**: Search for first/last occurrence
- **Predicate checking**: Monotonic properties

### 3. Common Mistakes
- Integer overflow (use left + (right - left) / 2)
- Wrong comparison operators
- Incorrect boundaries
- Infinite loops (forgetting to update left/right)

### 4. Debugging Tips
```cpp
// Add debug prints
int mid = left + (right - left) / 2;
cout << "left: " << left << ", right: " << right << ", mid: " << mid << endl;
```

### 5. Optimization Tips
- Use `lower_bound()` and `upper_bound()` from STL
- Precompute bounds when possible
- Avoid redundant calculations in predicate

---

## Conclusion

Master Binary Search by:

1. **Understanding the basics**: Sorted array search with O(log n)
2. **Learning variations**: First/last occurrence, insertion position
3. **Handling rotated arrays**: Identify sorted half
4. **Binary search on answer**: For optimization problems
5. **Practicing problems**: Start easy, move to hard

Remember: Binary search is about eliminating half the search space at each step. Look for sorted data and monotonic properties!

Good luck with your competitive programming journey!

