#include <iostream>
#include <queue>   // Bao gồm thư viện queue
#include <string>  // Để ví dụ với string

class CircularArrayQueue {
private:
    int* arr;
    int front;    // Chỉ số của phần tử đầu tiên
    int rear;     // Chỉ số của phần tử cuối cùng
    int capacity; // Kích thước tối đa của hàng đợi
    int currentSize; // Số lượng phần tử hiện tại trong hàng đợi

public:
    // Constructor
    CircularArrayQueue(int size) : capacity(size), front(0), rear(-1), currentSize(0) {
        if (size <= 0) {
            throw std::invalid_argument("Queue capacity must be positive.");
        }
        arr = new int[capacity];
        std::cout << "Circular Array Queue created with capacity: " << capacity << std::endl;
    }

    // Destructor
    ~CircularArrayQueue() {
        delete[] arr;
        std::cout << "Circular Array Queue destroyed." << std::endl;
    }

    // Thao tác Enqueue: Thêm phần tử vào cuối hàng đợi
    void enqueue(int value) {
        if (currentSize == capacity) {
            throw std::overflow_error("Queue Overflow: Cannot enqueue to a full queue.");
        }
        rear = (rear + 1) % capacity; // Di chuyển rear theo vòng tròn
        arr[rear] = value;
        currentSize++;
        std::cout << "Enqueued: " << value << std::endl;
    }

    // Thao tác Dequeue: Lấy phần tử từ đầu hàng đợi
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue Underflow: Cannot dequeue from an empty queue.");
        }
        int dequeuedValue = arr[front];
        front = (front + 1) % capacity; // Di chuyển front theo vòng tròn
        currentSize--;
        std::cout << "Dequeued: " << dequeuedValue << std::endl;
        return dequeuedValue;
    }

    // Thao tác Front/Peek: Xem phần tử đầu hàng đợi
    int frontValue() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty.");
        }
        return arr[front];
    }

    // Kiểm tra hàng đợi có rỗng không
    bool isEmpty() const {
        return currentSize == 0;
    }

    // Trả về kích thước hiện tại của hàng đợi
    int size() const {
        return currentSize;
    }
};

// Định nghĩa một Node cho danh sách liên kết
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue {
private:
    Node* frontNode; // Con trỏ tới nút đầu tiên của hàng đợi
    Node* rearNode;  // Con trỏ tới nút cuối cùng của hàng đợi
    int currentSize; // Kích thước hiện tại của hàng đợi

public:
    // Constructor
    LinkedListQueue() : frontNode(nullptr), rearNode(nullptr), currentSize(0) {
        std::cout << "Linked List Queue created." << std::endl;
    }

    // Destructor
    ~LinkedListQueue() {
        while (!isEmpty()) {
            // Lấy ra từng phần tử để giải phóng bộ nhớ
            // Tương tự như dequeue nhưng không cần trả về giá trị
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
            currentSize--;
        }
        // Đảm bảo rearNode cũng được đặt về nullptr sau khi tất cả được xóa
        rearNode = nullptr;
        std::cout << "Linked List Queue destroyed." << std::endl;
    }

    // Thao tác Enqueue: Thêm phần tử vào cuối hàng đợi
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = newNode; // Nếu rỗng, nút mới vừa là front vừa là rear
        } else {
            rearNode->next = newNode; // Nút cuối hiện tại trỏ tới nút mới
        }
        rearNode = newNode; // Cập nhật rearNode thành nút mới
        currentSize++;
        std::cout << "Enqueued: " << value << std::endl;
    }

    // Thao tác Dequeue: Lấy phần tử từ đầu hàng đợi
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue Underflow: Cannot dequeue from an empty queue.");
        }
        Node* temp = frontNode;        // Lưu lại nút đầu tiên
        int dequeuedValue = temp->data; // Lấy giá trị
        frontNode = frontNode->next;   // Di chuyển frontNode đến nút tiếp theo
        delete temp;                   // Giải phóng bộ nhớ của nút đã xóa
        currentSize--;

        if (frontNode == nullptr) { // Nếu hàng đợi trở nên rỗng sau khi dequeue
            rearNode = nullptr;    // Đảm bảo rearNode cũng là nullptr
        }
        std::cout << "Dequeued: " << dequeuedValue << std::endl;
        return dequeuedValue;
    }

    // Thao tác Front/Peek: Xem phần tử đầu hàng đợi
    int frontValue() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty.");
        }
        return frontNode->data;
    }

    // Kiểm tra hàng đợi có rỗng không
    bool isEmpty() const {
        return frontNode == nullptr; // Hoặc currentSize == 0
    }

    // Trả về kích thước hiện tại của hàng đợi
    int size() const {
        return currentSize;
    }
};

// Hàm main chính để thử nghiệm
int main() {
    std::cout << "--- Testing Circular Array-based Queue ---" << std::endl;
    try {
        CircularArrayQueue myArrQueue(3); // Tạo hàng đợi mảng vòng với kích thước 3

        myArrQueue.enqueue(10);
        myArrQueue.enqueue(20);
        std::cout << "Front element: " << myArrQueue.frontValue() << std::endl; // Output: 10
        myArrQueue.enqueue(30);
        std::cout << "Queue size: " << myArrQueue.size() << std::endl; // Output: 3

        try {
            myArrQueue.enqueue(40); // Sẽ ném ngoại lệ Queue Overflow
        } catch (const std::overflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        myArrQueue.dequeue(); // Output: Dequeued: 10
        std::cout << "Front element after dequeue: " << myArrQueue.frontValue() << std::endl; // Output: 20
        myArrQueue.enqueue(40); // Thêm 40 vào vị trí trống (vị trí 0 do rear = (2+1)%3 = 0)
        std::cout << "Front element after enqueue: " << myArrQueue.frontValue() << std::endl; // Output: 20 (vẫn là 20)
        std::cout << "Queue size: " << myArrQueue.size() << std::endl; // Output: 3

        myArrQueue.dequeue(); // Output: Dequeued: 20
        myArrQueue.dequeue(); // Output: Dequeued: 30
        myArrQueue.dequeue(); // Output: Dequeued: 40

        std::cout << "Is Circular Array Queue empty? " << (myArrQueue.isEmpty() ? "Yes" : "No") << std::endl;

        try {
            myArrQueue.dequeue(); // Sẽ ném ngoại lệ Queue Underflow
        } catch (const std::underflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "General Error with CircularArrayQueue: " << e.what() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl << std::endl;


    std::cout << "--- Testing Linked List-based Queue ---" << std::endl;
    try {
        LinkedListQueue myLLQueue;

        myLLQueue.enqueue(100);
        myLLQueue.enqueue(200);
        std::cout << "Front element: " << myLLQueue.frontValue() << std::endl; // Output: 100
        myLLQueue.enqueue(300);
        std::cout << "Queue size: " << myLLQueue.size() << std::endl; // Output: 3

        myLLQueue.dequeue(); // Output: Dequeued: 100
        std::cout << "Front element after dequeue: " << myLLQueue.frontValue() << std::endl; // Output: 200
        myLLQueue.dequeue(); // Output: Dequeued: 200
        myLLQueue.dequeue(); // Output: Dequeued: 300

        std::cout << "Is Linked List Queue empty? " << (myLLQueue.isEmpty() ? "Yes" : "No") << std::endl;

        try {
            myLLQueue.dequeue(); // Sẽ ném ngoại lệ Queue Underflow
        } catch (const std::underflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "General Error with LinkedListQueue: " << e.what() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl << std::endl;


    std::cout << "--- Testing std::queue (STL) ---" << std::endl;
    // Khởi tạo một queue chứa số nguyên
    std::queue<int> mySTLQueue;

    std::cout << "Is std::queue empty? " << (mySTLQueue.empty() ? "Yes" : "No") << std::endl;

    // Thao tác push (enqueue)
    mySTLQueue.push(1000);
    mySTLQueue.push(2000);
    mySTLQueue.push(3000);
    std::cout << "Pushed 1000, 2000, 3000." << std::endl;

    // Thao tác front (peek)
    std::cout << "Front element: " << mySTLQueue.front() << std::endl; // Output: 1000

    // Thao tác back (xem phần tử cuối cùng)
    std::cout << "Back element: " << mySTLQueue.back() << std::endl; // Output: 3000

    // Thao tác size
    std::cout << "Size of std::queue: " << mySTLQueue.size() << std::endl; // Output: 3

    // Thao tác pop (dequeue)
    mySTLQueue.pop(); // Xóa 1000
    std::cout << "Popped front element." << std::endl;
    std::cout << "New front element: " << mySTLQueue.front() << std::endl; // Output: 2000

    mySTLQueue.pop(); // Xóa 2000
    mySTLQueue.pop(); // Xóa 3000

    std::cout << "Is std::queue empty? " << (mySTLQueue.empty() ? "Yes" : "No") << std::endl;

    // std::queue không tự ném ngoại lệ khi pop hoặc front một queue rỗng.
    // Bạn cần tự kiểm tra trước khi gọi pop/front trên queue rỗng.
    if (mySTLQueue.empty()) {
        std::cout << "Cannot pop/front from an empty std::queue (checked manually)." << std::endl;
        // mySTLQueue.front(); // Calling front() or back() on empty queue is undefined behavior
        // mySTLQueue.pop();   // Calling pop() on empty queue is undefined behavior
    }

    // Ví dụ với queue chứa string
    std::queue<std::string> mySTLStringQueue;
    mySTLStringQueue.push("First task");
    mySTLStringQueue.push("Second task");
    std::cout << "Front string: " << mySTLStringQueue.front() << std::endl; // Output: First task

    std::cout << "--------------------------------" << std::endl;

    return 0;
}