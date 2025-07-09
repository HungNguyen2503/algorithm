#include <iostream> // Dành cho std::cout, std::endl
#include <string>   // Dành cho std::string
#include <vector>   // Dành cho std::vector
#include <map>      // Có thể dùng std::map thay cho mảng cố định nếu cần

// Định nghĩa kích thước bảng chữ cái (ví dụ: chữ cái Latinh viết thường 'a'-'z')
const int ALPHABET_SIZE = 26;

// Cấu trúc của một nút trong Trie
struct TrieNode {
    // Mảng con trỏ đến các nút con.
    // children[0] cho 'a', children[1] cho 'b', v.v.
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord; // True nếu một từ kết thúc tại nút này

    // Constructor để khởi tạo nút
    TrieNode() {
        isEndOfWord = false;
        // Khởi tạo tất cả con trỏ con là nullptr
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
    }

    // Destructor để giải phóng bộ nhớ các nút con một cách đệ quy
    ~TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            delete children[i]; // Gọi đệ quy destructor của các nút con
        }
    }
};

// Lớp Trie
class Trie {
private:
    TrieNode* root;

    // Hàm hỗ trợ đệ quy để thu thập tất cả các từ từ một nút
    void collectWords(TrieNode* node, std::string currentWord, std::vector<std::string>& words) {
        if (node->isEndOfWord) {
            words.push_back(currentWord);
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i] != nullptr) {
                char ch = 'a' + i; // Chuyển đổi chỉ số thành ký tự
                collectWords(node->children[i], currentWord + ch, words);
            }
        }
    }

public:
    // Constructor
    Trie() {
        root = new TrieNode(); // Khởi tạo nút gốc
    }

    // Destructor
    // Destructor của TrieNode sẽ tự động giải phóng toàn bộ cây
    ~Trie() {
        delete root; // Bắt đầu quá trình giải phóng từ gốc
    }

    // Chèn một từ vào Trie
    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a'; // Chuyển ký tự thành chỉ số (0-25)
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true; // Đánh dấu đây là kết thúc của một từ
    }

    // Tìm kiếm một từ đầy đủ trong Trie
    bool search(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return false; // Ký tự không tồn tại, từ không có
            }
            current = current->children[index];
        }
        // Sau khi duyệt hết từ, kiểm tra xem có phải là kết thúc của một từ không
        return current->isEndOfWord;
    }

    // Kiểm tra xem có bất kỳ từ nào trong Trie bắt đầu bằng tiền tố đã cho không
    bool startsWith(const std::string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return false; // Ký tự không tồn tại, không có từ nào bắt đầu bằng tiền tố này
            }
            current = current->children[index];
        }
        return true; // Đã duyệt hết tiền tố, nghĩa là có ít nhất một từ bắt đầu bằng tiền tố đó
    }

    // Hàm hỗ trợ để tìm nút tương ứng với tiền tố cuối cùng
    TrieNode* findPrefixNode(const std::string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return nullptr;
            }
            current = current->children[index];
        }
        return current;
    }

    // Trả về danh sách tất cả các từ trong Trie bắt đầu bằng tiền tố đã cho
    std::vector<std::string> autocomplete(const std::string& prefix) {
        std::vector<std::string> suggestions;
        TrieNode* prefixNode = findPrefixNode(prefix);

        if (prefixNode == nullptr) {
            return suggestions; // Không có từ nào bắt đầu bằng tiền tố này
        }

        // Bắt đầu thu thập các từ từ nút tiền tố
        collectWords(prefixNode, prefix, suggestions);
        return suggestions;
    }
};

// Hàm main để kiểm thử
int main() {
    Trie trie;

    // Chèn các từ
    std::cout << "--- Chen cac tu vao Trie ---" << std::endl;
    std::vector<std::string> words_to_insert = {"apple", "app", "apricot", "apply", "banana", "band", "bat", "badminton"};
    for (const std::string& word : words_to_insert) {
        trie.insert(word);
        std::cout << "Da chen: '" << word << "'" << std::endl;
    }

    // Kiểm tra tìm kiếm từ đầy đủ
    std::cout << "\n--- Kiem tra tim kiem tu day du ---" << std::endl;
    std::cout << "Tim 'apple': " << (trie.search("apple") ? "True" : "False") << std::endl;      // True
    std::cout << "Tim 'app': " << (trie.search("app") ? "True" : "False") << std::endl;          // True
    std::cout << "Tim 'apricot': " << (trie.search("apricot") ? "True" : "False") << std::endl;  // True
    std::cout << "Tim 'appl': " << (trie.search("appl") ? "True" : "False") << std::endl;        // False
    std::cout << "Tim 'application': " << (trie.search("application") ? "True" : "False") << std::endl; // False
    std::cout << "Tim 'banana': " << (trie.search("banana") ? "True" : "False") << std::endl;    // True

    // Kiểm tra tiền tố
    std::cout << "\n--- Kiem tra tien to (startsWith) ---" << std::endl;
    std::cout << "Co tu nao bat dau bang 'app' khong?: " << (trie.startsWith("app") ? "True" : "False") << std::endl;      // True
    std::cout << "Co tu nao bat dau bang 'ban' khong?: " << (trie.startsWith("ban") ? "True" : "False") << std::endl;      // True
    std::cout << "Co tu nao bat dau bang 'ap' khong?: " << (trie.startsWith("ap") ? "True" : "False") << std::endl;       // True
    std::cout << "Co tu nao bat dau bang 'base' khong?: " << (trie.startsWith("base") ? "True" : "False") << std::endl;   // False
    std::cout << "Co tu nao bat dau bang 'ba' khong?: " << (trie.startsWith("ba") ? "True" : "False") << std::endl;       // True

    // Minh họa tự động hoàn thành
    std::cout << "\n--- Minh hoa Tu dong hoan thanh (Autocomplete) ---" << std::endl;

    std::string prefix1 = "ap";
    std::vector<std::string> suggestions1 = trie.autocomplete(prefix1);
    std::cout << "Cac goi y cho '" << prefix1 << "': ";
    for (const std::string& s : suggestions1) {
        std::cout << s << " ";
    }
    std::cout << std::endl; // Expected: apple app apricot apply (thứ tự có thể khác)

    std::string prefix2 = "ban";
    std::vector<std::string> suggestions2 = trie.autocomplete(prefix2);
    std::cout << "Cac goi y cho '" << prefix2 << "': ";
    for (const std::string& s : suggestions2) {
        std::cout << s << " ";
    }
    std::cout << std::endl; // Expected: banana band (thứ tự có thể khác)

    std::string prefix3 = "bat";
    std::vector<std::string> suggestions3 = trie.autocomplete(prefix3);
    std::cout << "Cac goi y cho '" << prefix3 << "': ";
    for (const std::string& s : suggestions3) {
        std::cout << s << " ";
    }
    std::cout << std::endl; // Expected: bat

    std::string prefix4 = "bad";
    std::vector<std::string> suggestions4 = trie.autocomplete(prefix4);
    std::cout << "Cac goi y cho '" << prefix4 << "': ";
    for (const std::string& s : suggestions4) {
        std::cout << s << " ";
    }
    std::cout << std::endl; // Expected: badminton

    std::string prefix5 = "xyz";
    std::vector<std::string> suggestions5 = trie.autocomplete(prefix5);
    std::cout << "Cac goi y cho '" << prefix5 << "': ";
    for (const std::string& s : suggestions5) {
        std::cout << s << " ";
    }
    std::cout << std::endl; // Expected: (empty line)

    return 0;
}