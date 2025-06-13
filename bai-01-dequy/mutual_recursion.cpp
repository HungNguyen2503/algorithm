#include <iostream>
using namespace std;

bool isEven(int n);
bool isOdd(int n);

bool isEven(int n){
    if(n==0)
        return true;
    return isOdd(n-1);
}
bool isOdd(int n){
    return !isEven(n);
}


int main(){
    int n =9;
    bool kq = isEven(n);
    if(kq){
        cout<<n<< " la so chan";
    }else{
        cout<<n<< " la so le";
    }
    return 0;
}