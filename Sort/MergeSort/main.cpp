#include <bits/stdc++.h>
using namespace std;

// Hàm trộn hai mảng con đã sắp xếp
// left: chỉ số bắt đầu của mảng con thứ nhất
// mid: chỉ số kết thúc của mảng con thứ nhất (và mid + 1 là bắt đầu của mảng con thứ hai)
// right: chỉ số kết thúc của mảng con thứ hai
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Kích thước mảng con thứ nhất
    int n2 = right - mid;    // Kích thước mảng con thứ hai

    // Tạo các mảng tạm thời để lưu trữ các phần tử
    vector<int> L(n1);
    vector<int> R(n2);

    // Sao chép dữ liệu vào các mảng tạm thời L[] và R[]
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    // Trộn các mảng tạm thời trở lại arr[left..right]
    int i = 0; // Chỉ số ban đầu của mảng con thứ nhất
    int j = 0; // Chỉ số ban đầu của mảng con thứ hai
    int k = left; // Chỉ số ban đầu của mảng gộp (arr)

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Sao chép các phần tử còn lại của L[] (nếu có)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sao chép các phần tử còn lại của R[] (nếu có)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Hàm đệ quy thực hiện Merge Sort
// arr: Mảng cần sắp xếp
// left: Chỉ số bắt đầu của mảng con hiện tại
// right: Chỉ số kết thúc của mảng con hiện tại
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) { // Điều kiện dừng: Mảng con chỉ có 0 hoặc 1 phần tử
        return;
    }

    int mid = left + (right - left) / 2; // Tìm điểm giữa để chia mảng

    // Gọi đệ quy để sắp xếp nửa bên trái
    mergeSort(arr, left, mid);
    // Gọi đệ quy để sắp xếp nửa bên phải
    mergeSort(arr, mid + 1, right);

    // Trộn hai nửa đã sắp xếp lại với nhau
    merge(arr, left, mid, right);
}

// Hàm để in mảng
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Mang ban dau: ";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Mang sau khi sap xep tron (Merge Sort): ";
    printArray(arr); // Kết quả: 5 6 7 11 12 13

    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10};
    cout << "Mang ban dau: ";
    printArray(arr2);
    mergeSort(arr2, 0, arr2.size() - 1);
    cout << "Mang sau khi sap xep tron (Merge Sort): ";
    printArray(arr2); // Kết quả: 3 9 10 27 38 43 82

    return 0;
}