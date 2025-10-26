#include <bits/stdc++.h>
using namespace std;

// ===========================================
// ADVANCED RECURSION PATTERNS
// ===========================================

// 1. TREE TRAVERSAL (DFS) - Foundation for many problems
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Preorder: Root -> Left -> Right
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";  // Process root
    preorder(root->left);       // Visit left
    preorder(root->right);      // Visit right
}

// Inorder: Left -> Root -> Right
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);        // Visit left
    cout << root->val << " ";  // Process root
    inorder(root->right);       // Visit right
}

// Postorder: Left -> Right -> Root
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);      // Visit left
    postorder(root->right);     // Visit right
    cout << root->val << " ";  // Process root
}

// 2. DIVIDE & CONQUER - Binary Search
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

// 3. MEMOIZATION - Fibonacci with DP
unordered_map<int, long long> memo;

long long fibonacciMemo(int n) {
    if (n <= 1) return n;  // Base cases
    
    if (memo.find(n) != memo.end()) {
        return memo[n];  // Return cached result
    }
    
    memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
    return memo[n];
}

// 4. MULTIPLE RECURSIVE CALLS - Path counting
int countPaths(int m, int n) {
    // Base case: reached destination
    if (m == 1 || n == 1) return 1;
    
    // Recursive case: sum of paths from top and left
    return countPaths(m - 1, n) + countPaths(m, n - 1);
}

// 5. RECURSION WITH BACKTRACKING - Generate all subsets
void generateSubsets(vector<int>& nums, vector<int>& current, int index, vector<vector<int>>& result) {
    // Base case: processed all elements
    if (index == nums.size()) {
        result.push_back(current);
        return;
    }
    
    // Choice 1: Don't include current element
    generateSubsets(nums, current, index + 1, result);
    
    // Choice 2: Include current element
    current.push_back(nums[index]);
    generateSubsets(nums, current, index + 1, result);
    current.pop_back();  // Backtrack!
}

// 6. RECURSION WITH PRUNING - N-Queens (simplified)
bool isSafe(vector<string>& board, int row, int col, int n) {
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

void solveNQueens(vector<string>& board, int row, int n, vector<vector<string>>& solutions) {
    // Base case: placed all queens
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';  // Make choice
            solveNQueens(board, row + 1, n, solutions);  // Recurse
            board[row][col] = '.';  // Backtrack
        }
    }
}

// ===========================================
// COMPETITIVE PROGRAMMING EXAMPLES
// ===========================================

// Problem: Count ways to reach nth stair (can take 1 or 2 steps)
int countWays(int n) {
    if (n <= 1) return 1;  // Base cases
    return countWays(n - 1) + countWays(n - 2);
}

// Problem: Generate all permutations
void generatePermutations(vector<int>& nums, int start, vector<vector<int>>& result) {
    if (start == nums.size()) {
        result.push_back(nums);
        return;
    }
    
    for (int i = start; i < nums.size(); i++) {
        swap(nums[start], nums[i]);  // Make choice
        generatePermutations(nums, start + 1, result);  // Recurse
        swap(nums[start], nums[i]);  // Backtrack
    }
}

// Problem: Word Search (simplified)
bool wordSearch(vector<vector<char>>& board, string word, int i, int j, int index) {
    if (index == word.length()) return true;  // Found word
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return false;
    if (board[i][j] != word[index]) return false;
    
    char temp = board[i][j];
    board[i][j] = '#';  // Mark as visited
    
    bool found = wordSearch(board, word, i + 1, j, index + 1) ||
                 wordSearch(board, word, i - 1, j, index + 1) ||
                 wordSearch(board, word, i, j + 1, index + 1) ||
                 wordSearch(board, word, i, j - 1, index + 1);
    
    board[i][j] = temp;  // Backtrack
    return found;
}

// ===========================================
// TESTING FUNCTIONS
// ===========================================

int main() {
    cout << "=== Advanced Recursion Examples ===\n\n";
    
    // Test Fibonacci with memoization
    cout << "Fibonacci(10) with memoization: " << fibonacciMemo(10) << "\n";
    
    // Test path counting
    cout << "Ways to reach (3,3): " << countWays(3) << "\n";
    
    // Test subset generation
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> subsets;
    vector<int> current;
    generateSubsets(nums, current, 0, subsets);
    
    cout << "All subsets of [1,2,3]:\n";
    for (auto& subset : subsets) {
        cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";
    
    // Test permutation generation
    vector<vector<int>> permutations;
    generatePermutations(nums, 0, permutations);
    
    cout << "All permutations of [1,2,3]:\n";
    for (auto& perm : permutations) {
        cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            cout << perm[i];
            if (i < perm.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n";
    
    return 0;
}
