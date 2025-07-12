#include <bits/stdc++.h>
using namespace std;

void print_array(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << "\t";
    }
    cout << endl;
}
void print_permutations(int arr[], int n, int i){
    int j, swap;
    print_array(arr, n);
    for (j=i+1; j < n; j++)
    {
        if(arr[i]>arr[j]){
            swap = arr[i];
            arr[i] = arr[j];
            arr[j] = swap;
        }
        print_permutations(arr, n, i+1);
    }
    
}
int main(){
    int arr[] = {10, 2, 3, 6, 9, 1, 7, 20, 8, 4, 5, 19, 16, 24, 8, 64, 22};
    int n =  sizeof(arr) / sizeof(arr[0]);
    print_permutations(arr, n, 0);
    return 0;
}