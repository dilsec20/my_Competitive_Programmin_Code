#include <bits/stdc++.h>
using namespace std;

// void hanoi(int n, int from, int to , int aux, vector<pair<int,int>> &moves) {
//     if (n == 0) return;
//     hanoi(n - 1, from, aux, to, moves);
//     moves.push_back({from, to});
//     hanoi(n - 1, aux, to, from, moves);
// }


// vector<pair<int,int>> towerOfHanoi(int n) {
//     vector<pair<int,int>> moves;
//     hanoi(n, 1, 3, 2, moves);
//     return moves;
// }
// int main() {
//     int n;
//     cout << "Enter number of disks: ";
//     cin >> n;
//     vector<pair<int,int>> result = towerOfHanoi(n);
//     cout << "The sequence of moves involved in the Tower of Hanoi are:\n";
//     for (auto move : result) {
//         cout << "Move disk from rod " << move.first << " to rod " << move.second << endl;
//     }
//     return 0;
// }

int towerOfHanoi(int n, int from, int to , int aux) {
    if (n == 1) {
        
        return 1;
    }
    int moves = 0;
    moves += towerOfHanoi(n - 1, from, aux, to);
    
    moves += 1;
    moves += towerOfHanoi(n - 1, aux, to, from);
    return moves;
}
int main() {
    int n;
    
    cin >> n;
    int result = towerOfHanoi(n, 1, 3, 2);
    cout  << result << endl;
    return 0;
}