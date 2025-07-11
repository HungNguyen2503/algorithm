#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <stack>    // std::stack
#include <cmath>    // pow (cho lũy thừa)
#include <vector>   // Để lưu trữ token nếu cần
#include <sstream>  // Để phân tách chuỗi

// --- Cấu trúc Node ---
struct Node {
    std::string value; // Giá trị: ký tự toán tử hoặc chuỗi số
    bool is_operator;  // True nếu là toán tử, False nếu là toán hạng
    Node* left;
    Node* right;

    // Constructor cho toán hạng (số)
    Node(const std::string& val, bool op = false) :
        value(val), is_operator(op), left(nullptr), right(nullptr) {}
    
    // Destructor để giải phóng bộ nhớ đệ quy
    ~Node() {
        delete left;
        delete right;
    }
};

// --- Lớp ExpressionTree ---
class ExpressionTree {
private:
    Node* root;

    // Kiểm tra xem ký tự có phải toán tử không
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    // Thực hiện phép toán
    double performOperation(char op, double val1, double val2) {
        switch (op) {
            case '+': return val1 + val2;
            case '-': return val1 - val2;
            case '*': return val1 * val2;
            case '/': 
                if (val2 == 0) {
                    throw std::runtime_error("Loi: Chia cho 0!");
                }
                return val1 / val2;
            case '^': return std::pow(val1, val2);
            default: throw std::runtime_error("Toan tu khong hop le: " + std::string(1, op));
        }
    }

    // Đánh giá giá trị của biểu thức (đệ quy)
    double evaluateRecursive(Node* node) {
        if (node == nullptr) {
            return 0; // Hoặc ném lỗi, tùy vào cách xử lý yêu cầu
        }

        if (!node->is_operator) { // Nếu là toán hạng
            return std::stod(node->value); // Chuyển chuỗi thành double
        } else { // Nếu là toán tử
            double val_left = evaluateRecursive(node->left);
            double val_right = evaluateRecursive(node->right);
            return performOperation(node->value[0], val_left, val_right);
        }
    }

    // Lấy biểu thức dạng trung tố (đệ quy, có kèm ngoặc)
    std::string getInfixRecursive(Node* node) {
        if (node == nullptr) {
            return "";
        }

        if (!node->is_operator) { // Toán hạng
            return node->value;
        } else { // Toán tử
            // Luôn thêm ngoặc để giữ đúng thứ tự ưu tiên trong dạng trung tố
            // Có thể phức tạp hơn nếu muốn tối ưu số lượng ngoặc
            return "(" + getInfixRecursive(node->left) + " " +
                   node->value + " " +
                   getInfixRecursive(node->right) + ")";
        }
    }

public:
    // Constructor
    ExpressionTree() : root(nullptr) {}

    // Destructor
    ~ExpressionTree() {
        delete root; // Gọi destructor của root sẽ giải phóng toàn bộ cây
    }

    // Xây dựng cây từ biểu thức hậu tố
    // Ví dụ: "2 3 + 4 *"
    void buildFromPostfix(const std::string& postfixExpr) {
        std::stack<Node*> s;
        std::stringstream ss(postfixExpr); // Dùng stringstream để dễ dàng phân tách token
        std::string token;

        while (ss >> token) { // Đọc từng token một
            if (isOperator(token[0]) && token.length() == 1) { // Nếu là toán tử một ký tự
                Node* opNode = new Node(token, true);
                if (s.size() < 2) {
                    throw std::runtime_error("Loi: Bieu thuc hau to khong hop le (thieu toan hang)!");
                }
                opNode->right = s.top(); s.pop();
                opNode->left = s.top(); s.pop();
                s.push(opNode);
            } else { // Là toán hạng (số)
                s.push(new Node(token, false));
            }
        }

        if (s.size() != 1) {
            throw std::runtime_error("Loi: Bieu thuc hau to khong hop le (so luong toan tu/toan hang khong khop)!");
        }
        root = s.top(); // Nút cuối cùng trên stack là gốc
    }

    // Đánh giá giá trị của biểu thức
    double evaluate() {
        if (root == nullptr) {
            throw std::runtime_error("Loi: Cay bieu thuc rong!");
        }
        return evaluateRecursive(root);
    }

    // Lấy biểu thức dạng trung tố
    std::string getInfixExpression() {
        if (root == nullptr) {
            return "";
        }
        return getInfixRecursive(root);
    }
};

// --- Hàm main để kiểm thử ---
int main() {
    ExpressionTree exprTree;

    // Ví dụ 1: (2 + 3) * 4
    std::string postfix1 = "2 3 + 4 *";
    try {
        std::cout << "--- Bieu thuc 1: " << postfix1 << " ---" << std::endl;
        exprTree.buildFromPostfix(postfix1);
        std::cout << "Dang trung to: " << exprTree.getInfixExpression() << std::endl; // ((2 + 3) * 4)
        std::cout << "Gia tri: " << exprTree.evaluate() << std::endl; // 20
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n" << std::string(30, '-') << "\n" << std::endl;

    // Ví dụ 2: (10 + 5) * (8 - 3) / 2
    std::string postfix2 = "10 5 + 8 3 - * 2 /";
    try {
        // Cần tạo lại đối tượng hoặc clear cây cũ để test biểu thức mới
        // Với C++, cách đơn giản nhất là tạo đối tượng mới cho mỗi test case
        ExpressionTree exprTree2; 
        std::cout << "--- Bieu thuc 2: " << postfix2 << " ---" << std::endl;
        exprTree2.buildFromPostfix(postfix2);
        std::cout << "Dang trung to: " << exprTree2.getInfixExpression() << std::endl; // (((10 + 5) * (8 - 3)) / 2)
        std::cout << "Gia tri: " << exprTree2.evaluate() << std::endl; // 37.5
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n" << std::string(30, '-') << "\n" << std::endl;

    // Ví dụ 3: 5 + (-2)^3
    std::string postfix3 = "5 -2 3 ^ +";
    try {
        ExpressionTree exprTree3;
        std::cout << "--- Bieu thuc 3: " << postfix3 << " ---" << std::endl;
        exprTree3.buildFromPostfix(postfix3);
        std::cout << "Dang trung to: " << exprTree3.getInfixExpression() << std::endl; // (5 + (-2 ^ 3))
        std::cout << "Gia tri: " << exprTree3.evaluate() << std::endl; // -3
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n" << std::string(30, '-') << "\n" << std::endl;
    
    // Ví dụ lỗi: Biểu thức thiếu toán hạng
    std::string postfix_error = "2 +";
    try {
        ExpressionTree exprTree_error;
        std::cout << "--- Bieu thuc loi: " << postfix_error << " ---" << std::endl;
        exprTree_error.buildFromPostfix(postfix_error);
        std::cout << "Dang trung to: " << exprTree_error.getInfixExpression() << std::endl;
        std::cout << "Gia tri: " << exprTree_error.evaluate() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Loi xay ra: " << e.what() << std::endl; // In thông báo lỗi
    }

    return 0;
}