#include <iostream> // Để sử dụng cout, cin
#include <queue>    // Để sử dụng std::queue cho duyệt theo cấp độ

// Định nghĩa cấu trúc của một Node trong cây nhị phân
struct Node {
    int key;      // Giá trị của nút
    Node* left;   // Con trỏ đến nút con trái
    Node* right;  // Con trỏ đến nút con phải

    // Constructor để khởi tạo một nút mới
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// Lớp BinarySearchTree
class BinarySearchTree {
private:
    Node* root; // Nút gốc của cây

    // Phương thức đệ quy hỗ trợ chèn
    Node* insertRecursive(Node* node, int key) {
        // Nếu cây con rỗng, tạo nút mới và trả về
        if (node == nullptr) {
            return new Node(key);
        }

        // Đi xuống cây con trái hoặc phải tùy thuộc vào giá trị key
        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }
        // Nếu key đã tồn tại (key == node->key), không làm gì cả (có thể bỏ qua hoặc cập nhật)
        return node;
    }

    // Phương thức đệ quy hỗ trợ tìm kiếm
    bool searchRecursive(Node* node, int key) {
        // Nếu nút rỗng hoặc tìm thấy key
        if (node == nullptr) {
            return false; // Không tìm thấy
        }
        if (node->key == key) {
            return true; // Tìm thấy
        }

        // Đi xuống cây con trái hoặc phải
        if (key < node->key) {
            return searchRecursive(node->left, key);
        } else {
            return searchRecursive(node->right, key);
        }
    }

    // Tìm nút có giá trị nhỏ nhất trong một cây con (đi xuống nhánh trái nhất)
    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Phương thức đệ quy hỗ trợ xóa
    Node* deleteRecursive(Node* node, int key) {
        // Trường hợp cơ bản: cây con rỗng hoặc không tìm thấy key
        if (node == nullptr) {
            return node;
        }

        // 1. Tìm nút cần xóa
        if (key < node->key) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = deleteRecursive(node->right, key);
        } else { // key == node->key, đây là nút cần xóa
            // Trường hợp 1: Nút lá hoặc nút có 1 con
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node; // Giải phóng bộ nhớ của nút hiện tại
                return temp; // Thay thế nút bằng con phải của nó (có thể là nullptr)
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node; // Giải phóng bộ nhớ của nút hiện tại
                return temp; // Thay thế nút bằng con trái của nó
            }

            // Trường hợp 2: Nút có 2 con
            // Tìm phần tử nhỏ nhất trong cây con phải (in-order successor)
            Node* temp = findMinNode(node->right);
            node->key = temp->key; // Sao chép giá trị của phần tử đó vào nút hiện tại
            // Xóa phần tử nhỏ nhất trong cây con phải (vì nó đã được sao chép)
            node->right = deleteRecursive(node->right, temp->key);
        }
        return node;
    }

    // Duyệt cây theo thứ tự giữa (LNR: Left, Node, Right)
    void inorderRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderRecursive(node->left);
        std::cout << node->key << " ";
        inorderRecursive(node->right);
    }

    // Duyệt cây tiền thứ tự (NLR: Node, Left, Right)
    void preorderRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->key << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }

    // Duyệt cây hậu thứ tự (LRN: Left, Right, Node)
    void postorderRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        std::cout << node->key << " ";
    }

    // Hàm hỗ trợ xóa toàn bộ cây (để tránh rò rỉ bộ nhớ)
    void destroyTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    // Constructor của BST
    BinarySearchTree() : root(nullptr) {}

    // Destructor để giải phóng bộ nhớ khi đối tượng BST bị hủy
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Phương thức công khai để chèn
    void insert(int key) {
        root = insertRecursive(root, key);
    }

    // Phương thức công khai để tìm kiếm
    bool search(int key) {
        return searchRecursive(root, key);
    }

    // Phương thức công khai để xóa
    void deleteNode(int key) {
        root = deleteRecursive(root, key);
    }

    // Phương thức công khai để duyệt theo thứ tự giữa
    void inorderTraversal() {
        inorderRecursive(root);
        std::cout << std::endl;
    }

    // Phương thức công khai để duyệt tiền thứ tự
    void preorderTraversal() {
        preorderRecursive(root);
        std::cout << std::endl;
    }

    // Phương thức công khai để duyệt hậu thứ tự
    void postorderTraversal() {
        postorderRecursive(root);
        std::cout << std::endl;
    }

    // Phương thức công khai để duyệt theo cấp độ (BFS)
    void levelorderTraversal() {
        if (root == nullptr) {
            return;
        }

        std::queue<Node*> q; // Sử dụng std::queue để triển khai BFS
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front(); // Lấy nút ở đầu hàng đợi
            q.pop();                   // Xóa nút khỏi hàng đợi

            std::cout << current->key << " "; // In giá trị nút

            // Thêm con trái và con phải (nếu có) vào hàng đợi
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }
};

// Hàm main để kiểm thử
int main() {
    BinarySearchTree bst;

    std::cout << "--- Chen cac phan tu vao cay ---" << std::endl;
    int elements[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 45, 75, 85};
    for (int element : elements) {
        bst.insert(element);
        std::cout << "Chen: " << element << std::endl;
    }

    std::cout << "\n--- Duyet cay theo thu tu (In-order Traversal) ---" << std::endl;
    std::cout << "Ket qua (In-order): ";
    bst.inorderTraversal(); // Expected: 10 20 30 35 40 45 50 60 70 75 80 85

    std::cout << "\n--- Duyet cay tien thu tu (Pre-order Traversal) ---" << std::endl;
    std::cout << "Ket qua (Pre-order): ";
    bst.preorderTraversal(); // Expected: 50 30 20 10 40 35 45 70 60 80 75 85

    std::cout << "\n--- Duyet cay hau thu tu (Post-order Traversal) ---" << std::endl;
    std::cout << "Ket qua (Post-order): ";
    bst.postorderTraversal(); // Expected: 10 20 35 45 40 30 60 75 85 80 70 50

    std::cout << "\n--- Duyet cay theo cap do (Level-order Traversal) ---" << std::endl;
    std::cout << "Ket qua (Level-order): ";
    bst.levelorderTraversal(); // Expected: 50 30 70 20 40 60 80 10 35 45 75 85

    std::cout << "\n--- Tim kiem cac phan tu ---" << std::endl;
    std::cout << "Tim kiem 40: " << (bst.search(40) ? "True" : "False") << std::endl; // Expected: True
    std::cout << "Tim kiem 99: " << (bst.search(99) ? "True" : "False") << std::endl; // Expected: False
    std::cout << "Tim kiem 50: " << (bst.search(50) ? "True" : "False") << std::endl; // Expected: True

    std::cout << "\n--- Xoa cac phan tu ---" << std::endl;
    std::cout << "Cay ban dau (In-order): ";
    bst.inorderTraversal();

    std::cout << "\nXoa 20 (nut la):" << std::endl;
    bst.deleteNode(20);
    std::cout << "Cay sau khi xoa 20 (In-order): ";
    bst.inorderTraversal(); // Expected: 10 30 35 40 45 50 60 70 75 80 85

    std::cout << "\nXoa 70 (nut co 2 con):" << std::endl;
    bst.deleteNode(70);
    std::cout << "Cay sau khi xoa 70 (In-order): ";
    bst.inorderTraversal(); // Expected: 10 30 35 40 45 50 60 75 80 85 (75 the cho 70)

    std::cout << "\nXoa 30 (nut co 1 con):" << std::endl;
    bst.deleteNode(30);
    std::cout << "Cay sau khi xoa 30 (In-order): ";
    bst.inorderTraversal(); // Expected: 10 35 40 45 50 60 75 80 85 (40 the cho 30)

    std::cout << "\nXoa 50 (nut goc):" << std::endl;
    bst.deleteNode(50);
    std::cout << "Cay sau khi xoa 50 (In-order): ";
    bst.inorderTraversal(); // Expected: 10 35 40 45 60 75 80 85 (60 the cho 50)

    std::cout << "\nTim kiem 70 sau khi xoa: " << (bst.search(70) ? "True" : "False") << std::endl; // Expected: False
    std::cout << "Tim kiem 50 sau khi xoa: " << (bst.search(50) ? "True" : "False") << std::endl; // Expected: False

    return 0;
}