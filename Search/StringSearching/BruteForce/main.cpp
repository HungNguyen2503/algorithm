#include <iostream> // Dành cho std::cout, std::endl
#include <string>   // Dành cho std::string
#include <vector>   // Dành cho std::vector

// Hàm tìm kiếm xâu mẫu bằng thuật toán vét cạn
// text: xâu văn bản đầu vào
// pattern: xâu mẫu cần tìm
// Trả về một vector chứa tất cả các chỉ số bắt đầu mà xâu mẫu được tìm thấy trong văn bản
std::vector<int> bruteForceSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> foundIndices; // Lưu trữ các chỉ số tìm thấy

    int n = text.length();    // Độ dài của xâu văn bản
    int m = pattern.length(); // Độ dài của xâu mẫu

    // Xử lý các trường hợp đặc biệt
    if (m == 0) { // Nếu xâu mẫu rỗng, coi như tìm thấy ở mọi vị trí (hoặc vị trí đầu tiên nếu văn bản rỗng)
        for (int i = 0; i < n; ++i) {
            foundIndices.push_back(i);
        }
        if (n == 0) { // Cả text và pattern đều rỗng
            foundIndices.push_back(0);
        }
        return foundIndices;
    }
    if (n == 0 || n < m) { // Nếu văn bản rỗng hoặc ngắn hơn xâu mẫu, không thể tìm thấy
        return foundIndices;
    }

    // Duyệt qua tất cả các vị trí bắt đầu có thể của xâu mẫu trong văn bản
    // i là chỉ số bắt đầu của xâu mẫu trong text
    for (int i = 0; i <= n - m; ++i) {
        int j; // j là chỉ số để duyệt qua các ký tự của xâu mẫu

        // So sánh từng ký tự của xâu mẫu với các ký tự tương ứng trong văn bản
        for (j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                break; // Ký tự không khớp, không cần so sánh tiếp
            }
        }

        // Nếu vòng lặp bên trong kết thúc vì j == m, nghĩa là toàn bộ xâu mẫu đã khớp
        if (j == m) {
            foundIndices.push_back(i); // Thêm chỉ số bắt đầu tìm thấy vào danh sách
        }
    }
    return foundIndices;
}

// Hàm trợ giúp để in kết quả tìm kiếm
void printResults(const std::string& text, const std::string& pattern, const std::vector<int>& indices) {
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
    std::cout << "--- Thuat toan Vet can (Brute-Force String Matching) ---\n\n";

    // Ví dụ 1: Tìm thấy nhiều lần
    printResults("ABABDABACDABABCABAB", "ABAB", bruteForceSearch("ABABDABACDABABCABAB", "ABAB"));

    // Ví dụ 2: Không tìm thấy
    printResults("ABCDEF", "XYZ", bruteForceSearch("ABCDEF", "XYZ"));

    // Ví dụ 3: Xâu lặp lại, thể hiện nhược điểm về hiệu suất
    printResults("AAAAA", "AAA", bruteForceSearch("AAAAA", "AAA"));

    // Ví dụ 4: Tìm thấy ở giữa
    printResults("Hello World", "World", bruteForceSearch("Hello World", "World"));
    
    // Ví dụ 5: Xâu mẫu rỗng
    printResults("test string", "", bruteForceSearch("test string", "")); 

    // Ví dụ 6: Xâu văn bản rỗng
    printResults("", "pattern", bruteForceSearch("", "pattern")); 

    // Ví dụ 7: Cả hai đều rỗng
    printResults("", "", bruteForceSearch("", "")); 

    return 0;
}