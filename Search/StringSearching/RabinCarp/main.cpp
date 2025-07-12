#include <iostream>
#include <string>
#include <vector>
#include <cmath> // Để sử dụng pow hoặc tính lũy thừa

// Cài đặt thuật toán tìm kiếm xâu Rabin-Karp
std::vector<int> rabinKarpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> found_indices; // Danh sách các chỉ số tìm thấy

    int n = text.length();         // Độ dài xâu văn bản
    int m = pattern.length();      // Độ dài xâu mẫu

    // Xử lý các trường hợp đặc biệt
    if (m == 0) { // Xâu mẫu rỗng thì luôn được tìm thấy ở mọi vị trí
        for (int i = 0; i <= n; ++i) found_indices.push_back(i);
        return found_indices;
    }
    if (n == 0 || n < m) { // Văn bản rỗng hoặc ngắn hơn xâu mẫu, không thể tìm thấy
        return found_indices;
    }

    // --- Tham số cho hàm băm ---
    int d = 256; // Kích thước bảng chữ cái (ví dụ: 256 cho ASCII)
    int q = 101; // Một số nguyên tố lớn (để giảm thiểu va chạm băm)

    // h = d^(m-1) % q. Giá trị của d^(m-1) mod q, được dùng để loại bỏ ký tự đầu tiên
    int h = 1;
    for (int i = 0; i < m - 1; ++i) {
        h = (h * d) % q;
    }

    // --- Tính giá trị băm cho Pattern và đoạn con đầu tiên của Text ---
    int pattern_hash = 0;
    int text_window_hash = 0;

    for (int i = 0; i < m; ++i) {
        pattern_hash = (d * pattern_hash + pattern[i]) % q;
        text_window_hash = (d * text_window_hash + text[i]) % q;
    }

    // --- Duyệt qua văn bản và thực hiện tìm kiếm ---
    // i là chỉ số bắt đầu của cửa sổ hiện tại trong văn bản
    for (int i = 0; i <= n - m; ++i) {
        // Nếu giá trị băm khớp, tiến hành kiểm tra xác minh
        if (pattern_hash == text_window_hash) {
            // Kiểm tra xác minh (ký tự từng ký tự) để xử lý va chạm băm
            bool match = true;
            for (int j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                found_indices.push_back(i); // Tìm thấy khớp
            }
        }

        // Tính toán giá trị băm của đoạn con tiếp theo bằng rolling hash
        // Chỉ thực hiện nếu chưa phải là đoạn con cuối cùng
        if (i < n - m) {
            // Loại bỏ ký tự đầu tiên của cửa sổ cũ và thêm ký tự mới vào cuối
            text_window_hash = (d * (text_window_hash - text[i] * h) + text[i + m]) % q;

            // Đảm bảo giá trị băm không âm (trong C++, % có thể trả về âm với số âm)
            if (text_window_hash < 0) {
                text_window_hash = (text_window_hash + q);
            }
        }
    }
    return found_indices;
}

// Hàm trợ giúp để in kết quả
void print_results(const std::string& text, const std::string& pattern, const std::vector<int>& indices) {
    std::cout << "Van ban: \"" << text << "\"\n";
    std::cout << "Xau mau: \"" << pattern << "\"\n";
    if (indices.empty()) {
        std::cout << "Khong tim thay xau mau.\n";
    } else {
        std::cout << "Tim thay xau mau tai cac chi so bat dau: ";
        for (int index : indices) {
            std::cout << index << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------\n";
}

int main() {
    std::cout << "--- Thuat toan Rabin-Karp (Tim kiem xau) ---\n\n";

    print_results("GEEKSFORGEEKS", "GEEKS", rabinKarpSearch("GEEKSFORGEEKS", "GEEKS"));
    print_results("ABABDABACDABABCABAB", "ABAB", rabinKarpSearch("ABABDABACDABABCABAB", "ABAB"));
    print_results("ABCDEF", "XYZ", rabinKarpSearch("ABCDEF", "XYZ"));
    print_results("AAAAA", "AAA", rabinKarpSearch("AAAAA", "AAA"));
    print_results("BANANA", "ANA", rabinKarpSearch("BANANA", "ANA"));
    print_results("HELLO WORLD", "WORLD", rabinKarpSearch("HELLO WORLD", "WORLD"));
    
    // Các trường hợp đặc biệt
    print_results("test", "", rabinKarpSearch("test", ""));
    print_results("", "test", rabinKarpSearch("", "test"));
    print_results("", "", rabinKarpSearch("", ""));

    // Ví dụ với ký tự khác (ASCII values)
    print_results("The quick brown fox jumps over the lazy dog", "quick", rabinKarpSearch("The quick brown fox jumps over the lazy dog", "quick"));

    return 0;
}