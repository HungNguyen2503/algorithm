#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) { // Duyệt từ phần tử thứ 2 (chỉ số 1)
        int key = arr[i]; // Lấy phần tử hiện tại để chèn
        int j = i - 1;

        // Di chuyển các phần tử của arr[0..i-1], lớn hơn key,
        // đến một vị trí sau vị trí hiện tại của chúng
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // Chèn key vào đúng vị trí
    }
}

void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6};
    cout << "Mang ban dau: ";
    printArray(arr);

    insertionSort(arr);

    cout << "Mang sau khi sap xep chen: ";
    printArray(arr); // Kết quả: 5 6 11 12 13

    return 0;
}