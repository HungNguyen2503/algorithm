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

void findClosestToAverage(vector<int> arr)
{
    float average = accumulate(arr.begin(), arr.end(), 0.0f)/arr.size();
    cout<<"Average: "<<average;
    int near = 0;
    float absoluteDifference = fabs(arr[0] - average);
    for(int i=1; i<arr.size(); i++){
        if(fabs(arr[i] - average) < absoluteDifference){
            absoluteDifference = fabs(arr[i] -average);
            near = i;
        }
    }
    cout<<"Closest To Average: "<<arr[near];
}
int main(){
    vector<int> arr;
    arr = enterArray();
    showArray(arr);
    findClosestToAverage(arr);
    return 0;
}