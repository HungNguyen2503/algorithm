#include <iostream> // Để sử dụng cout, cerr
#include <stdexcept> // Để sử dụng std::underflow_error
#include <stack> // Bao gồm thư viện stack STL cho ví dụ thứ 3
#include <string> // Để ví dụ với string trong std::stack

class ArrayStack {
private:
    int* arr;       // Con trỏ tới mảng lưu trữ các phần tử
    int topIndex;   // Chỉ số của phần tử trên cùng (-1 khi rỗng)
    int capacity;   // Kích thước tối đa của ngăn xếp

public:
    // Constructor: Khởi tạo ngăn xếp với một kích thước nhất định
    ArrayStack(int size) : capacity(size), topIndex(-1) {
        if (size <= 0) {
            throw std::invalid_argument("Stack capacity must be positive.");
        }
        arr = new int[capacity]; // Cấp phát động mảng
        std::cout << "Array Stack created with capacity: " << capacity << std::endl;
    }

    // Destructor: Giải phóng bộ nhớ khi đối tượng bị hủy
    ~ArrayStack() {
        delete[] arr;
        std::cout << "Array Stack destroyed." << std::endl;
    }

    // Thao tác PUSH: Thêm phần tử vào đỉnh
    void push(int value) {
        if (topIndex >= capacity - 1) {
            // Ngăn xếp đầy, không thể thêm nữa
            throw std::overflow_error("Stack Overflow: Cannot push to a full stack.");
        }
        arr[++topIndex] = value; // Tăng topIndex rồi gán giá trị
        std::cout << "Pushed: " << value << std::endl;
    }

    // Thao tác POP: Lấy phần tử từ đỉnh
    int pop() {
        if (topIndex < 0) {
            // Ngăn xếp rỗng, không có gì để lấy ra
            throw std::underflow_error("Stack Underflow: Cannot pop from an empty stack.");
        }
        int poppedValue = arr[topIndex--]; // Lấy giá trị rồi giảm topIndex
        std::cout << "Popped: " << poppedValue << std::endl;
        return poppedValue;
    }

    // Thao tác PEEK/TOP: Xem phần tử trên cùng
    int peek() const { // Sử dụng const vì không thay đổi trạng thái
        if (topIndex < 0) {
            throw std::underflow_error("Stack is empty.");
        }
        return arr[topIndex];
    }

    // Kiểm tra ngăn xếp có rỗng không
    bool isEmpty() const { // Sử dụng const vì không thay đổi trạng thái
        return topIndex == -1;
    }

    // Trả về kích thước hiện tại của ngăn xếp
    int size() const { // Sử dụng const vì không thay đổi trạng thái
        return topIndex + 1;
    }
};

// Định nghĩa một Node cho danh sách liên kết
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};


/////////////////////////////////////////////////////
class LinkedListStack {
private:
    Node* topNode; // Con trỏ tới nút trên cùng của ngăn xếp
    int currentSize; // Kích thước hiện tại của ngăn xếp

public:
    // Constructor: Khởi tạo ngăn xếp rỗng
    LinkedListStack() : topNode(nullptr), currentSize(0) {
        std::cout << "Linked List Stack created." << std::endl;
    }

    // Destructor: Giải phóng tất cả các nút trong ngăn xếp
    ~LinkedListStack() {
        while (!isEmpty()) {
            // Lấy ra từng phần tử để giải phóng bộ nhớ
            // Tương tự như pop nhưng không cần trả về giá trị
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
            currentSize--;
        }
        std::cout << "Linked List Stack destroyed." << std::endl;
    }

    // Thao tác PUSH: Thêm phần tử vào đỉnh
    void push(int value) {
        Node* newNode = new Node(value); // Tạo nút mới
        newNode->next = topNode;        // Nút mới trỏ tới nút hiện tại ở đỉnh
        topNode = newNode;              // Cập nhật topNode thành nút mới
        currentSize++;
        std::cout << "Pushed: " << value << std::endl;
    }

    // Thao tác POP: Lấy phần tử từ đỉnh
    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack Underflow: Cannot pop from an empty stack.");
        }
        Node* temp = topNode;       // Lưu lại nút đỉnh hiện tại
        int poppedValue = temp->data; // Lấy giá trị của nút đỉnh
        topNode = topNode->next;    // Cập nhật topNode xuống nút tiếp theo
        delete temp;                // Giải phóng bộ nhớ của nút đã xóa
        currentSize--;
        std::cout << "Popped: " << poppedValue << std::endl;
        return poppedValue;
    }

    // Thao tác PEEK/TOP: Xem phần tử trên cùng
    int peek() const { // Sử dụng const vì không thay đổi trạng thái
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty.");
        }
        return topNode->data;
    }

    // Kiểm tra ngăn xếp có rỗng không
    bool isEmpty() const { // Sử dụng const vì không thay đổi trạng thái
        return topNode == nullptr;
    }

    // Trả về kích thước hiện tại của ngăn xếp
    int size() const { // Sử dụng const vì không thay đổi trạng thái
        return currentSize;
    }
};

// Hàm main chính để thử nghiệm
int main() {
    std::cout << "--- Testing Array-based Stack ---" << std::endl;
    try {
        ArrayStack myArrStack(3); // Tạo ngăn xếp mảng với kích thước 3

        myArrStack.push(10);
        myArrStack.push(20);
        std::cout << "Top element: " << myArrStack.peek() << std::endl;
        myArrStack.push(30);
        std::cout << "Stack size: " << myArrStack.size() << std::endl; // Output: 3

        try {
            myArrStack.push(40); // Sẽ ném ngoại lệ Stack Overflow
        } catch (const std::overflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        myArrStack.pop();
        std::cout << "Top element after pop: " << myArrStack.peek() << std::endl;
        myArrStack.pop();
        myArrStack.pop();

        std::cout << "Is Array Stack empty? " << (myArrStack.isEmpty() ? "Yes" : "No") << std::endl;

        try {
            myArrStack.pop(); // Sẽ ném ngoại lệ Stack Underflow
        } catch (const std::underflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "General Error with ArrayStack: " << e.what() << std::endl;
    }
    std::cout << "---------------------------------" << std::endl << std::endl;


    std::cout << "--- Testing Linked List-based Stack ---" << std::endl;
    try {
        LinkedListStack myLLStack;

        myLLStack.push(100);
        myLLStack.push(200);
        std::cout << "Top element: " << myLLStack.peek() << std::endl;
        myLLStack.push(300);
        std::cout << "Stack size: " << myLLStack.size() << std::endl; // Output: 3

        myLLStack.pop();
        std::cout << "Top element after pop: " << myLLStack.peek() << std::endl;
        myLLStack.pop();
        myLLStack.pop();

        std::cout << "Is Linked List Stack empty? " << (myLLStack.isEmpty() ? "Yes" : "No") << std::endl;

        try {
            myLLStack.pop(); // Sẽ ném ngoại lệ Stack Underflow
        } catch (const std::underflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "General Error with LinkedListStack: " << e.what() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl << std::endl;


    std::cout << "--- Testing std::stack (STL) ---" << std::endl;
    // Khởi tạo một stack chứa số nguyên
    std::stack<int> mySTLStack;

    std::cout << "Is std::stack empty? " << (mySTLStack.empty() ? "Yes" : "No") << std::endl;

    // Thao tác push
    mySTLStack.push(1000);
    mySTLStack.push(2000);
    mySTLStack.push(3000);
    std::cout << "Pushed 1000, 2000, 3000." << std::endl;

    // Thao tác top (peek)
    std::cout << "Top element: " << mySTLStack.top() << std::endl;

    // Thao tác size
    std::cout << "Size of std::stack: " << mySTLStack.size() << std::endl;

    // Thao tác pop
    mySTLStack.pop(); // Xóa 3000
    std::cout << "Popped top element." << std::endl;
    std::cout << "New top element: " << mySTLStack.top() << std::endl;

    mySTLStack.pop(); // Xóa 2000
    mySTLStack.pop(); // Xóa 1000

    std::cout << "Is std::stack empty? " << (mySTLStack.empty() ? "Yes" : "No") << std::endl;

    // std::stack không tự ném ngoại lệ khi pop hoặc top một stack rỗng.
    // Bạn cần tự kiểm tra trước khi gọi pop/top trên stack rỗng để tránh undefined behavior.
    if (mySTLStack.empty()) {
        std::cout << "Cannot pop/top from an empty std::stack (checked manually)." << std::endl;
    }

    // Ví dụ với stack chứa string
    std::stack<std::string> mySTLStringStack;
    mySTLStringStack.push("Apple");
    mySTLStringStack.push("Banana");
    std::cout << "Top string: " << mySTLStringStack.top() << std::endl;

    std::cout << "--------------------------------" << std::endl;

    return 0;
}