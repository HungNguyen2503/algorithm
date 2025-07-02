#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) { // Duyệt qua từng phần tử để đặt vào đúng vị trí
        int min_idx = i; // Giả sử phần tử hiện tại là nhỏ nhất

        // Tìm phần tử nhỏ nhất trong phần chưa sắp xếp (từ i+1 đến cuối mảng)
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Hoán đổi phần tử nhỏ nhất tìm được với phần tử đầu tiên của phần chưa sắp xếp
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    cout << "Mang ban dau: ";
    printArray(arr);

    selectionSort(arr);

    cout << "Mang sau khi sap xep lua chon: ";
    printArray(arr); // Kết quả: 11 12 22 25 64

    return 0;
}