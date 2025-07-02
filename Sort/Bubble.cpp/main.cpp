#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped; // Biến cờ để kiểm tra xem có sự hoán đổi nào xảy ra trong lần duyệt không

    for (int i = 0; i < n - 1; ++i) { // Lặp qua tất cả các phần tử của mảng
        swapped = false; // Reset cờ cho mỗi lần duyệt
        for (int j = 0; j < n - 1 - i; ++j) { // Duyệt qua mảng để so sánh các cặp kề nhau
            if (arr[j] > arr[j + 1]) { // Nếu phần tử hiện tại lớn hơn phần tử tiếp theo
                swap(arr[j], arr[j + 1]); // Hoán đổi chúng
                swapped = true; // Đánh dấu là có sự hoán đổi
            }
        }
        // Nếu không có phần tử nào được hoán đổi trong lần duyệt này,
        // có nghĩa là mảng đã được sắp xếp, thoát vòng lặp
        if (swapped == false) {
            break;
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
    vector<int> arr = {5, 1, 4, 2, 8};
    cout << "Mang ban dau: ";
    printArray(arr);

    bubbleSort(arr);

    cout << "Mang sau khi sap xep noi bot: ";
    printArray(arr); // Kết quả: 1 2 4 5 8

    return 0;
}