#include <iostream>
#include <vector>
#include <algorithm> // Để sử dụng std::max_element nếu muốn tìm max

// Hàm để in mảng
void printArray(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void countingSort(std::vector<int>& arr) {
    int n = arr.size();

    // 1. Tìm giá trị lớn nhất (max_val) trong mảng để xác định kích thước mảng count
    if (n == 0) return; // Xử lý trường hợp mảng rỗng
    int max_val = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    // Hoặc sử dụng std::max_element nếu bạn muốn:
    // int max_val = *std::max_element(arr.begin(), arr.end());

    // 2. Tạo mảng count và khởi tạo bằng 0
    // Kích thước của mảng count sẽ là max_val + 1 (để chứa các số từ 0 đến max_val)
    std::vector<int> count(max_val + 1, 0);

    // 3. Đếm số lần xuất hiện của mỗi phần tử trong mảng arr
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }

    // 4. Chuyển đổi mảng count thành mảng vị trí tích lũy
    // count[i] bây giờ chứa số lượng các phần tử nhỏ hơn hoặc bằng i
    for (int i = 1; i <= max_val; ++i) {
        count[i] += count[i - 1];
    }

    // 5. Tạo mảng output và xây dựng mảng đã sắp xếp
    // Duyệt mảng đầu vào TỪ CUỐI VỀ ĐẦU để đảm bảo tính ổn định (stable sort)
    std::vector<int> output(n);
    for (int i = n - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i]; // Đặt phần tử vào đúng vị trí của nó
        count[arr[i]]--; // Giảm số lượng để xử lý các phần tử trùng lặp
    }

    // 6. Sao chép các phần tử đã sắp xếp từ output về lại arr
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

int main() {
    std::vector<int> arr = {1, 4, 1, 2, 7, 5, 2};
    std::cout << "Mang ban dau: ";
    printArray(arr);

    countingSort(arr);

    std::cout << "Mang sau khi sap xep dem (Counting Sort): ";
    printArray(arr); // Kết quả: 1 1 2 2 4 5 7

    std::vector<int> arr2 = {9, 2, 5, 1, 8, 2, 3, 5, 7, 9};
    std::cout << "Mang ban dau: ";
    printArray(arr2);
    countingSort(arr2);
    std::cout << "Mang sau khi sap xep dem (Counting Sort): ";
    printArray(arr2); // Kết quả: 1 2 2 3 5 5 7 8 9 9

    return 0;
}