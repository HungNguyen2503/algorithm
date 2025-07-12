#include <bits/stdc++.h>
using namespace std;

vector<int> enterArray(){
    vector<int> arr;
    int n;
    cout<<"number of elements in array:";
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cout<<"number "<<i+1<<":";
        cin>>temp;
        arr.push_back(temp);
    }
    return arr;
}

void showArray(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
}

int countOccurrences(vector<int> arr, int value){
    int result = 0;
    for(const auto& v : arr){
        if(v==value) result++;
    }
    return result;
}

int maxEven(vector<int> arr){
    int max = -99999;
    for(const auto& v : arr){
        if(v > max && v%2==0) max = v;
    }
    return max;
}

int minOdd(vector<int> arr){
    int min = 99999;
    for(const auto& v : arr){
        if(v < min && v%2!=0) min = v;
    }
    return min;
}

int main(){
    vector<int> arr = enterArray();
    int value;

    showArray(arr);
    cout<<"enter value: ";
    cin>>value;
    cout<<"number of occurrences: "<<countOccurrences(arr, value)<<endl;
    cout<<"Max even             : "<<maxEven(arr)<<endl;
    cout<<"Min odd              : "<<minOdd(arr)<<endl;

    return 0;
}