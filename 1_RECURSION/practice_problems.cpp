#include <bits/stdc++.h>
using namespace std;

// ===========================================
// PRACTICE PROBLEM SET
// ===========================================

// Problem 1: Print all permutations of a string
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

// Problem 2: Count number of ways to reach nth stair
int countStairs(int n) {
    if (n <= 1) return 1;
    return countStairs(n - 1) + countStairs(n - 2);
}

// Problem 3: Generate all subsets of an array
void generateSubsets(vector<int>& nums, vector<int>& current, int index, vector<vector<int>>& result) {
    result.push_back(current);
    
    for (int i = index; i < nums.size(); i++) {
        current.push_back(nums[i]);
        generateSubsets(nums, current, i + 1, result);
        current.pop_back();
    }
}

// Problem 4: Find all paths in a binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void findPaths(TreeNode* root, vector<int>& path, vector<vector<int>>& allPaths) {
    if (!root) return;
    
    path.push_back(root->val);
    
    if (!root->left && !root->right) {
        allPaths.push_back(path);
    } else {
        findPaths(root->left, path, allPaths);
        findPaths(root->right, path, allPaths);
    }
    
    path.pop_back();  // Backtrack
}

// Problem 5: Solve Sudoku
bool solveSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        if (solveSudoku(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool isValid(vector<vector<char>>& board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == c) return false;
        if (board[i][col] == c) return false;
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
    }
    return true;
}

// Problem 6: Generate all valid parentheses
void generateParentheses(int n, string current, int open, int close, vector<string>& result) {
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }
    
    if (open < n) {
        generateParentheses(n, current + "(", open + 1, close, result);
    }
    
    if (close < open) {
        generateParentheses(n, current + ")", open, close + 1, result);
    }
}

// Problem 7: Find all combinations that sum to target
void combinationSum(vector<int>& candidates, int target, vector<int>& current, 
                   int start, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    
    for (int i = start; i < candidates.size(); i++) {
        if (candidates[i] > target) break;
        
        current.push_back(candidates[i]);
        combinationSum(candidates, target - candidates[i], current, i, result);
        current.pop_back();
    }
}

// Problem 8: Word Search in 2D grid
bool wordSearch(vector<vector<char>>& board, string word, int i, int j, int index) {
    if (index == word.length()) return true;
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return false;
    if (board[i][j] != word[index]) return false;
    
    char temp = board[i][j];
    board[i][j] = '#';
    
    bool found = wordSearch(board, word, i + 1, j, index + 1) ||
                 wordSearch(board, word, i - 1, j, index + 1) ||
                 wordSearch(board, word, i, j + 1, index + 1) ||
                 wordSearch(board, word, i, j - 1, index + 1);
    
    board[i][j] = temp;
    return found;
}

// Problem 9: Generate all permutations with duplicates
void permuteUnique(vector<int>& nums, vector<int>& current, vector<bool>& used, vector<vector<int>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) continue;
        
        used[i] = true;
        current.push_back(nums[i]);
        permuteUnique(nums, current, used, result);
        current.pop_back();
        used[i] = false;
    }
}

// Problem 10: Rat in a Maze
bool ratInMaze(vector<vector<int>>& maze, int i, int j, vector<vector<int>>& path) {
    int n = maze.size();
    if (i < 0 || i >= n || j < 0 || j >= n || maze[i][j] == 0) return false;
    
    path[i][j] = 1;
    
    if (i == n - 1 && j == n - 1) return true;
    
    if (ratInMaze(maze, i + 1, j, path) || ratInMaze(maze, i, j + 1, path)) {
        return true;
    }
    
    path[i][j] = 0;  // Backtrack
    return false;
}

// ===========================================
// OPTIMIZATION TECHNIQUES
// ===========================================

// Memoization for Fibonacci
unordered_map<int, long long> memo;
long long fibonacciMemo(int n) {
    if (n <= 1) return n;
    if (memo.find(n) != memo.end()) return memo[n];
    
    memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
    return memo[n];
}

// DP for climbing stairs
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

// ===========================================
// TESTING FUNCTIONS
// ===========================================

int main() {
    cout << "=== Practice Problem Solutions ===\n\n";
    
    // Test 1: Permutations
    string str = "ABC";
    cout << "Permutations of " << str << ": ";
    printPermutations(str, 0, str.length() - 1);
    cout << "\n\n";
    
    // Test 2: Stairs
    int n = 5;
    cout << "Ways to climb " << n << " stairs: " << countStairs(n) << "\n";
    cout << "Ways to climb " << n << " stairs (DP): " << climbStairsDP(n) << "\n\n";
    
    // Test 3: Subsets
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> subsets;
    vector<int> current;
    generateSubsets(nums, current, 0, subsets);
    
    cout << "Subsets of [1,2,3]:\n";
    for (auto& subset : subsets) {
        cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";
    
    // Test 4: Parentheses
    vector<string> parentheses;
    generateParentheses(3, "", 0, 0, parentheses);
    
    cout << "Valid parentheses for n=3:\n";
    for (auto& paren : parentheses) {
        cout << paren << " ";
    }
    cout << "\n\n";
    
    // Test 5: Combination Sum
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> combinations;
    vector<int> currentComb;
    combinationSum(candidates, target, currentComb, 0, combinations);
    
    cout << "Combinations that sum to " << target << ":\n";
    for (auto& comb : combinations) {
        cout << "[";
        for (int i = 0; i < comb.size(); i++) {
            cout << comb[i];
            if (i < comb.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";
    
    // Test 6: Fibonacci with memoization
    cout << "Fibonacci(20) with memoization: " << fibonacciMemo(20) << "\n";
    
    return 0;
}
