#include<bits/stdc++.h>
using namespace std;

void seriesHelper(int current, int k, vector<int>& result){
    
    result.push_back(current);
    if(current<=0)return;
    seriesHelper(current - k, k, result);
    result.push_back(current);
}


vector<int> series(int n, int k){
    vector<int> result;
    seriesHelper(n, k,result);  
    return result;
    
}
int main(){
    int n,k;
    cin>>n>>k;
    vector<int> ans = series(n, k);
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    return 0;   
}