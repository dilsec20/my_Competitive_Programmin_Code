#include <bits/stdc++.h>
using namespace std;

char findGender(int n, int k){
    if(n==1 || k==1)return 'M';

    char parentGneder = findGender(n-1, (k+1)/2);
    if(parentGneder == 'M'){
        if(k%2==1)return 'M';
        else return 'F';
    }
    else{
        if(k%2==1)return 'F';
        else return 'M';
    }
}
int main(){
    int n, k;
    cin>>n>>k;
    cout<<findGender(n, k);
    if(findGender(n, k)=='M')cout<<"ale";
    else cout<<"emale";
    return 0;   
}