#include <iostream>
#include <vector>
#include <algorithm> // Để sử dụng std::sort
#include <iomanip>   // Để định dạng đầu ra số thập phân

// Hàm để in mảng (có thể dùng cho float)
void printArray(const std::vector<float>& arr) {
    for (float x : arr) {
        std::cout << std::fixed << std::setprecision(2) << x << " "; // Định dạng 2 chữ số thập phân
    }
    std::cout << std::endl;
}

void bucketSort(std::vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return; // Mảng rỗng hoặc chỉ có 1 phần tử đã sắp xếp

    // 1. Tạo các thùng (buckets)
    // Giả sử có 10 thùng. Mỗi thùng là một vector để chứa các phần tử.
    // Số lượng thùng có thể được điều chỉnh tùy thuộc vào phạm vi và phân bố dữ liệu.
    const int NUM_BUCKETS = 10;
    std::vector<std::vector<float>> buckets(NUM_BUCKETS);

    // 2. Phân phối các phần tử vào các thùng tương ứng
    // Các phần tử từ 0.0 đến 0.99... sẽ được phân vào 10 thùng.
    // Ví dụ: 0.12 -> index 1, 0.89 -> index 8
    for (int i = 0; i < n; ++i) {
        int bucket_index = static_cast<int>(NUM_BUCKETS * arr[i]); // Công thức để tính chỉ số thùng
        buckets[bucket_index].push_back(arr[i]);
    }

    // 3. Sắp xếp riêng lẻ các phần tử bên trong mỗi thùng
    // Sử dụng std::sort (hoặc Insertion Sort nếu số lượng phần tử trong thùng nhỏ)
    for (int i = 0; i < NUM_BUCKETS; ++i) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // 4. Hợp nhất các phần tử từ các thùng lại để tạo mảng đã sắp xếp
    int index = 0;
    for (int i = 0; i < NUM_BUCKETS; ++i) {
        for (float val : buckets[i]) {
            arr[index++] = val;
        }
    }
}

int main() {
    std::vector<float> arr = {0.89, 0.45, 0.62, 0.12, 0.33, 0.76};
    std::cout << "Mang ban dau: ";
    printArray(arr);

    bucketSort(arr);

    std::cout << "Mang sau khi sap xep theo thung (Bucket Sort): ";
    printArray(arr); // Kết quả: 0.12 0.33 0.45 0.62 0.76 0.89

    std::vector<float> arr2 = {0.41, 0.82, 0.03, 0.49, 0.37, 0.61, 0.19, 0.55};
    std::cout << "Mang ban dau: ";
    printArray(arr2);
    bucketSort(arr2);
    std::cout << "Mang sau khi sap xep theo thung (Bucket Sort): ";
    printArray(arr2); // Kết quả: 0.03 0.19 0.37 0.41 0.49 0.55 0.61 0.82

    return 0;
}