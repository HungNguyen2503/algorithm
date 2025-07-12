#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> arr, int value)
{
    int left = 0, right = arr.size() - 1, mid;

    do
    {
        mid = (left + right) / 2;
        if (value == arr[mid])
        {
            return mid;
        }
        else if (value < arr[mid])
        {
            right = mid-1;
        }
        else
        {
            left = mid+1;
        }
    }while (left <= right);

    return -1;
}

int binarySearchRecursion(vector<int> arr, int value, int left, int right){
    if(left>right){
        return -1;
    }
    int mid = (left+right)/2;
    if(arr[mid]==value) return mid;
    else if(value < arr[mid]) return binarySearchRecursion(arr, value, left, mid-1);
    else return binarySearchRecursion(arr, value, mid+1, right);
}

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6};
    cout<<binarySearch(a, 6)<<endl;
    cout<<binarySearchRecursion(a, 6, 0, a.size()-1);
    return 0;
}