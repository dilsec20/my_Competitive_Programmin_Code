# Greedy Algorithms Quick Reference

## Quick Patterns

### Activity Selection
```cpp
struct Activity { int start, end; };

int maxActivities(vector<Activity>& a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) { 
        return x.end < y.end; 
    });
    
    int count = 1, lastEnd = a[0].end;
    for (int i = 1; i < a.size(); i++) {
        if (a[i].start >= lastEnd) {
            count++;
            lastEnd = a[i].end;
        }
    }
    return count;
}
```

### Fractional Knapsack
```cpp
struct Item { int value, weight; };

double fractionalKnapsack(vector<Item>& items, int cap) {
    sort(items.begin(), items.end(),
         [](auto& a, auto& b) {
             return (double)a.value / a.weight > 
                    (double)b.value / b.weight;
         });
    
    double val = 0.0;
    for (auto& item : items) {
        if (cap >= item.weight) {
            val += item.value;
            cap -= item.weight;
        } else {
            val += (double)item.value / item.weight * cap;
            break;
        }
    }
    return val;
}
```

### Merge Intervals
```cpp
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}
```

### Job Sequencing
```cpp
struct Job { int profit, deadline; };

int jobSequencing(vector<Job>& jobs) {
    sort(jobs.rbegin(), jobs.rend());
    
    vector<bool> slot(maxDeadline + 1, false);
    int profit = 0;
    
    for (auto& job : jobs) {
        for (int j = job.deadline; j >= 1; j--) {
            if (!slot[j]) {
                slot[j] = true;
                profit += job.profit;
                break;
            }
        }
    }
    return profit;
}
```

### Stock Trading (Multiple Trades)
```cpp
int maxProfit(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i-1]) {
            profit += prices[i] - prices[i-1];
        }
    }
    return profit;
}
```

### Jump Game
```cpp
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    return true;
}

int minJumps(vector<int>& nums) {
    int jumps = 0, currentEnd = 0, farthest = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    return jumps;
}
```

## Common Sorting Criteria

| Problem Type | Sort By | Why |
|--------------|---------|-----|
| Activity Selection | End time | Finish early first |
| Job Sequencing | Profit | Maximize profit |
| Fractional Knapsack | Value/Weight | Best value per unit |
| Interval Merging | Start time | Sequential processing |
| Remove Overlaps | End time | Keep shorter intervals |
| Two City Scheduling | Difference | Cost difference |
| Maximum Units | Units per box | Maximize units |

## When to Use Greedy

### ✅ Use Greedy When:
- Problem has **optimal substructure**
- **Greedy choice property** holds
- Can make locally optimal choice
- No need to consider all possibilities
- Can determine priority/ordering

### ❌ DON'T Use Greedy When:
- Need to consider all possibilities
- Subproblems overlap (use DP)
- Locally optimal ≠ globally optimal
- Need to "undo" choices
- Problem requires backtracking

## Common Patterns

### Pattern 1: Sort + Select
```cpp
sort(items.begin(), items.end(), compare);
for (auto& item : items) {
    if (condition) select(item);
}
```

### Pattern 2: Sort + Merge
```cpp
sort(intervals.begin(), intervals.end());
vector<Result> merged;
for (auto& interval : intervals) {
    if (overlaps) merge(interval);
    else add(interval);
}
```

### Pattern 3: Priority Selection
```cpp
priority_queue<Item, vector<Item>, Compare> pq;
for (auto& item : items) pq.push(item);
while (!pq.empty() && condition) {
    process(pq.top());
    pq.pop();
}
```

## Time Complexity

- **Sorting**: O(n log n)
- **Single pass**: O(n)
- **Combined**: O(n log n)
- **Priority queue**: O(n log n)

## Debugging Tips

1. **Test with small examples** - Manual verification
2. **Check sorting order** - Is criteria correct?
3. **Verify edge cases** - Empty, single, edge values
4. **Prove greedy choice** - Why optimal?
5. **Consider alternatives** - Should use DP?

## STL Tips

```cpp
// Custom comparator
sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
    return a.end < b.end;  // Sort by end time
});

// Priority queue (max heap)
priority_queue<int> maxHeap;

// Priority queue (min heap)
priority_queue<int, vector<int>, greater<int>> minHeap;

// Custom priority queue
struct Compare {
    bool operator()(const Job& a, const Job& b) {
        return a.profit < b.profit;  // Lower first
    }
};
priority_queue<Job, vector<Job>, Compare> pq;
```

## Common Mistakes

1. ❌ Wrong sorting criteria
2. ❌ Using greedy when DP needed
3. ❌ Not handling tie cases
4. ❌ Missing edge cases
5. ❌ Incorrect loop boundaries

## Key Takeaways

- **Sorting is crucial** - Most greedy problems require sorting
- **Comparison function matters** - Determines correctness
- **Prove it works** - Mathematical verification
- **Know alternatives** - When to use DP instead
- **Test thoroughly** - Edge cases are critical

## See Also
- [Greedy_Algorithm_Guide.md](Greedy_Algorithm_Guide.md) - Complete guide
- [greedy_algorithms.cpp](greedy_algorithms.cpp) - Code implementations
- [practice_problems_list.md](practice_problems_list.md) - Problem lists

