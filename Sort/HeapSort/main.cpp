#include <bits/stdc++.h>
using namespace std;

// Hàm heapify: Duy trì thuộc tính Max-Heap cho một cây con gốc tại 'i'
// n: Kích thước của heap (mảng con cần heapify)
// i: Chỉ số của nút gốc trong cây con cần heapify
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Khởi tạo nút lớn nhất làm gốc
    int left = 2 * i + 1;  // Chỉ số con trái
    int right = 2 * i + 2; // Chỉ số con phải

    // Nếu con trái lớn hơn gốc
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Nếu con phải lớn hơn phần tử lớn nhất hiện tại
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Nếu phần tử lớn nhất không phải là gốc (có sự thay đổi)
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Đệ quy heapify cây con bị ảnh hưởng
        heapify(arr, n, largest);
    }
}

// Hàm chính thực hiện Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Giai đoạn 1: Xây dựng Max-Heap (tái sắp xếp mảng)
    // Duyệt từ nút không phải lá đầu tiên trở về gốc.
    // Nút không phải lá cuối cùng có chỉ số là (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    // Giai đoạn 2: Trích xuất từng phần tử từ heap
    // Duyệt từ phần tử cuối cùng của heap về đầu
    for (int i = n - 1; i > 0; --i) {
        // Hoán đổi gốc (phần tử lớn nhất) với phần tử cuối cùng
        swap(arr[0], arr[i]);

        // Gọi heapify trên heap đã giảm kích thước
        heapify(arr, i, 0); // Kích thước heap hiện tại là 'i' (phần tử cuối cùng đã được đặt vào đúng vị trí)
    }
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

    heapSort(arr);

    cout << "Mang sau khi sap xep dong (Heap Sort): ";
    printArray(arr); // Kết quả: 5 6 7 11 12 13

    vector<int> arr2 = {4, 10, 3, 5, 1};
    cout << "Mang ban dau: ";
    printArray(arr2);
    heapSort(arr2);
    cout << "Mang sau khi sap xep dong (Heap Sort): ";
    printArray(arr2); // Kết quả: 1 3 4 5 10

    return 0;
}