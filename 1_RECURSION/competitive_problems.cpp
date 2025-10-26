#include <bits/stdc++.h>
using namespace std;

// ===========================================
// COMPETITIVE PROGRAMMING PROBLEMS
// ===========================================

// Problem 1: Count all possible paths from top-left to bottom-right
// in a matrix with obstacles (0 = obstacle, 1 = path)
class UniquePaths {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return dfs(obstacleGrid, 0, 0, dp);
    }
    
private:
    int dfs(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
        int m = grid.size(), n = grid[0].size();
        
        // Base cases
        if (i >= m || j >= n || grid[i][j] == 1) return 0;
        if (i == m - 1 && j == n - 1) return 1;
        
        // Memoization
        if (dp[i][j] != -1) return dp[i][j];
        
        // Recursive case: go right or down
        dp[i][j] = dfs(grid, i + 1, j, dp) + dfs(grid, i, j + 1, dp);
        return dp[i][j];
    }
};

// Problem 2: Generate all possible combinations of k numbers from 1 to n
class Combinations {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(1, n, k, current, result);
        return result;
    }
    
private:
    void backtrack(int start, int n, int k, vector<int>& current, vector<vector<int>>& result) {
        // Base case: found k numbers
        if (current.size() == k) {
            result.push_back(current);
            return;
        }
        
        // Try each number from start to n
        for (int i = start; i <= n; i++) {
            current.push_back(i);  // Choose
            backtrack(i + 1, n, k, current, result);  // Explore
            current.pop_back();  // Backtrack
        }
    }
};

// Problem 3: Partition a string into palindromes
class PalindromePartitioning {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
private:
    void backtrack(string& s, int start, vector<string>& current, vector<vector<string>>& result) {
        // Base case: processed entire string
        if (start == s.length()) {
            result.push_back(current);
            return;
        }
        
        // Try each possible palindrome starting at start
        for (int i = start; i < s.length(); i++) {
            if (isPalindrome(s, start, i)) {
                current.push_back(s.substr(start, i - start + 1));  // Choose
                backtrack(s, i + 1, current, result);  // Explore
                current.pop_back();  // Backtrack
            }
        }
    }
    
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }
};

// Problem 4: Restore IP addresses
class RestoreIPAddresses {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
private:
    void backtrack(string& s, int start, vector<string>& current, vector<string>& result) {
        // Base case: formed 4 parts and used all digits
        if (current.size() == 4 && start == s.length()) {
            result.push_back(current[0] + "." + current[1] + "." + current[2] + "." + current[3]);
            return;
        }
        
        // Pruning: can't form valid IP
        if (current.size() >= 4 || start >= s.length()) return;
        
        // Try 1, 2, or 3 digits
        for (int len = 1; len <= 3 && start + len <= s.length(); len++) {
            string part = s.substr(start, len);
            
            if (isValidPart(part)) {
                current.push_back(part);  // Choose
                backtrack(s, start + len, current, result);  // Explore
                current.pop_back();  // Backtrack
            }
        }
    }
    
    bool isValidPart(string& part) {
        if (part.empty() || part.length() > 3) return false;
        if (part.length() > 1 && part[0] == '0') return false;
        
        int num = stoi(part);
        return num >= 0 && num <= 255;
    }
};

// Problem 5: Word Break II - Find all possible sentences
class WordBreakII {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<string> result;
        vector<string> current;
        backtrack(s, 0, wordSet, current, result);
        return result;
    }
    
private:
    void backtrack(string& s, int start, unordered_set<string>& wordSet, 
                   vector<string>& current, vector<string>& result) {
        // Base case: processed entire string
        if (start == s.length()) {
            string sentence = "";
            for (int i = 0; i < current.size(); i++) {
                sentence += current[i];
                if (i < current.size() - 1) sentence += " ";
            }
            result.push_back(sentence);
            return;
        }
        
        // Try each possible word starting at start
        for (int i = start; i < s.length(); i++) {
            string word = s.substr(start, i - start + 1);
            if (wordSet.find(word) != wordSet.end()) {
                current.push_back(word);  // Choose
                backtrack(s, i + 1, wordSet, current, result);  // Explore
                current.pop_back();  // Backtrack
            }
        }
    }
};

// Problem 6: Generate all possible valid parentheses with n pairs
class GenerateParentheses {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack("", 0, 0, n, result);
        return result;
    }
    
private:
    void backtrack(string current, int open, int close, int n, vector<string>& result) {
        // Base case: generated valid parentheses
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }
        
        // Add opening parenthesis if possible
        if (open < n) {
            backtrack(current + "(", open + 1, close, n, result);
        }
        
        // Add closing parenthesis if valid
        if (close < open) {
            backtrack(current + ")", open, close + 1, n, result);
        }
    }
};

// Problem 7: Letter Case Permutation
class LetterCasePermutation {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> result;
        backtrack(s, 0, result);
        return result;
    }
    
private:
    void backtrack(string& s, int index, vector<string>& result) {
        // Base case: processed all characters
        if (index == s.length()) {
            result.push_back(s);
            return;
        }
        
        // If current character is a letter, try both cases
        if (isalpha(s[index])) {
            s[index] = tolower(s[index]);  // Choose lowercase
            backtrack(s, index + 1, result);  // Explore
            
            s[index] = toupper(s[index]);  // Choose uppercase
            backtrack(s, index + 1, result);  // Explore
            
            s[index] = tolower(s[index]);  // Backtrack
        } else {
            // Non-letter character, just move to next
            backtrack(s, index + 1, result);
        }
    }
};

// Problem 8: Subsets with duplicates
class SubsetsWithDup {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<int>& current, vector<vector<int>>& result) {
        result.push_back(current);
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates
            if (i > start && nums[i] == nums[i - 1]) continue;
            
            current.push_back(nums[i]);  // Choose
            backtrack(nums, i + 1, current, result);  // Explore
            current.pop_back();  // Backtrack
        }
    }
};

// ===========================================
// OPTIMIZATION TECHNIQUES
// ===========================================

// Memoization example: Fibonacci with DP
class FibonacciDP {
public:
    long long fibonacci(int n) {
        vector<long long> dp(n + 1, -1);
        return memoizedFib(n, dp);
    }
    
private:
    long long memoizedFib(int n, vector<long long>& dp) {
        if (n <= 1) return n;
        if (dp[n] != -1) return dp[n];
        
        dp[n] = memoizedFib(n - 1, dp) + memoizedFib(n - 2, dp);
        return dp[n];
    }
};

// Pruning example: Early termination in backtracking
class PruningExample {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;  // Early pruning
        
        sort(nums.rbegin(), nums.rend());  // Sort descending for better pruning
        return backtrack(nums, 0, sum / 2);
    }
    
private:
    bool backtrack(vector<int>& nums, int index, int target) {
        if (target == 0) return true;
        if (index >= nums.size() || target < 0) return false;
        
        // Pruning: if current number is greater than target, skip
        if (nums[index] > target) return false;
        
        // Try including current number
        if (backtrack(nums, index + 1, target - nums[index])) return true;
        
        // Try excluding current number
        return backtrack(nums, index + 1, target);
    }
};

// ===========================================
// TESTING FUNCTIONS
// ===========================================

int main() {
    cout << "=== Competitive Programming Problems ===\n\n";
    
    // Test combinations
    Combinations comb;
    auto result = comb.combine(4, 2);
    cout << "Combinations of 4 choose 2:\n";
    for (auto& c : result) {
        cout << "[";
        for (int i = 0; i < c.size(); i++) {
            cout << c[i];
            if (i < c.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";
    
    // Test palindrome partitioning
    PalindromePartitioning pp;
    auto partitions = pp.partition("aab");
    cout << "Palindrome partitions of 'aab':\n";
    for (auto& partition : partitions) {
        cout << "[";
        for (int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if (i < partition.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";
    
    // Test letter case permutation
    LetterCasePermutation lcp;
    auto permutations = lcp.letterCasePermutation("a1b2");
    cout << "Letter case permutations of 'a1b2':\n";
    for (auto& perm : permutations) {
        cout << "\"" << perm << "\" ";
    }
    cout << "\n\n";
    
    // Test Fibonacci with DP
    FibonacciDP fib;
    cout << "Fibonacci(20) with DP: " << fib.fibonacci(20) << "\n";
    
    return 0;
}
