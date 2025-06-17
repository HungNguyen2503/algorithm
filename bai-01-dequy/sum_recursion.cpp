#include <bits/stdc++.h>
using namespace std;

int sum(int n){
    if(n==1){
        return n;
    }
    return n + sum(n-1);
}

void reverseTheDigits(int n){
    if(n==0){
        return;
    }
    cout<<n%10;
    reverseTheDigits(n/10);
}

int sumOfDigits(int n){
    if(n==0){
        return 0;
    }
    return n%10 + sumOfDigits(n/10);
}

int main(){
    int n = 100;

    cout<<sum(n)<<endl;
    reverseTheDigits(100);
    cout<<endl;
    cout<<sumOfDigits(100);


    return 0;
}