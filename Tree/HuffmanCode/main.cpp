#include <iostream>     // Dành cho std::cout, std::endl
#include <string>       // Dành cho std::string
#include <vector>       // Dành cho std::vector
#include <queue>        // Dành cho std::priority_queue
#include <map>          // Dành cho std::map (lưu tần suất và mã Huffman)
#include <algorithm>    // Dành cho std::sort (nếu cần, nhưng priority_queue tự sắp xếp)

// --- Bước 1: Định nghĩa cấu trúc Node cho cây Huffman ---
struct HuffmanNode {
    char data;      // Ký tự (chỉ có nghĩa nếu là nút lá)
    int frequency;  // Tần suất xuất hiện
    HuffmanNode *left, *right; // Con trỏ đến nút con trái và phải

    // Constructor cho nút lá
    HuffmanNode(char data, int frequency) :
        data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    // Constructor cho nút nội bộ (tổng hợp từ hai nút con)
    HuffmanNode(int frequency, HuffmanNode* left, HuffmanNode* right) :
        data('\0'), frequency(frequency), left(left), right(right) {}

    // Destructor để giải phóng bộ nhớ (quan trọng trong C++)
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// --- Bước 2: Comparator cho Priority Queue ---
// Priority Queue cần một cách để biết nút nào có "ưu tiên" cao hơn (tần suất thấp hơn)
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency; // Sắp xếp tăng dần theo tần suất (min-heap)
    }
};

class HuffmanCoding {
private:
    HuffmanNode* root; // Nút gốc của cây Huffman
    std::map<char, std::string> huffmanCodes; // Lưu trữ mã Huffman cho từng ký tự

    // --- Bước 3: Xây dựng cây Huffman ---
    HuffmanNode* buildHuffmanTree(const std::map<char, int>& frequencies) {
        // Hàng đợi ưu tiên (min-heap) để lưu trữ các nút HuffmanNode
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;

        // Tạo các nút lá và thêm vào hàng đợi ưu tiên
        for (auto const& [char_data, freq] : frequencies) {
            pq.push(new HuffmanNode(char_data, freq));
        }

        // Lặp lại cho đến khi chỉ còn một nút trong hàng đợi (nút gốc của cây Huffman)
        while (pq.size() > 1) {
            // Lấy ra hai nút có tần suất thấp nhất
            HuffmanNode* left_child = pq.top(); pq.pop();
            HuffmanNode* right_child = pq.top(); pq.pop();

            // Tạo nút cha mới với tần suất là tổng của hai con
            HuffmanNode* parent = new HuffmanNode(left_child->frequency + right_child->frequency, left_child, right_child);
            pq.push(parent); // Thêm nút cha vào hàng đợi
        }

        return pq.top(); // Nút cuối cùng còn lại là gốc của cây Huffman
    }

    // --- Bước 4: Tạo mã Huffman bằng cách duyệt cây ---
    void generateHuffmanCodesRecursive(HuffmanNode* node, std::string currentCode) {
        // Nếu là nút rỗng, dừng lại
        if (node == nullptr) {
            return;
        }

        // Nếu là nút lá, đó là một ký tự và chúng ta đã tìm thấy mã của nó
        if (node->left == nullptr && node->right == nullptr) {
            huffmanCodes[node->data] = currentCode;
            return;
        }

        // Duyệt cây con trái (gán '0')
        generateHuffmanCodesRecursive(node->left, currentCode + "0");
        // Duyệt cây con phải (gán '1')
        generateHuffmanCodesRecursive(node->right, currentCode + "1");
    }

public:
    // Constructor
    HuffmanCoding() : root(nullptr) {}

    // Destructor để giải phóng bộ nhớ cây Huffman
    ~HuffmanCoding() {
        delete root;
    }

    // Hàm chính để xây dựng cây và tạo mã
    void buildAndGenerateCodes(const std::string& text) {
        // 1. Đếm tần suất các ký tự
        std::map<char, int> frequencies;
        for (char c : text) {
            frequencies[c]++;
        }

        // Nếu chuỗi rỗng hoặc chỉ có 1 ký tự duy nhất
        if (frequencies.empty()) {
            root = nullptr;
            huffmanCodes.clear();
            return;
        }
        if (frequencies.size() == 1) {
            // Trường hợp đặc biệt: chỉ có 1 ký tự, gán mã "0" cho nó
            root = new HuffmanNode(frequencies.begin()->first, frequencies.begin()->second);
            huffmanCodes[frequencies.begin()->first] = "0";
            return;
        }

        // 2. Xây dựng cây Huffman
        root = buildHuffmanTree(frequencies);

        // 3. Tạo mã Huffman từ cây
        generateHuffmanCodesRecursive(root, "");
    }

    // --- Nén dữ liệu (Encode) ---
    std::string encode(const std::string& text) {
        if (huffmanCodes.empty()) {
            std::cerr << "Loi: Ma Huffman chua duoc tao. Hay goi buildAndGenerateCodes truoc." << std::endl;
            return "";
        }

        std::string encoded_text = "";
        for (char c : text) {
            if (huffmanCodes.count(c)) { // Kiểm tra xem ký tự có trong bảng mã không
                encoded_text += huffmanCodes[c];
            } else {
                std::cerr << "Loi: Ky tu '" << c << "' khong co trong bang ma Huffman!" << std::endl;
                return ""; // Xử lý lỗi nếu gặp ký tự không có trong cây
            }
        }
        return encoded_text;
    }

    // --- Giải nén dữ liệu (Decode) ---
    std::string decode(const std::string& encoded_text) {
        if (root == nullptr) {
            std::cerr << "Loi: Cay Huffman rong. Khong the giai nen." << std::endl;
            return "";
        }
        if (encoded_text.empty()) {
            return "";
        }

        std::string decoded_text = "";
        HuffmanNode* current_node = root;

        for (char bit : encoded_text) {
            if (bit == '0') {
                current_node = current_node->left;
            } else if (bit == '1') {
                current_node = current_node->right;
            } else {
                std::cerr << "Loi: Chuoi ma hoa khong hop le (chua ky tu khac '0'/'1')!" << std::endl;
                return "";
            }

            // Nếu đến nút lá, đó là một ký tự đã được giải mã
            if (current_node->left == nullptr && current_node->right == nullptr) {
                decoded_text += current_node->data;
                current_node = root; // Quay về gốc để giải mã ký tự tiếp theo
            }
        }
        return decoded_text;
    }

    // In bảng mã Huffman
    void printCodes() {
        std::cout << "Bang ma Huffman:\n";
        for (auto const& [char_data, code] : huffmanCodes) {
            std::cout << "  '" << char_data << "': " << code << "\n";
        }
    }
};

// Hàm main để kiểm thử
int main() {
    std::string original_text = "this is a huffman example";
    std::cout << "--- Van ban goc: '" << original_text << "' ---\n";

    HuffmanCoding huffman;
    huffman.buildAndGenerateCodes(original_text);

    huffman.printCodes();

    std::string encoded_data = huffman.encode(original_text);
    std::cout << "\n--- Du lieu da nen: " << encoded_data << " ---\n";

    std::string decoded_data = huffman.decode(encoded_data);
    std::cout << "\n--- Du lieu da giai nen: '" << decoded_data << "' ---\n";

    // Kiểm tra xem dữ liệu có khớp không
    if (original_text == decoded_data) {
        std::cout << "\nKet qua: Nen va giai nen THANH CONG! Du lieu khop.\n";
    } else {
        std::cout << "\nKet qua: Nen va giai nen THAT BAI! Du lieu khong khop.\n";
    }

    std::cout << "\n--------------------------------------------------\n";

    std::string text2 = "aaaaaaaaabbbbbcccdde";
    std::cout << "--- Van ban goc 2: '" << text2 << "' ---\n";
    HuffmanCoding huffman2;
    huffman2.buildAndGenerateCodes(text2);
    huffman2.printCodes();
    std::string encoded_data2 = huffman2.encode(text2);
    std::cout << "\n--- Du lieu da nen 2: " << encoded_data2 << " ---\n";
    std::string decoded_data2 = huffman2.decode(encoded_data2);
    std::cout << "\n--- Du lieu da giai nen 2: '" << decoded_data2 << "' ---\n";
    if (text2 == decoded_data2) {
        std::cout << "\nKet qua: Nen va giai nen THANH CONG! Du lieu khop.\n";
    } else {
        std::cout << "\nKet qua: Nen va giai nen THAT BAI! Du lieu khong khop.\n";
    }

    // Trường hợp đặc biệt: chuỗi rỗng
    std::cout << "\n--------------------------------------------------\n";
    std::string empty_text = "";
    std::cout << "--- Van ban goc rong: '" << empty_text << "' ---\n";
    HuffmanCoding huffman_empty;
    huffman_empty.buildAndGenerateCodes(empty_text);
    huffman_empty.printCodes();
    std::string encoded_empty = huffman_empty.encode(empty_text);
    std::cout << "\n--- Du lieu da nen rong: " << encoded_empty << " ---\n";
    std::string decoded_empty = huffman_empty.decode(encoded_empty);
    std::cout << "\n--- Du lieu da giai nen rong: '" << decoded_empty << "' ---\n";
    if (empty_text == decoded_empty) {
        std::cout << "\nKet qua: Nen va giai nen THANH CONG! Du lieu khop.\n";
    } else {
        std::cout << "\nKet qua: Nen va giai nen THAT BAI! Du lieu khong khop.\n";
    }

    // Trường hợp đặc biệt: chuỗi chỉ có 1 ký tự duy nhất
    std::cout << "\n--------------------------------------------------\n";
    std::string single_char_text = "aaaaa";
    std::cout << "--- Van ban goc (1 ky tu): '" << single_char_text << "' ---\n";
    HuffmanCoding huffman_single;
    huffman_single.buildAndGenerateCodes(single_char_text);
    huffman_single.printCodes();
    std::string encoded_single = huffman_single.encode(single_char_text);
    std::cout << "\n--- Du lieu da nen (1 ky tu): " << encoded_single << " ---\n";
    std::string decoded_single = huffman_single.decode(encoded_single);
    std::cout << "\n--- Du lieu da giai nen (1 ky tu): '" << decoded_single << "' ---\n";
    if (single_char_text == decoded_single) {
        std::cout << "\nKet qua: Nen va giai nen THANH CONG! Du lieu khop.\n";
    } else {
        std::cout << "\nKet qua: Nen va giai nen THAT BAI! Du lieu khong khop.\n";
    }


    return 0;
}