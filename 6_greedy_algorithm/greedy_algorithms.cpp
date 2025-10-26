#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// ACTIVITY SELECTION
// ============================================================================

struct Activity {
    int start, end, id;
    
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

// ============================================================================
// FRACTIONAL KNAPSACK
// ============================================================================

struct Item {
    int value, weight;
    double ratio;
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
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

// ============================================================================
// JOB SEQUENCING WITH DEADLINES
// ============================================================================

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

// ============================================================================
// MINIMUM PLATFORMS REQUIRED
// ============================================================================

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

// ============================================================================
// INTERVAL PROBLEMS
// ============================================================================

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

vector<vector<int>> insertInterval(vector<vector<int>>& intervals, 
                                     vector<int>& newInterval) {
    vector<vector<int>> result;
    int i = 0;
    
    while (i < intervals.size() && intervals[i][1] < newInterval[0]) {
        result.push_back(intervals[i++]);
    }
    
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);
    
    while (i < intervals.size()) {
        result.push_back(intervals[i++]);
    }
    
    return result;
}

int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<pair<int, int>> points;
    
    for (const auto& interval : intervals) {
        points.push_back({interval[0], 1});
        points.push_back({interval[1], -1});
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

// ============================================================================
// GREEDY STRING OPERATIONS
// ============================================================================

string removeDuplicateLetters(string s) {
    vector<int> lastIndex(26, -1);
    vector<bool> visited(26, false);
    string result;
    
    for (int i = 0; i < s.length(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    for (int i = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        
        if (visited[c]) continue;
        
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

vector<int> partitionLabels(string s) {
    vector<int> lastIndex(26, -1);
    
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

// ============================================================================
// STOCK PROBLEMS
// ============================================================================

int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}

int maxProfitMultiple(vector<int>& prices) {
    int profit = 0;
    
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i-1]) {
            profit += prices[i] - prices[i-1];
        }
    }
    
    return profit;
}

int maxProfitWithFee(vector<int>& prices, int fee) {
    int hold = -prices[0];
    int sold = 0;
    
    for (int i = 1; i < prices.size(); i++) {
        int prevSold = sold;
        sold = max(sold, hold + prices[i] - fee);
        hold = max(hold, prevSold - prices[i]);
    }
    
    return sold;
}

// ============================================================================
// JUMP GAME
// ============================================================================

bool canJump(vector<int>& nums) {
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    
    return true;
}

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

// ============================================================================
// GAS STATION
// ============================================================================

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

// ============================================================================
// JOB SCHEDULING
// ============================================================================

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

// ============================================================================
// MAXIMUM UNITS ON TRUCK
// ============================================================================

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

// ============================================================================
// COIN CHANGE (GREEDY)
// ============================================================================

int coinChangeGreedy(vector<int>& coins, int amount) {
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

// ============================================================================
// TWO CITY SCHEDULING
// ============================================================================

int twoCityScheduling(vector<vector<int>>& costs) {
    sort(costs.begin(), costs.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return (a[1] - a[0]) > (b[1] - b[0]);
         });
    
    int total = 0;
    int n = costs.size() / 2;
    
    for (int i = 0; i < n; i++) {
        total += costs[i][0] + costs[i+n][1];
    }
    
    return total;
}

// ============================================================================
// TESTING FUNCTIONS
// ============================================================================

void testActivitySelection() {
    cout << "Testing Activity Selection:" << endl;
    
    vector<Activity> activities = {
        {1, 2, 1}, {3, 4, 2}, {0, 6, 3}, 
        {5, 7, 4}, {8, 9, 5}, {5, 9, 6}
    };
    
    int result = maxActivities(activities);
    cout << "Max activities that can be done: " << result << endl;
    cout << endl;
}

void testFractionalKnapsack() {
    cout << "Testing Fractional Knapsack:" << endl;
    
    vector<Item> items = {
        {60, 10, 0}, {100, 20, 0}, {120, 30, 0}
    };
    int capacity = 50;
    
    double result = fractionalKnapsack(items, capacity);
    cout << "Maximum value: " << result << endl;
    cout << endl;
}

void testIntervalProblems() {
    cout << "Testing Interval Problems:" << endl;
    
    vector<vector<int>> intervals = {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}
    };
    
    vector<vector<int>> merged = mergeIntervals(intervals);
    cout << "Merged intervals: ";
    for (const auto& interval : merged) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;
    cout << endl;
}

void testGreedyOptimization() {
    cout << "Testing Greedy Optimization:" << endl;
    
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int profit = maxProfit(prices);
    cout << "Max profit from stock: " << profit << endl;
    
    vector<int> nums = {2, 3, 1, 1, 4};
    bool canReach = canJump(nums);
    cout << "Can reach end: " << canReach << endl;
    
    cout << endl;
}

void testStringProblems() {
    cout << "Testing String Problems:" << endl;
    
    string s = "bcabc";
    string result = removeDuplicateLetters(s);
    cout << "Remove duplicates from '" << s << "': " << result << endl;
    
    string s2 = "ababcbacadefegdehijhklij";
    vector<int> partitions = partitionLabels(s2);
    cout << "Partition sizes: ";
    for (int size : partitions) cout << size << " ";
    cout << endl;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "Greedy Algorithms Test Suite" << endl;
    cout << "===========================" << endl << endl;
    
    testActivitySelection();
    testFractionalKnapsack();
    testIntervalProblems();
    testGreedyOptimization();
    testStringProblems();
    
    return 0;
}

