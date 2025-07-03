#include <bits/stdc++.h>
using namespace std;

// Hàm phân hoạch (Lomuto Partition Scheme)
// arr: Mảng cần phân hoạch
// low: Chỉ số bắt đầu của mảng con
// high: Chỉ số kết thúc của mảng con (phần tử này được chọn làm chốt)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Chọn phần tử cuối cùng làm chốt
    int i = (low - 1); // Chỉ số của phần tử nhỏ hơn (dùng để theo dõi vị trí của phần tử cuối cùng nhỏ hơn chốt)

    for (int j = low; j <= high - 1; ++j) {
        // Nếu phần tử hiện tại nhỏ hơn hoặc bằng chốt
        if (arr[j] <= pivot) {
            i++; // Tăng chỉ số của phần tử nhỏ hơn
            swap(arr[i], arr[j]); // Hoán đổi arr[i] và arr[j]
        }
    }
    // Đặt chốt vào đúng vị trí của nó (sau tất cả các phần tử nhỏ hơn)
    swap(arr[i + 1], arr[high]);
    return (i + 1); // Trả về chỉ số của chốt sau khi phân hoạch
}

// Hàm đệ quy thực hiện Quick Sort
// arr: Mảng cần sắp xếp
// low: Chỉ số bắt đầu của mảng con hiện tại
// high: Chỉ số kết thúc của mảng con hiện tại
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) { // Điều kiện dừng: Mảng con có ít nhất 2 phần tử
        // pi là chỉ số phân hoạch, arr[pi] bây giờ nằm ở đúng vị trí
        int pi = partition(arr, low, high);

        // Sắp xếp đệ quy các phần tử trước và sau phân hoạch
        quickSort(arr, low, pi - 1);  // Mảng con bên trái của chốt
        quickSort(arr, pi + 1, high); // Mảng con bên phải của chốt
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
    vector<int> arr = {10, 80, 30, 90, 40, 50, 70};
    cout << "Mang ban dau: ";
    printArray(arr);

    quickSort(arr, 0, arr.size() - 1);

    cout << "Mang sau khi sap xep nhanh (Quick Sort): ";
    printArray(arr); // Kết quả: 10 30 40 50 70 80 90

    vector<int> arr2 = {5, 4, 3, 2, 1};
    cout << "Mang ban dau: ";
    printArray(arr2);
    quickSort(arr2, 0, arr2.size() - 1);
    cout << "Mang sau khi sap xep nhanh (Quick Sort): ";
    printArray(arr2); // Kết quả: 1 2 3 4 5

    return 0;
}