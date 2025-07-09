#include <iostream> // Dành cho std::cout, std::endl
#include <algorithm> // Dành cho std::max

// Cấu trúc của một Node trong cây AVL
struct Node {
    int key;      // Giá trị của nút
    Node* left;   // Con trỏ đến nút con trái
    Node* right;  // Con trỏ đến nút con phải
    int height;   // Chiều cao của nút (tính từ nút đó đến lá sâu nhất)

    // Constructor để khởi tạo một nút mới
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

// Lớp AVLTree
class AVLTree {
private:
    Node* root; // Nút gốc của cây

    // Hàm lấy chiều cao của một nút. Trả về 0 nếu nút là nullptr.
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    // Hàm cập nhật chiều cao của một nút.
    // Chiều cao của nút = 1 + max(chiều cao cây con trái, chiều cao cây con phải)
    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    // Hàm tính yếu tố cân bằng của một nút
    // Balance Factor = height(right_subtree) - height(left_subtree)
    int get_balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->right) - height(node->left);
    }

    // --- Các phép xoay (Rotations) ---

    // Xoay Phải (Right Rotation)
    // Thực hiện khi cây con trái của một nút bị mất cân bằng (BF = -2)
    // Ví dụ:   Z                       Y
    //         / \                     / \
    //        Y   T3      ->          X   Z
    //       / \                     / \ / \
    //      X   T2                  T0 T1 T2 T3
    //     / \
    //    T0 T1
    Node* rightRotate(Node* z) {
        Node* y = z->left;
        Node* T2 = y->right;

        // Thực hiện xoay
        y->right = z;
        z->left = T2;

        // Cập nhật chiều cao của các nút bị ảnh hưởng
        updateHeight(z);
        updateHeight(y);

        return y; // Trả về nút gốc mới của cây con đã xoay
    }

    // Xoay Trái (Left Rotation)
    // Thực hiện khi cây con phải của một nút bị mất cân bằng (BF = 2)
    // Ví dụ:   Y                           Z
    //         / \                         / \
    //        T1  Z           ->          Y   T3
    //           / \                     / \
    //          T2 T3                   T1 T2
    Node* leftRotate(Node* y) {
        Node* z = y->right;
        Node* T2 = z->left;

        // Thực hiện xoay
        z->left = y;
        y->right = T2;

        // Cập nhật chiều cao của các nút bị ảnh hưởng
        updateHeight(y);
        updateHeight(z);

        return z; // Trả về nút gốc mới của cây con đã xoay
    }

    // Phương thức đệ quy để chèn một giá trị vào cây và tự cân bằng
    Node* insertRecursive(Node* node, int key) {
        // 1. Thực hiện chèn BST thông thường
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        } else { // Các giá trị trùng lặp thường không được phép trong BST cân bằng
            return node;
        }

        // 2. Cập nhật chiều cao của nút hiện tại
        updateHeight(node);

        // 3. Lấy yếu tố cân bằng của nút này
        int balance = get_balance(node);

        // 4. Kiểm tra xem có mất cân bằng không và thực hiện xoay nếu cần

        // Trường hợp L-L (Left Left Case)
        // Mất cân bằng do chèn vào cây con trái của cây con trái (BF < -1 và key nhỏ hơn con trái)
        if (balance < -1 && key < node->left->key) {
            return rightRotate(node);
        }

        // Trường hợp R-R (Right Right Case)
        // Mất cân bằng do chèn vào cây con phải của cây con phải (BF > 1 và key lớn hơn con phải)
        if (balance > 1 && key > node->right->key) {
            return leftRotate(node);
        }

        // Trường hợp L-R (Left Right Case)
        // Mất cân bằng do chèn vào cây con phải của cây con trái (BF < -1 và key lớn hơn con trái)
        if (balance < -1 && key > node->left->key) {
            node->left = leftRotate(node->left); // Xoay trái trên cây con trái
            return rightRotate(node);            // Sau đó xoay phải trên nút hiện tại
        }

        // Trường hợp R-L (Right Left Case)
        // Mất cân bằng do chèn vào cây con trái của cây con phải (BF > 1 và key nhỏ hơn con phải)
        if (balance > 1 && key < node->right->key) {
            node->right = rightRotate(node->right); // Xoay phải trên cây con phải
            return leftRotate(node);             // Sau đó xoay trái trên nút hiện tại
        }

        return node; // Trả về con trỏ nút (sau khi đã cân bằng hoặc không cần cân bằng)
    }

    // Phương thức đệ quy hỗ trợ tìm kiếm
    bool searchRecursive(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) {
            return true;
        }

        if (key < node->key) {
            return searchRecursive(node->left, key);
        } else {
            return searchRecursive(node->right, key);
        }
    }

    // Duyệt cây theo thứ tự giữa (In-order: Left, Node, Right)
    void inorderRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderRecursive(node->left);
        std::cout << node->key << " (h:" << node->height << ", bf:" << get_balance(node) << ") ";
        inorderRecursive(node->right);
    }

    // Hàm hỗ trợ xóa toàn bộ cây (để tránh rò rỉ bộ nhớ)
    void destroyTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node; // Giải phóng bộ nhớ của nút hiện tại
    }

public:
    // Constructor của AVLTree
    AVLTree() : root(nullptr) {}

    // Destructor để giải phóng bộ nhớ khi đối tượng AVLTree bị hủy
    ~AVLTree() {
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

    // Phương thức công khai để duyệt theo thứ tự giữa
    void inorderTraversal() {
        inorderRecursive(root);
        std::cout << std::endl;
    }

    // Hàm để in chiều cao của gốc (cho mục đích kiểm tra)
    int getRootHeight() {
        return height(root);
    }
};

// Hàm main để kiểm thử
int main() {
    AVLTree avl;

    std::cout << "--- Chen cac phan tu vao cay AVL ---" << std::endl;
    // Chèn theo thứ tự tăng dần để minh họa việc cân bằng
    // Ví dụ, nếu đây là BST thường, nó sẽ thoái hóa thành danh sách liên kết.
    // Với AVL, nó sẽ tự cân bằng thông qua các phép xoay.
    int elements[] = {10, 20, 30, 40, 50, 25, 5, 35, 45, 15};
    for (int element : elements) {
        std::cout << "Chen: " << element << std::endl;
        avl.insert(element);
        std::cout << "Cay (In-order): ";
        avl.inorderTraversal();
        std::cout << "Chieu cao goc: " << avl.getRootHeight() << "\n" << std::endl;
    }

    std::cout << "\n--- Kiem tra tim kiem ---" << std::endl;
    std::cout << "Tim kiem 30: " << (avl.search(30) ? "True" : "False") << std::endl; // True
    std::cout << "Tim kiem 99: " << (avl.search(99) ? "True" : "False") << std::endl; // False
    std::cout << "Tim kiem 10: " << (avl.search(10) ? "True" : "False") << std::endl; // True

    std::cout << "\n--- Duyet cay cuoi cung (In-order) ---" << std::endl;
    std::cout << "Ket qua (In-order): ";
    avl.inorderTraversal();

    return 0;
}