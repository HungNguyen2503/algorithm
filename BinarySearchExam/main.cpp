#include <bits/stdc++.h>
using namespace std;

vector<float> enterArray(){
    vector<float> arr;
    int n;
    cout<<"number of elements in array:";
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        float temp;
        cout<<"number "<<i+1<<":";
        cin>>temp;
        arr.push_back(temp);
    }
    return arr;
}

void showArray(vector<float> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
}

int searchBinaryValue(vector<float> arr, float value){
    int mid = (arr.size()-1)/2;
    int left = 0, right=arr.size();

    do{
        if(arr[mid]==value) return mid;
        else if(arr[mid] > value) right = mid--;
        else left = mid++;
    }while(left<=right);
    return -1;
}

int main(){
    vector<float> arr = enterArray();
    showArray(arr);
    float value;
    cout<<"enter value search:";
    cin>>value;
    cout<<searchBinaryValue(arr, value);

    return 0;
}