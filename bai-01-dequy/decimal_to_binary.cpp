#include <bits/stdc++.h>

using namespace std;

string decimalToBinary(int n){
    if(n/2 == 0){
        return to_string(n % 2);
    }
    return decimalToBinary(n/2) + to_string(n%2);
}

int main(){
    int n = 13;
    if (n>0) {
        cout<<decimalToBinary(n);
    } else {
        cout << n << " is NOT a positive integer." << endl;
    }
}