#include <bits/stdc++.h>
using namespace std;

// long long  fibonacci(long long  n){
//     if(n<=1) return n;
//     return fibonacci(n-1) + fibonacci(n-2);
// }

// int  main(){
//     long long n;
//     cout<<"Enter a number: ";
//     cin>>n;
//     // for(long long  i=0;i<n;i++){
//     //     cout<<fibonacci(i)<<" ";
//     // }
//      int result = fibonacci(n);
//      cout<<"Fibonacci of "<<n<<" is "<<result<<endl;
//     return 0;
// }

vector<int> fib_sequence(int n){
    if(n==0) return {};
    if(n==1) return {0};
    if(n==2) return {0, 1};

    vector<int> seq = fib_sequence(n-1);
    int next_fib = seq[n-2] + seq[n-3];
    seq.push_back(next_fib);
    return seq;
}
int main(){
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    vector<int> result = fib_sequence(n);
    
    // for(int num : result){
    //     cout<<num<<" ";
    // }
    
    cout<<"Fibonacci of "<<n<<" is "<<result[n-1]<<endl;
    return 0;
}