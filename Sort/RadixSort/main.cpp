#include <iostream>
#include <vector>
#include <algorithm> // Để sử dụng std::max_element nếu cần

// Hàm tiện ích để in mảng
void printArray(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// Hàm tìm giá trị lớn nhất trong mảng
int getMax(const std::vector<int>& arr) {
    int max_val = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

// Hàm Counting Sort được sửa đổi để sắp xếp các phần tử dựa trên chữ số được xác định bởi 'exp'
// exp: Biểu thị vị trí chữ số (1 cho đơn vị, 10 cho chục, 100 cho trăm, v.v.)
void countSortForRadix(std::vector<int>& arr, int n, int exp) {
    std::vector<int> output(n); // Mảng đầu ra tạm thời
    std::vector<int> count(10, 0); // Mảng đếm cho các chữ số từ 0 đến 9

    // Đếm số lần xuất hiện của các chữ số ở vị trí hiện tại
    for (int i = 0; i < n; ++i) {
        count[(arr[i] / exp) % 10]++;
    }

    // Chuyển đổi count[i] thành vị trí tích lũy
    // count[i] bây giờ chứa vị trí thực tế của chữ số này trong mảng output
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Xây dựng mảng output
    // Duyệt từ cuối về đầu để đảm bảo tính ổn định
    for (int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Sao chép các phần tử đã sắp xếp từ output trở lại arr
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

// Hàm chính thực hiện Radix Sort
void radixSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return; // Mảng rỗng hoặc chỉ có 1 phần tử đã sắp xếp

    // Tìm giá trị lớn nhất để biết số chữ số tối đa cần sắp xếp
    int max_val = getMax(arr);

    // Thực hiện Counting Sort cho từng chữ số.
    // exp là 10^i, nơi i là chỉ số chữ số hiện tại
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        countSortForRadix(arr, n, exp);
    }
}

int main() {
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    std::cout << "Mang ban dau: ";
    printArray(arr);

    radixSort(arr);

    std::cout << "Mang sau khi sap xep co so (Radix Sort): ";
    printArray(arr); // Kết quả: 2 24 45 66 75 90 170 802

    std::vector<int> arr2 = {329, 457, 657, 839, 436, 720, 355};
    std::cout << "Mang ban dau: ";
    printArray(arr2);
    radixSort(arr2);
    std::cout << "Mang sau khi sap xep co so (Radix Sort): ";
    printArray(arr2); // Kết quả: 329 355 436 457 657 720 839

    return 0;
}