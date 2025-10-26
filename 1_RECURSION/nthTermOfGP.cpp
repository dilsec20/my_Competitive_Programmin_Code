#include <bits/stdc++.h>
using namespace std;

// int nthTermOfGP(int n, int a, int r){
//     const int MOD = 1000000007;
//     n = n % MOD;
//     a = a % MOD;             
//     if(n==1)return a;
//     return r * nthTermOfGP(n-1, a, r);
// }
// int main(){
//     int n,a,r;
//     cin>>n>>a>>r;
//     cout<<nthTermOfGP(n, a, r);
//     return 0;   
// }


const int MOD = 1000000007;


long long modPow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int nthTermOfGP(int n, int a, int r) {
    
    long long term = (1LL * a * modPow(r, n - 1, MOD)) % MOD;
    return term;
}




int main(){
    int n,a,r;
    cin>>n>>a>>r;
    cout<<nthTermOfGP(n, a, r);
    return 0;   
}