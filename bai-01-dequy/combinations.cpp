#include <bits/stdc++.h>

using namespace std;

int combinate(int n, int k){
    if(k==0 || n==k){
        return 1;
    }
    return combinate(n-1, k-1) + combinate(n-1, k);
}

int main(){
    cout<<combinate(5,3);
    return 0;
}