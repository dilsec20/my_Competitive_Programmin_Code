# Recursion & Backtracking in C++ for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Recursion Fundamentals](#recursion-fundamentals)
3. [Advanced Recursion Patterns](#advanced-recursion-patterns)
4. [Backtracking Concepts](#backtracking-concepts)
5. [Classic Backtracking Problems](#classic-backtracking-problems)
6. [Competitive Programming Problems](#competitive-programming-problems)
7. [Optimization Techniques](#optimization-techniques)
8. [Practice Problems](#practice-problems)
9. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

Recursion and backtracking are fundamental concepts in competitive programming. This guide provides a comprehensive approach to mastering these techniques with practical examples and competitive programming problems.

### What You'll Learn:
- Core recursion concepts and patterns
- Backtracking algorithms and templates
- Optimization techniques (memoization, pruning)
- Competitive programming problem-solving strategies
- Time and space complexity analysis

---

## Recursion Fundamentals

### Basic Recursion Template
```cpp
returnType function(parameters) {
    // Base case
    if (base_condition) {
        return base_value;
    }
    
    // Recursive case
    return combine(
        function(modified_parameters),
        current_work
    );
}
```

### Key Concepts:
1. **Base Case**: The stopping condition that prevents infinite recursion
2. **Recursive Case**: The part that calls the function with modified parameters
3. **Call Stack**: Understanding how recursive calls are managed in memory

### Example: Factorial
```cpp
int factorial(int n) {
    if (n == 0) return 1;  // Base case
    return n * factorial(n - 1);  // Recursive case
}
```

### Example: Fibonacci
```cpp
int fibonacci(int n) {
    if (n <= 1) return n;  // Base cases
    return fibonacci(n - 1) + fibonacci(n - 2);  // Recursive case
}
```

### Example: Digit Sum
```cpp
int digitSum(int n) {
    if (n == 0) return 0;  // Base case
    return (n % 10) + digitSum(n / 10);  // Recursive case
}
```

---

## Advanced Recursion Patterns

### 1. Tree Traversal (DFS)
```cpp
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";  // Process root
    preorder(root->left);       // Visit left
    preorder(root->right);      // Visit right
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);        // Visit left
    cout << root->val << " ";  // Process root
    inorder(root->right);       // Visit right
}

void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);      // Visit left
    postorder(root->right);     // Visit right
    cout << root->val << " ";  // Process root
}
```

### 2. Divide & Conquer
```cpp
int binarySearch(vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;  // Base case: not found
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) return mid;  // Base case: found
    
    // Recursive cases
    if (arr[mid] > target) {
        return binarySearch(arr, target, left, mid - 1);
    } else {
        return binarySearch(arr, target, mid + 1, right);
    }
}
```

### 3. Memoization
```cpp
unordered_map<int, long long> memo;

long long fibonacciMemo(int n) {
    if (n <= 1) return n;  // Base cases
    
    if (memo.find(n) != memo.end()) {
        return memo[n];  // Return cached result
    }
    
    memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
    return memo[n];
}
```

### 4. Multiple Recursive Calls
```cpp
int countPaths(int m, int n) {
    // Base case: reached destination
    if (m == 1 || n == 1) return 1;
    
    // Recursive case: sum of paths from top and left
    return countPaths(m - 1, n) + countPaths(m, n - 1);
}
```

---

## Backtracking Concepts

### What is Backtracking?
Backtracking is a systematic way to explore all possible solutions by building solutions incrementally and abandoning partial solutions that cannot lead to a complete solution.

### Backtracking Template
```cpp
void backtrack(current_state) {
    // Base case: found a solution
    if (is_solution(current_state)) {
        process_solution(current_state);
        return;
    }
    
    // Try all possible choices
    for (each possible choice) {
        if (is_valid(choice)) {
            make_choice(choice);           // Choose
            backtrack(updated_state);      // Explore
            undo_choice(choice);           // Unchoose (Backtrack!)
        }
    }
}
```

### Key Components:
1. **Choose**: Make a choice
2. **Explore**: Recurse with the choice
3. **Unchoose**: Undo the choice (backtrack)

---

## Classic Backtracking Problems

### 1. N-Queens Problem
```cpp
class NQueens {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        solve(board, 0, solutions);
        return solutions;
    }
    
private:
    void solve(vector<string>& board, int row, vector<vector<string>>& solutions) {
        int n = board.size();
        
        // Base case: placed all queens
        if (row == n) {
            solutions.push_back(board);
            return;
        }
        
        // Try placing queen in each column of current row
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col)) {
                board[row][col] = 'Q';  // Make choice
                solve(board, row + 1, solutions);  // Explore
                board[row][col] = '.';  // Backtrack
            }
        }
    }
    
    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();
        
        // Check column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }
        
        // Check diagonals
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        
        return true;
    }
};
```

### 2. Generate All Subsets
```cpp
class Subsets {
public:
    vector<vector<int>> generateSubsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<int>& current, vector<vector<int>>& result) {
        // Every subset is valid, so we add it
        result.push_back(current);
        
        // Try adding each remaining element
        for (int i = start; i < nums.size(); i++) {
            current.push_back(nums[i]);  // Choose
            backtrack(nums, i + 1, current, result);  // Explore
            current.pop_back();  // Backtrack
        }
    }
};
```

### 3. Generate All Permutations
```cpp
class Permutations {
public:
    vector<vector<int>> generatePermutations(vector<int>& nums) {
        vector<vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& result) {
        // Base case: generated a complete permutation
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        // Try each element at current position
        for (int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);  // Choose
            backtrack(nums, start + 1, result);  // Explore
            swap(nums[start], nums[i]);  // Backtrack
        }
    }
};
```

### 4. Sudoku Solver
```cpp
class SudokuSolver {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
    
private:
    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;  // Choose
                            if (solve(board)) return true;  // Explore
                            board[i][j] = '.';  // Backtrack
                        }
                    }
                    return false;  // No valid number found
                }
            }
        }
        return true;  // All cells filled
    }
    
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // Check row
            if (board[row][i] == c) return false;
            // Check column
            if (board[i][col] == c) return false;
            // Check 3x3 box
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }
};
```

---

## Competitive Programming Problems

### 1. Unique Paths with Obstacles
```cpp
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
```

### 2. Generate Combinations (n choose k)
```cpp
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
```

### 3. Palindrome Partitioning
```cpp
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
```

### 4. Word Search
```cpp
class WordSearch {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    bool backtrack(vector<vector<char>>& board, string& word, int i, int j, int index) {
        // Base case: found the word
        if (index == word.length()) return true;
        
        // Boundary check
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return false;
        
        // Character mismatch
        if (board[i][j] != word[index]) return false;
        
        char temp = board[i][j];
        board[i][j] = '#';  // Mark as visited
        
        // Try all 4 directions
        bool found = backtrack(board, word, i + 1, j, index + 1) ||
                     backtrack(board, word, i - 1, j, index + 1) ||
                     backtrack(board, word, i, j + 1, index + 1) ||
                     backtrack(board, word, i, j - 1, index + 1);
        
        board[i][j] = temp;  // Backtrack
        return found;
    }
};
```

---

## Optimization Techniques

### 1. Memoization
```cpp
// Fibonacci with memoization
unordered_map<int, long long> memo;

long long fibonacciMemo(int n) {
    if (n <= 1) return n;
    if (memo.find(n) != memo.end()) return memo[n];
    
    memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
    return memo[n];
}
```

### 2. Pruning
```cpp
// Early termination in backtracking
bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;  // Early pruning
    
    sort(nums.rbegin(), nums.rend());  // Sort descending for better pruning
    return backtrack(nums, 0, sum / 2);
}

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
```

### 3. DP Transitions
```cpp
// Convert recursion to iterative DP
int climbStairsDP(int n) {
    if (n <= 2) return n;
    
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}
```

---

## Practice Problems

### Easy Level:
1. Print all permutations of a string
2. Count ways to reach nth stair
3. Generate all subsets of an array
4. Find all paths in a binary tree
5. Generate all valid parentheses

### Medium Level:
1. N-Queens problem
2. Sudoku solver
3. Word search in 2D grid
4. Combination sum
5. Palindrome partitioning

### Hard Level:
1. Word break II
2. Letter case permutation
3. Subsets with duplicates
4. Rat in a maze
5. Generate all permutations with duplicates

### Sample Solutions:

#### Print Permutations
```cpp
void printPermutations(string str, int left, int right) {
    if (left == right) {
        cout << str << " ";
        return;
    }
    
    for (int i = left; i <= right; i++) {
        swap(str[left], str[i]);
        printPermutations(str, left + 1, right);
        swap(str[left], str[i]);  // Backtrack
    }
}
```

#### Count Stairs
```cpp
int countStairs(int n) {
    if (n <= 1) return 1;
    return countStairs(n - 1) + countStairs(n - 2);
}
```

#### Generate Subsets
```cpp
void generateSubsets(vector<int>& nums, vector<int>& current, int index, vector<vector<int>>& result) {
    result.push_back(current);
    
    for (int i = index; i < nums.size(); i++) {
        current.push_back(nums[i]);
        generateSubsets(nums, current, i + 1, result);
        current.pop_back();
    }
}
```

---

## Tips for Competitive Programming

### 1. Time Complexity Analysis
- **Recursion**: O(branches^depth) where branches = number of choices at each step
- **Backtracking**: O(2^n) for subsets, O(n!) for permutations
- **Memoization**: Reduces exponential time to polynomial

### 2. Space Complexity
- **Recursion**: O(depth) for call stack
- **Backtracking**: O(depth) for recursion + O(n) for current solution
- **Memoization**: O(n) for cache storage

### 3. Common Patterns
- **Generate all**: Use backtracking
- **Count ways**: Use recursion with memoization
- **Find one solution**: Use backtracking with early return
- **Optimization**: Use DP instead of pure recursion

### 4. Debugging Tips
- Draw recursion trees for complex problems
- Use print statements to trace execution
- Check base cases carefully
- Verify backtracking (undo operations)

### 5. Performance Optimization
- Use memoization for overlapping subproblems
- Apply pruning to reduce search space
- Consider iterative solutions for better space efficiency
- Use bit manipulation for subset problems

### 6. Common Mistakes
- Forgetting base cases
- Not undoing choices in backtracking
- Infinite recursion due to incorrect base case
- Stack overflow for deep recursion

---

## Conclusion

Recursion and backtracking are powerful techniques in competitive programming. Master these concepts by:

1. **Understanding the fundamentals**: Base cases, recursive cases, call stack
2. **Learning the patterns**: Tree traversal, divide & conquer, memoization
3. **Practicing backtracking**: Use the template, understand choose-explore-unchoose
4. **Optimizing solutions**: Apply memoization, pruning, and DP transitions
5. **Solving problems**: Start with easy problems and gradually increase difficulty

Remember: Practice makes perfect! Solve as many problems as possible to internalize these concepts.

---

## Additional Resources

- **Online Judges**: LeetCode, Codeforces, AtCoder
- **Books**: "Introduction to Algorithms" by Cormen et al.
- **Practice**: Start with recursion basics, then move to backtracking
- **Contests**: Participate in regular contests to apply these techniques

Good luck with your competitive programming journey!
