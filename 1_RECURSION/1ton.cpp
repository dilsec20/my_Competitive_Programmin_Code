// #include <bits/stdc++.h>
// using namespace std;

// vector<int> oneton(int n){
//     if(n==1) return {1};

//     vector<int> ans = oneton(n-1);
//     ans.push_back(n);
//     return ans;
// }
// int main(){
//     int n;
//     cout<<"Enter a number: ";
//     cin>>n;
//     vector<int> result = oneton(n);
    
//     for(int num : result){
//         cout<<num<<" ";
//     }
//     cout<<endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;


void fun(int n){
    if(n==0) return;
    
    
    fun(n-1);
    cout<<n<<" ";
}
int main()
{
    int n;
    cin>>n;
    fun(n);
    return 0;
}
