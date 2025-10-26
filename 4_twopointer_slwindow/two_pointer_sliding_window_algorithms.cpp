#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// TWO POINTERS - OPPOSITE ENDS
// ============================================================================

// Two Sum in sorted array
vector<int> twoSum(vector<int>& arr, int target) {
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

// Container with most water
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

// Trapping rain water
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

// Check if array is palindrome
bool isPalindrome(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        if (arr[left] != arr[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Reverse string using two pointers
void reverseString(vector<char>& s) {
    int left = 0;
    int right = s.size() - 1;
    
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

// Valid palindrome string (ignore non-alphanumeric)
bool isPalindromeString(string s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
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

// ============================================================================
// TWO POINTERS - BOTH FORWARD (FAST AND SLOW)
// ============================================================================

// Remove duplicates from sorted array
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

// Remove duplicates (at most 2 duplicates allowed)
int removeDuplicates2(vector<int>& arr) {
    if (arr.size() <= 2) return arr.size();
    
    int writeIndex = 2;
    for (int readIndex = 2; readIndex < arr.size(); readIndex++) {
        if (arr[readIndex] != arr[writeIndex - 2]) {
            arr[writeIndex++] = arr[readIndex];
        }
    }
    return writeIndex;
}

// Remove all occurrences of val
int removeElement(vector<int>& arr, int val) {
    int writeIndex = 0;
    for (int readIndex = 0; readIndex < arr.size(); readIndex++) {
        if (arr[readIndex] != val) {
            arr[writeIndex++] = arr[readIndex];
        }
    }
    return writeIndex;
}

// Move zeros to end
void moveZeros(vector<int>& arr) {
    int nonZeroIndex = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != 0) {
            swap(arr[nonZeroIndex++], arr[i]);
        }
    }
}

// ============================================================================
// THREE POINTERS
// ============================================================================

// Three Sum problem
vector<vector<int>> threeSum(vector<int>& arr) {
    vector<vector<int>> result;
    int n = arr.size();
    sort(arr.begin(), arr.end());
    
    for (int i = 0; i < n - 2; i++) {
        // Skip duplicates
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

// Dutch National Flag (Sort 0s, 1s, 2s)
void sort012(vector<int>& arr) {
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

// Partition array around pivot
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ============================================================================
// SLIDING WINDOW - FIXED SIZE
// ============================================================================

// Maximum sum subarray of size k
int maxSumSubarrayK(vector<int>& arr, int k) {
    int windowSum = 0;
    
    // Calculate sum of first window
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

// Average of subarray of size k
vector<double> averageOfSubarrayK(vector<int>& arr, int k) {
    vector<double> result;
    double windowSum = 0;
    
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    result.push_back(windowSum / k);
    
    for (int i = k; i < arr.size(); i++) {
        windowSum = windowSum - arr[i - k] + arr[i];
        result.push_back(windowSum / k);
    }
    
    return result;
}

// Count of subarrays with exactly k odd numbers
int countSubarraysKOdd(vector<int>& arr, int k) {
    int left = 0;
    int oddCount = 0;
    int result = 0;
    int temp = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        if (arr[right] % 2 == 1) {
            oddCount++;
            temp = 0;
        }
        
        while (oddCount == k) {
            temp++;
            if (arr[left] % 2 == 1) {
                oddCount--;
            }
            left++;
        }
        result += temp;
    }
    
    return result;
}

// ============================================================================
// SLIDING WINDOW - VARIABLE SIZE
// ============================================================================

// Minimum size subarray sum >= target
int minSizeSubarraySum(vector<int>& arr, int target) {
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

// Longest substring without repeating characters
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

// Minimum window substring
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

// Longest substring with at most k distinct characters
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

// ============================================================================
// SLIDING WINDOW WITH DEQUE
// ============================================================================

// Sliding window maximum
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

// Sliding window minimum
vector<int> slidingWindowMin(vector<int>& arr, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < arr.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    
    return result;
}

// ============================================================================
// ADVANCED PATTERNS
// ============================================================================

// Subarray sum equals k (using hashmap)
int subarraySumEqualsK(vector<int>& arr, int k) {
    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0;
    int count = 0;
    
    for (int num : arr) {
        sum += num;
        if (prefixSum.find(sum - k) != prefixSum.end()) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    
    return count;
}

// Maximum points you can obtain
int maxScore(vector<int>& cardPoints, int k) {
    int totalSum = 0;
    for (int point : cardPoints) {
        totalSum += point;
    }
    
    int windowSize = cardPoints.size() - k;
    int windowSum = 0;
    
    for (int i = 0; i < windowSize; i++) {
        windowSum += cardPoints[i];
    }
    
    int minSum = windowSum;
    
    for (int i = windowSize; i < cardPoints.size(); i++) {
        windowSum = windowSum - cardPoints[i - windowSize] + cardPoints[i];
        minSum = min(minSum, windowSum);
    }
    
    return totalSum - minSum;
}

// Maximum consecutive ones III
int longestOnes(vector<int>& arr, int k) {
    int left = 0;
    int maxLen = 0;
    int zeroCount = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        if (arr[right] == 0) {
            zeroCount++;
        }
        
        while (zeroCount > k) {
            if (arr[left] == 0) {
                zeroCount--;
            }
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testTwoPointers() {
    cout << "Testing Two Pointers:" << endl;
    
    vector<int> arr1 = {2, 7, 11, 15};
    auto result = twoSum(arr1, 9);
    cout << "Two Sum [2,7,11,15] target=9: [" << result[0] << "," << result[1] << "]" << endl;
    
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max Area: " << maxArea(height) << endl;
    
    vector<int> arr2 = {0, 1, 1, 1, 1, 2, 2, 3};
    cout << "Remove duplicates: " << removeDuplicates(arr2) << endl;
    
    cout << endl;
}

void testSlidingWindow() {
    cout << "Testing Sliding Window:" << endl;
    
    vector<int> arr = {2, 1, 5, 1, 3, 2};
    cout << "Max Sum Subarray K=3: " << maxSumSubarrayK(arr, 3) << endl;
    
    string s = "abcabcbb";
    cout << "Longest unique substring: " << longestUniqueSubstring(s) << endl;
    
    cout << endl;
}

void testAdvanced() {
    cout << "Testing Advanced:" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    vector<int> windowMax = slidingWindowMax(arr, 3);
    cout << "Sliding window max: ";
    for (int x : windowMax) cout << x << " ";
    cout << endl;
    
    vector<int> arr2 = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    cout << "Longest Ones K=2: " << longestOnes(arr2, 2) << endl;
    
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Two Pointers and Sliding Window Test Suite" << endl;
    cout << "==========================================" << endl << endl;
    
    testTwoPointers();
    testSlidingWindow();
    testAdvanced();
    
    return 0;
}

