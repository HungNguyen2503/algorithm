#include <iostream>
#include <string>
#include <vector>
#include <map> // Để tạo bảng dịch chuyển (shift table) cho ký tự xấu

// Hàm tiền xử lý: Xây dựng bảng dịch chuyển Bad Character cho Boyer-Moore-Horspool
// badCharTable[c] = vị trí cuối cùng của ký tự 'c' trong pattern (tính từ cuối pattern)
// Ví dụ: pattern = "EXAMPLE" (m=7)
// badCharTable['E'] = 1 (vì E cuối cùng cách 1 vị trí so với cuối pattern)
// badCharTable['L'] = 2
// badCharTable['P'] = 3
// ...
// badCharTable['X'] = 4
// badCharTable['M'] = 5
// badCharTable['A'] = 6
// Nếu ký tự không có trong pattern, dịch chuyển bằng độ dài pattern (m)
std::map<char, int> computeBadCharTableHorspool(const std::string& pattern) {
    std::map<char, int> badCharTable;
    int m = pattern.length();

    // Mặc định cho mọi ký tự: dịch chuyển bằng độ dài pattern (m)
    // Nếu ký tự không có trong pattern, ta dịch chuyển cả pattern đi m vị trí
    for (int i = 0; i < 256; ++i) { // Giả định ký tự ASCII
        badCharTable[(char)i] = m;
    }

    // Cập nhật vị trí dịch chuyển thực tế cho các ký tự CÓ TRONG pattern
    // pattern[i] sẽ khớp với text. Dịch chuyển là (m-1-i)
    // Ví dụ: Pattern "ABC" (m=3)
    // C ở index 2 (m-1), dịch chuyển 3-1-2 = 0
    // B ở index 1, dịch chuyển 3-1-1 = 1
    // A ở index 0, dịch chuyển 3-1-0 = 2
    for (int i = 0; i < m - 1; ++i) { // Duyệt từ đầu đến ký tự thứ m-2 (ký tự cuối cùng của pattern không được bao gồm)
        badCharTable[pattern[i]] = m - 1 - i;
    }
    // Riêng ký tự cuối cùng của pattern, nếu có khớp, ta dịch chuyển m (để tìm khớp tiếp theo)
    // Trường hợp ký tự cuối cùng của pattern là độc nhất, không trùng với bất kỳ ký tự nào trước đó
    // trong pattern (ngoại trừ chính nó) thì bảng này ổn.
    // Nếu có trùng lặp, cần cẩn thận hơn để đảm bảo dịch chuyển ít nhất 1.
    // Cách chuẩn: shift = m - 1 - index_of_char
    
    // Một cách phổ biến khác:
    // badCharTable[c] = (index của c trong pattern từ cuối lên, +1)
    // hoặc đơn giản là vị trí cuối cùng của c trong pattern
    
    // Cách chuẩn và đơn giản nhất cho Horspool:
    // badCharTable[c] = m (default)
    // badCharTable[pattern[i]] = m - 1 - i (for i from 0 to m-2)
    // pattern[m-1] is not in the table, it defaults to m (full shift)
    
    // Final simpler and correct bad char table for Horspool:
    // Stores the distance from the end of the pattern (m-1) to the last occurrence of char in pattern[0...m-2]
    // If char is not present in pattern[0...m-2], default shift is m.
    std::map<char, int> bcTable;
    for (int i = 0; i < 256; ++i) {
        bcTable[(char)i] = m; // Default shift for any char not in pattern or last char of pattern
    }
    for (int i = 0; i < m - 1; ++i) { // For all chars except the last one in pattern
        bcTable[pattern[i]] = m - 1 - i;
    }
    return bcTable;
}

// Hàm tìm kiếm xâu mẫu bằng thuật toán Boyer-Moore-Horspool
std::vector<int> boyerMooreHorspoolSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> foundIndices;
    int n = text.length();
    int m = pattern.length();

    // Xử lý các trường hợp đặc biệt
    if (m == 0) { // Xâu mẫu rỗng thì luôn được tìm thấy ở mọi vị trí
        for (int i = 0; i < n; ++i) foundIndices.push_back(i);
        if (n == 0) foundIndices.push_back(0);
        return foundIndices;
    }
    if (n == 0 || n < m) { // Văn bản rỗng hoặc ngắn hơn xâu mẫu
        return foundIndices;
    }

    // Tiền xử lý: Xây dựng bảng Bad Character
    std::map<char, int> badCharTable = computeBadCharTableHorspool(pattern);

    int i = 0; // i là chỉ số của cửa sổ so sánh trong văn bản
    while (i <= (n - m)) {
        int j = m - 1; // j là chỉ số để duyệt pattern từ cuối lên

        // So sánh pattern với text từ phải sang trái
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        // Nếu j < 0, nghĩa là toàn bộ pattern đã khớp
        if (j < 0) {
            foundIndices.push_back(i); // Lưu chỉ số bắt đầu tìm thấy
            // Dịch chuyển pattern để tìm kiếm các khớp tiếp theo.
            // Dịch chuyển là giá trị từ bảng badCharTable dựa trên ký tự cuối cùng của cửa sổ
            // hoặc 1 nếu mẫu rỗng
            i += (m > 0 ? badCharTable[text[i + m - 1]] : 1);
        } else {
            // Ký tự không khớp tại text[i+j] và pattern[j]
            // Dịch chuyển mẫu dựa trên Bad Character Heuristic
            // char_at_text_end: ký tự ở cuối cửa sổ hiện tại trong văn bản
            char char_at_text_end = text[i + m - 1];
            
            // Bước dịch chuyển là lấy giá trị từ bảng badCharTable cho ký tự ở cuối cửa sổ
            // Đảm bảo dịch chuyển ít nhất 1 vị trí
            int shift = badCharTable[char_at_text_end];
            if (shift < 1) shift = 1; // Trường hợp ký tự không khớp là ký tự cuối của pattern và nó khớp.

            // Một cách khác để tính shift:
            // if pattern[j] != text[i+j]: // This is the mismatch character
            //     shift = max(1, j - badCharTable[text[i+j]])
            // Nhưng Horspool đơn giản hơn: chỉ quan tâm đến ký tự cuối cùng của cửa sổ.
            
            // Theo định nghĩa Horspool, ta luôn dịch chuyển dựa trên ký tự ở text[i + m - 1]
            // trừ đi vị trí của ký tự đó trong pattern (nếu có)
            // hoặc shift = m nếu không có.
            
            // Correct Horspool shift logic (using badCharTable from computeBadCharTableHorspool):
            // The shift amount depends only on the character aligned with pattern's last character.
            i += badCharTable[char_at_text_end];
        }
    }
    return foundIndices;
}

// Hàm trợ giúp để in kết quả (tái sử dụng)
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
    std::cout << "--- Thuat toan Boyer-Moore-Horspool (Ngan gon, hieu qua) ---\n\n";

    print_results("ABABDABACDABABCABAB", "ABAB", boyerMooreHorspoolSearch("ABABDABACDABABCABAB", "ABAB"));
    print_results("ABCDEF", "XYZ", boyerMooreHorspoolSearch("ABCDEF", "XYZ"));
    print_results("AAAAA", "AAA", boyerMooreHorspoolSearch("AAAAA", "AAA"));
    print_results("GEEKSFORGEEKS", "GEEKS", boyerMooreHorspoolSearch("GEEKSFORGEEKS", "GEEKS"));
    print_results("HELLO WORLD", "WORLD", boyerMooreHorspoolSearch("HELLO WORLD", "WORLD"));
    print_results("AABAACAADAABAABAA", "AABA", boyerMooreHorspoolSearch("AABAACAADAABAABAA", "AABA"));
    print_results("BANANA", "ANA", boyerMooreHorspoolSearch("BANANA", "ANA")); // Test case điển hình cho BMH
    print_results("THIS IS A TEST TEXT", "TEST", boyerMooreHorspoolSearch("THIS IS A TEST TEXT", "TEST"));
    
    // Các trường hợp đặc biệt
    print_results("test", "", boyerMooreHorspoolSearch("test", ""));
    print_results("", "test", boyerMooreHorspoolSearch("", "test"));
    print_results("", "", boyerMooreHorspoolSearch("", ""));

    return 0;
}