#include <bits/stdc++.h>
using namespace std;

int linearSearch(vector<int> arr, int value){
    for (int i = 0; i < arr.size() ; i++){
        if(arr.at(i) == value){
            return i;
        }
    }
    return -1;
}

int linearSearchFor(vector<int> arr, int value){
    int i;
    for(i=0; i<arr.size() && arr.at(i) != value; i++);
    if(i == arr.size()) return -1;
    return i;
}

int main(){
    srand(time(NULL));
    vector<int> arr;
    int n = 10;
    for(int i=0 ;i<n; i++){
        arr.push_back(rand()%10000);
    }

    for (int i = 0; i < arr.size() ; i++){
        cout<<arr.at(i)<<endl;
    }
    cout<<endl;
    cout<<linearSearch(arr, 50)<<endl;
    cout<<linearSearchFor(arr, 4)<<endl;

    return 0;
}