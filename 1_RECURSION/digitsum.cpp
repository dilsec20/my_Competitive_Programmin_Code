#include <bits/stdc++.h>
using namespace std;

long long  digitSum(long long n) {
    if (n == 0)
        return 0;
    return (n % 10) + digitSum(n / 10);
}

int main(){
    long long  n;
    cin>>n;
    long long  num = digitSum(n);
    cout<<num<<endl;
    return 0;
}
// vector<long long> digitsum(long long n) {
//     if (n == 0) {
//         return {};
//     }
//     vector<long long> result = digitsum(n / 10);
//     result.push_back(n % 10);
//     return result;
// }
// int main() {
//     long long n;
//     cin >> n;
//     long long sum = 0;
//     vector<long long> digits = digitsum(n);
//     for (long long digit : digits) {
//         sum += digit;
        
//     }
//     cout << sum << endl;
//     return 0;
// }

