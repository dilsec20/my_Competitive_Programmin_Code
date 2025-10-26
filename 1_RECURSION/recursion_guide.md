# Recursion & Backtracking Guide for Competitive Programming

## 📚 Learning Path

### Phase 1: Recursion Fundamentals ✅ (You have this!)
- Base cases and recursive cases
- Call stack understanding
- Simple recursive functions

### Phase 2: Advanced Recursion Patterns
- Tree traversals (DFS)
- Divide & Conquer
- Memoization
- Multiple recursive calls

### Phase 3: Backtracking Introduction
- What is backtracking?
- Backtracking template
- State space tree concept

### Phase 4: Classic Backtracking Problems
- N-Queens Problem
- Sudoku Solver
- Generate Subsets
- Generate Permutations
- Combination Sum
- Word Search

### Phase 5: Optimization Techniques
- Pruning strategies
- Memoization in backtracking
- DP transitions from recursion

### Phase 6: Competitive Programming Problems
- Codeforces/LeetCode problems
- Contest-style problems
- Time complexity analysis

## 🎯 Key Concepts to Master

### Recursion Template:
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

### Backtracking Template:
```cpp
void backtrack(current_state) {
    // Base case - found a solution
    if (is_solution(current_state)) {
        process_solution(current_state);
        return;
    }
    
    // Try all possible choices
    for (each possible choice) {
        if (is_valid(choice)) {
            make_choice(choice);
            backtrack(updated_state);
            undo_choice(choice); // Backtrack!
        }
    }
}
```

## 📝 Practice Problems Order

1. **Easy Recursion**: Print patterns, count digits, reverse string
2. **Medium Recursion**: Binary tree problems, path finding
3. **Easy Backtracking**: Generate subsets, permutations
4. **Medium Backtracking**: N-Queens, Sudoku
5. **Hard Backtracking**: Word search, combination problems
6. **Competitive**: Contest problems with time constraints

## ⚡ Performance Tips

- Always identify the time complexity
- Use memoization when subproblems overlap
- Apply pruning to reduce search space
- Consider iterative solutions for better space efficiency
- Practice drawing recursion trees for complex problems
