#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BASIC BINARY SEARCH
// ============================================================================

// Standard binary search
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Prevent overflow
        
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

// Binary search - lower bound (first position where value >= target)
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

// Binary search - upper bound (first position where value > target)
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

// Find insertion position
int findInsertionPos(vector<int>& arr, int target) {
    return lowerBound(arr, target);
}

// ============================================================================
// FIND FIRST AND LAST OCCURRENCE
// ============================================================================

// Find first occurrence
int firstOccurrence(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching in left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Find last occurrence
int lastOccurrence(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching in right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Count occurrences
int countOccurrences(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return 0;
    int last = lastOccurrence(arr, target);
    return last - first + 1;
}

// Find range [first, last] occurrence
vector<int> searchRange(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return {-1, -1};
    int last = lastOccurrence(arr, target);
    return {first, last};
}

// ============================================================================
// SEARCH IN ROTATED ARRAYS
// ============================================================================

// Search in rotated sorted array
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

// Find minimum in rotated array
int findMinRotated(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[right]) {
            right = mid;  // Minimum is in left half
        } else {
            left = mid + 1;  // Minimum is in right half
        }
    }
    return arr[left];
}

// Find rotation count
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

// Search with duplicates (handle edge case)
int searchRotatedWithDuplicates(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        // Handle duplicates
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;
            right--;
            continue;
        }
        
        // Left half is sorted
        if (arr[left] <= arr[mid]) {
            if (target >= arr[left] && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (target > arr[mid] && target <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

// ============================================================================
// SEARCH IN 2D MATRICES
// ============================================================================

// Search in sorted matrix (each row sorted, first element of row > last element of previous row)
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Binary search on which row
    int top = 0, bottom = rows - 1;
    while (top <= bottom) {
        int midRow = top + (bottom - top) / 2;
        
        if (target >= matrix[midRow][0] && target <= matrix[midRow][cols - 1]) {
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
        } else if (target < matrix[midRow][0]) {
            bottom = midRow - 1;
        } else {
            top = midRow + 1;
        }
    }
    return false;
}

// Search in matrix where each row and column is sorted
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
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

// Find kth smallest in multiplication table
int findKthNumber(int m, int n, int k) {
    int left = 1;
    int right = m * n;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        
        for (int i = 1; i <= m; i++) {
            count += min(n, mid / i);
        }
        
        if (count >= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// ============================================================================
// BINARY SEARCH ON ANSWER
// ============================================================================

// Square root using binary search
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

// Koko eating bananas
bool canFinish(vector<int>& piles, int speed, int hours) {
    int totalHours = 0;
    for (int pile : piles) {
        totalHours += (pile + speed - 1) / speed;  // Ceiling division
    }
    return totalHours <= hours;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int left = 1;
    int right = *max_element(piles.begin(), piles.end());
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canFinish(piles, mid, h)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// Split array largest sum
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

int splitArray(vector<int>& nums, int m) {
    int left = *max_element(nums.begin(), nums.end());
    int right = accumulate(nums.begin(), nums.end(), 0);
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canSplit(nums, mid, m)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// Capacity to ship packages
bool canShip(vector<int>& weights, int capacity, int days) {
    int currentLoad = 0;
    int daysUsed = 1;
    
    for (int weight : weights) {
        if (currentLoad + weight > capacity) {
            daysUsed++;
            currentLoad = weight;
            if (daysUsed > days) return false;
        } else {
            currentLoad += weight;
        }
    }
    return true;
}

int shipWithinDays(vector<int>& weights, int days) {
    int left = *max_element(weights.begin(), weights.end());
    int right = accumulate(weights.begin(), weights.end(), 0);
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canShip(weights, mid, days)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// Divide chocolate
bool canDivide(vector<int>& sweetness, int minSweetness, int k) {
    int pieces = 0;
    int currentSweetness = 0;
    
    for (int s : sweetness) {
        currentSweetness += s;
        if (currentSweetness >= minSweetness) {
            pieces++;
            currentSweetness = 0;
        }
    }
    return pieces >= k + 1;
}

int maximizeSweetness(vector<int>& sweetness, int k) {
    int left = *min_element(sweetness.begin(), sweetness.end());
    int right = accumulate(sweetness.begin(), sweetness.end(), 0) / (k + 1);
    
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        
        if (canDivide(sweetness, mid, k)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

// ============================================================================
// ADVANCED PATTERNS
// ============================================================================

// Find peak element
int findPeak(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
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

// Search in infinite array (simulated)
int searchInfinite(vector<int>& arr, int target) {
    int left = 0;
    int right = 1;
    
    // Find bounds first
    while (arr[right] < target) {
        left = right;
        right *= 2;
        if (right >= arr.size()) {
            right = arr.size() - 1;
            break;
        }
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

// Exponential search
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

// ============================================================================
// VALIDATE PERFECT SQUARE
// ============================================================================

bool isPerfectSquare(int num) {
    if (num < 2) return true;
    
    int left = 2;
    int right = num / 2;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long square = (long long) mid * mid;
        
        if (square == num) {
            return true;
        } else if (square > num) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return false;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testBasicSearch() {
    cout << "Testing Basic Binary Search:" << endl;
    
    vector<int> arr = {2, 3, 4, 10, 40};
    int target = 10;
    int result = binarySearch(arr, target);
    cout << "Search for " << target << " in [2,3,4,10,40]: " << result << endl;
    
    cout << "Lower bound of 5 in [2,3,4,10,40]: " << lowerBound(arr, 5) << endl;
    cout << "Upper bound of 5 in [2,3,4,10,40]: " << upperBound(arr, 5) << endl;
    
    cout << endl;
}

void testFirstLast() {
    cout << "Testing First/Last Occurrence:" << endl;
    
    vector<int> arr = {1, 2, 2, 2, 3, 4, 4, 4, 5};
    int target = 2;
    
    cout << "First occurrence of 2: " << firstOccurrence(arr, target) << endl;
    cout << "Last occurrence of 2: " << lastOccurrence(arr, target) << endl;
    cout << "Count of 2: " << countOccurrences(arr, target) << endl;
    
    vector<int> range = searchRange(arr, 4);
    cout << "Range of 4: [" << range[0] << "," << range[1] << "]" << endl;
    
    cout << endl;
}

void testRotatedSearch() {
    cout << "Testing Rotated Array Search:" << endl;
    
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    cout << "Search for " << target << " in rotated array: " << searchRotated(arr, target) << endl;
    
    vector<int> arr2 = {3, 4, 5, 1, 2};
    cout << "Min element in rotated array: " << findMinRotated(arr2) << endl;
    cout << "Rotation count: " << findRotationCount(arr2) << endl;
    
    cout << endl;
}

void testBinarySearchOnAnswer() {
    cout << "Testing Binary Search on Answer:" << endl;
    
    int x = 16;
    cout << "Square root of " << x << ": " << mySqrt(x) << endl;
    
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    cout << "Min eating speed for " << h << " hours: " << minEatingSpeed(piles, h) << endl;
    
    vector<int> nums = {7, 2, 5, 10, 8};
    int m = 2;
    cout << "Min largest sum with " << m << " splits: " << splitArray(nums, m) << endl;
    
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Binary Search Algorithms Test Suite" << endl;
    cout << "===================================" << endl << endl;
    
    testBasicSearch();
    testFirstLast();
    testRotatedSearch();
    testBinarySearchOnAnswer();
    
    return 0;
}

