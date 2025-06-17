#include<bits/stdc++.h>

using namespace std;

int integerOfLogarithm(int n){
    cout<<n/2<<endl;
    if(n<2){
        return 0;
    }
    return 1 + integerOfLogarithm(n/2);
}

int main(){

    cout<<integerOfLogarithm(10);
    return 0;
}