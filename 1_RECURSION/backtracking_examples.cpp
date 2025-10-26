#include <bits/stdc++.h>
using namespace std;

// ===========================================
// BACKTRACKING TEMPLATE & EXAMPLES
// ===========================================

/*
BACKTRACKING TEMPLATE:

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
*/

// ===========================================
// CLASSIC BACKTRACKING PROBLEMS
// ===========================================

// 1. N-QUEENS PROBLEM
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

// 2. SUBSET GENERATION
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

// 3. PERMUTATION GENERATION
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

// 4. COMBINATION SUM
class CombinationSum {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int target, int start, vector<int>& current, vector<vector<int>>& result) {
        // Base case: found a valid combination
        if (target == 0) {
            result.push_back(current);
            return;
        }
        
        // Try each candidate
        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] > target) break;  // Pruning
            
            current.push_back(candidates[i]);  // Choose
            backtrack(candidates, target - candidates[i], i, current, result);  // Explore
            current.pop_back();  // Backtrack
        }
    }
};

// 5. WORD SEARCH
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

// 6. SUDOKU SOLVER
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

// ===========================================
// COMPETITIVE PROGRAMMING EXAMPLES
// ===========================================

// Problem: Generate all valid parentheses
class ValidParentheses {
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

// Problem: Letter combinations of phone number
class LetterCombinations {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> result;
        string current;
        backtrack(digits, 0, current, result);
        return result;
    }
    
private:
    vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    void backtrack(string& digits, int index, string& current, vector<string>& result) {
        // Base case: generated complete combination
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }
        
        string letters = phone[digits[index] - '0'];
        for (char c : letters) {
            current.push_back(c);  // Choose
            backtrack(digits, index + 1, current, result);  // Explore
            current.pop_back();  // Backtrack
        }
    }
};

// ===========================================
// TESTING FUNCTIONS
// ===========================================

int main() {
    cout << "=== Backtracking Examples ===\n\n";
    
    // Test subset generation
    vector<int> nums = {1, 2, 3};
    Subsets subsetGenerator;
    auto subsets = subsetGenerator.generateSubsets(nums);
    
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
    Permutations permGenerator;
    auto permutations = permGenerator.generatePermutations(nums);
    
    cout << "All permutations of [1,2,3]:\n";
    for (auto& perm : permutations) {
        cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            cout << perm[i];
            if (i < perm.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";
    
    // Test valid parentheses
    ValidParentheses parenGenerator;
    auto parentheses = parenGenerator.generateParenthesis(3);
    
    cout << "Valid parentheses for n=3:\n";
    for (auto& paren : parentheses) {
        cout << paren << " ";
    }
    cout << "\n\n";
    
    // Test combination sum
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    CombinationSum combSum;
    auto combinations = combSum.combinationSum(candidates, target);
    
    cout << "Combinations that sum to " << target << ":\n";
    for (auto& comb : combinations) {
        cout << "[";
        for (int i = 0; i < comb.size(); i++) {
            cout << comb[i];
            if (i < comb.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n";
    
    return 0;
}
