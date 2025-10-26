# Greedy Algorithms in C++ for Competitive Programming

## Table of Contents
1. [Introduction](#introduction)
2. [Basic Greedy Concepts](#basic-greedy-concepts)
3. [Common Greedy Patterns](#common-greedy-patterns)
4. [Interval Problems](#interval-problems)
5. [Activity Selection](#activity-selection)
6. [Greedy Scheduling](#greedy-scheduling)
7. [Practice Problems](#practice-problems)
8. [Tips for Competitive Programming](#tips-for-competitive-programming)

---

## Introduction

A greedy algorithm makes locally optimal choices at each step with the hope of finding a global optimum. It's a problem-solving approach where at each step, you make the best choice available without considering future consequences.

### When to Use Greedy?
- **Optimal substructure**: Problem can be broken into subproblems
- **Greedy choice property**: Locally optimal choices lead to global optimum
- **No overlapping subproblems**: Unlike DP, we don't revisit subproblems

### What You'll Learn:
- Activity selection and interval scheduling
- Fractional knapsack and greedy optimization
- Minimum spanning tree (Kruskal's, Prim's)
- Shortest path algorithms (Dijkstra's)
- Huffman coding and data compression
- Job scheduling and deadline problems

---

## Basic Greedy Concepts

### Key Principles

1. **Greedy Choice**: Make the best local choice
2. **Optimal Substructure**: Optimal solution contains optimal sub-solutions
3. **Prove It Works**: Mathematical proof for correctness

### Example: Coin Change (Greedy)

```cpp
int coinChangeGreedy(vector<int>& coins, int amount) {
    // Sort in descending order
    sort(coins.rbegin(), coins.rend());
    
    int count = 0;
    
    for (int coin : coins) {
        while (amount >= coin) {
            amount -= coin;
            count++;
        }
    }
    
    return (amount == 0) ? count : -1;
}
```

**Note**: Greedy only works when coin system is "canonical" (e.g., USD coins)

---

## Common Greedy Patterns

### 1. Activity Selection Problem

```cpp
struct Activity {
    int start, end;
    
    bool operator<(const Activity& other) const {
        return end < other.end;
    }
};

int maxActivities(vector<Activity>& activities) {
    sort(activities.begin(), activities.end());
    
    int count = 1;
    int lastEnd = activities[0].end;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastEnd) {
            count++;
            lastEnd = activities[i].end;
        }
    }
    
    return count;
}
```

### 2. Fractional Knapsack

```cpp
struct Item {
    int value, weight;
    double ratio;  // value per unit weight
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    // Calculate ratio for each item
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }
    
    sort(items.begin(), items.end(), compareItems);
    
    double totalValue = 0.0;
    
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += item.ratio * capacity;
            break;
        }
    }
    
    return totalValue;
}
```

### 3. Minimum Platforms Required

```cpp
int minPlatforms(vector<int>& arrival, vector<int>& departure) {
    sort(arrival.begin(), arrival.end());
    sort(departure.begin(), departure.end());
    
    int i = 0, j = 0;
    int platforms = 0;
    int maxPlatforms = 0;
    
    while (i < arrival.size() && j < departure.size()) {
        if (arrival[i] <= departure[j]) {
            platforms++;
            i++;
        } else {
            platforms--;
            j++;
        }
        maxPlatforms = max(maxPlatforms, platforms);
    }
    
    return maxPlatforms;
}
```

### 4. Job Sequencing with Deadlines

```cpp
struct Job {
    int profit, deadline, id;
    
    bool operator<(const Job& other) const {
        return profit > other.profit;
    }
};

int jobSequencing(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end());
    
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }
    
    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0;
    
    for (const auto& job : jobs) {
        for (int j = min(job.deadline, maxDeadline); j >= 1; j--) {
            if (!slot[j]) {
                slot[j] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    
    return totalProfit;
}
```

---

## Interval Problems

### 1. Merge Intervals

```cpp
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end(), 
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });
    
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

### 2. Non-overlapping Intervals

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[1] < b[1];
         });
    
    int keep = 1;
    int end = intervals[0][1];
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= end) {
            keep++;
            end = intervals[i][1];
        }
    }
    
    return intervals.size() - keep;
}
```

### 3. Insert Interval

```cpp
vector<vector<int>> insertInterval(vector<vector<int>>& intervals, 
                                     vector<int>& newInterval) {
    vector<vector<int>> result;
    int i = 0;
    
    // Add intervals before newInterval
    while (i < intervals.size() && intervals[i][1] < newInterval[0]) {
        result.push_back(intervals[i++]);
    }
    
    // Merge overlapping intervals
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);
    
    // Add remaining intervals
    while (i < intervals.size()) {
        result.push_back(intervals[i++]);
    }
    
    return result;
}
```

---

## Activity Selection

### Select Maximum Non-overlapping Activities

```cpp
int maxActivities(vector<pair<int, int>>& activities) {
    sort(activities.begin(), activities.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
             return a.second < b.second;
         });
    
    int count = 1;
    int lastEnd = activities[0].second;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].first >= lastEnd) {
            count++;
            lastEnd = activities[i].second;
        }
    }
    
    return count;
}
```

### Weighted Activity Selection

```cpp
struct WeightedActivity {
    int start, end, weight;
};

bool compareEnd(const WeightedActivity& a, const WeightedActivity& b) {
    return a.end < b.end;
}

int weightedActivitySelection(vector<WeightedActivity>& activities) {
    sort(activities.begin(), activities.end(), compareEnd);
    
    vector<int> dp(activities.size());
    dp[0] = activities[0].weight;
    
    for (int i = 1; i < activities.size(); i++) {
        int j = binarySearchLastNonOverlapping(activities, i);
        dp[i] = max(dp[i-1], 
                   (j != -1 ? dp[j] : 0) + activities[i].weight);
    }
    
    return dp[activities.size() - 1];
}
```

---

## Greedy Scheduling

### 1. Task Scheduler

```cpp
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> count;
    int maxCount = 0;
    int maxFreq = 0;
    
    for (char task : tasks) {
        count[task]++;
        maxFreq = max(maxFreq, count[task]);
    }
    
    for (auto& [task, cnt] : count) {
        if (cnt == maxFreq) maxCount++;
    }
    
    int result = (maxFreq - 1) * (n + 1) + maxCount;
    return max(result, (int)tasks.size());
}
```

### 2. Meeting Rooms II

```cpp
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<pair<int, int>> points;
    
    for (const auto& interval : intervals) {
        points.push_back({interval[0], 1});   // Start
        points.push_back({interval[1], -1});  // End
    }
    
    sort(points.begin(), points.end());
    
    int rooms = 0;
    int maxRooms = 0;
    
    for (const auto& point : points) {
        rooms += point.second;
        maxRooms = max(maxRooms, rooms);
    }
    
    return maxRooms;
}
```

### 3. Maximum Units on a Truck

```cpp
int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    sort(boxTypes.begin(), boxTypes.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[1] > b[1];
         });
    
    int totalUnits = 0;
    
    for (const auto& box : boxTypes) {
        int boxesToTake = min(truckSize, box[0]);
        totalUnits += boxesToTake * box[1];
        truckSize -= boxesToTake;
        
        if (truckSize == 0) break;
    }
    
    return totalUnits;
}
```

---

## Greedy on Strings

### 1. Remove Duplicate Letters

```cpp
string removeDuplicateLetters(string s) {
    vector<int> lastIndex(26, -1);
    vector<bool> visited(26, false);
    string result;
    
    // Find last occurrence of each character
    for (int i = 0; i < s.length(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    for (int i = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        
        if (visited[c]) continue;
        
        // Remove larger characters that appear later
        while (!result.empty() && result.back() > s[i] && 
               lastIndex[result.back() - 'a'] > i) {
            visited[result.back() - 'a'] = false;
            result.pop_back();
        }
        
        visited[c] = true;
        result += s[i];
    }
    
    return result;
}
```

### 2. Partition Labels

```cpp
vector<int> partitionLabels(string s) {
    vector<int> lastIndex(26, -1);
    
    // Find last occurrence of each character
    for (int i = 0; i < s.length(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    vector<int> result;
    int start = 0;
    int end = 0;
    
    for (int i = 0; i < s.length(); i++) {
        end = max(end, lastIndex[s[i] - 'a']);
        
        if (i == end) {
            result.push_back(i - start + 1);
            start = i + 1;
        }
    }
    
    return result;
}
```

---

## Greedy Optimization

### 1. Best Time to Buy and Sell Stock

```cpp
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}
```

### 2. Gas Station

```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0;
    int current = 0;
    int start = 0;
    
    for (int i = 0; i < gas.size(); i++) {
        total += gas[i] - cost[i];
        current += gas[i] - cost[i];
        
        if (current < 0) {
            current = 0;
            start = i + 1;
        }
    }
    
    return (total >= 0) ? start : -1;
}
```

### 3. Jump Game

```cpp
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    
    return true;
}

// Jump Game II - minimum jumps
int jump(vector<int>& nums) {
    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;
    
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

---

## Practice Problems

### Easy Level (800-1200)
1. Best Time to Buy and Sell Stock
2. Jump Game
3. Partition Labels
4. Maximum Units on a Truck
5. Two City Scheduling

### Medium Level (1200-1800)
1. Activity Selection
2. Fractional Knapsack
3. Job Sequencing
4. Minimum Platforms
5. Gas Station

### Hard Level (1800+)
1. Weighted Activity Selection
2. Scheduling with Machines
3. Optimal Resource Allocation
4. Advanced Interval Problems
5. Greedy on Trees

---

## Tips for Competitive Programming

### 1. When to Use Greedy?
- Problem has **optimal substructure**
- **Greedy choice property** holds
- Can make local optimal choice without considering future

### 2. Common Patterns
- **Sorting + Greedy**: Sort by some criteria then greedily select
- **Interval Scheduling**: Sort by end time, select non-overlapping
- **Knapsack Variants**: Sort by value/weight ratio
- **Graph Greedy**: MST, shortest path

### 3. Debugging Tips
- Test with edge cases
- Verify with small examples
- Prove correctness if possible
- Consider greedy might not work (need DP)

### 4. Common Mistakes
- Not sorting properly
- Wrong comparison function
- Missing edge cases
- Assuming greedy always works (might need DP)

---

## Conclusion

Master Greedy Algorithms by:

1. **Understanding when greedy works**: Optimal substructure + greedy choice
2. **Learning common patterns**: Activity selection, scheduling, knapsack
3. **Practicing problems**: Start easy, move to optimization
4. **Knowing when not to use**: Some problems need DP instead
5. **Proving correctness**: Mathematical verification

Remember: Greedy makes locally optimal choices. Not all problems can be solved greedily - know when to use DP instead!

Good luck with your competitive programming journey!

