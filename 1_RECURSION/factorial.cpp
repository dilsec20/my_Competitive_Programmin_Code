#include <bits/stdc++.h>
using namespace std;

// vector<int> factorial(int n) {
//     if (n == 0) return {1}; 

//     vector<int> prevFactorial = factorial(n - 1);
//     vector<int> result;
//     int carry = 0;

   
//     for (int digit : prevFactorial) {
//         int prod = digit * n + carry;
//         result.push_back(prod % 10);
//         carry = prod / 10;
//     }


//     while (carry) {
//         result.push_back(carry % 10);
//         carry /= 10;
//     }

//     return result;
// }
// int main() {
//     int n;
//     cout << "Enter a number to compute its factorial: ";
//     cin >> n;
//     vector<int> result = factorial(n);

//     cout << n << "! = ";
//     for (auto it = result.rbegin(); it != result.rend(); ++it) {
//         cout << *it;
//     }
//     cout << endl;
    
    
    


//     return 0;
// }

int factorial(int n){
    if(n==0) return 1;
    return n*factorial(n-1);
}
int main(){
    int n;
    cout<<"Enter a number to compute its factorial: ";
    cin>>n;
    int result = factorial(n);
    //cout<<n<<"! = "<<result<<endl;
    for(int i=0;i<=n;i++){
        cout<<factorial(i)<<" ";
    }
    return 0;
}