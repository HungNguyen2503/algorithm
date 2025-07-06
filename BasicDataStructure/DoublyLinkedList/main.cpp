#include <bits/stdc++.h>

// Cấu trúc của một Nút trong danh sách liên kết đôi
struct Node {
    int data;
    Node* next; // Con trỏ tới nút kế tiếp
    Node* prev; // Con trỏ tới nút phía trước

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Lớp quản lý danh sách liên kết đôi
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor và Destructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Các phương thức thao tác
    void insertAtBeginning(int data);
    void insertAtEnd(int data);
    void deleteByValue(int key);
    void printForward();
    void printBackward();
};

void DoublyLinkedList::insertAtBeginning(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) { // Nếu danh sách rỗng
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::insertAtEnd(int data) {
    Node* newNode = new Node(data);
    if (tail == nullptr) { // Nếu danh sách rỗng
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::deleteByValue(int key) {
    Node* current = head;

    // Tìm nút có giá trị key
    while (current != nullptr && current->data != key) {
        current = current->next;
    }

    // Nếu không tìm thấy hoặc danh sách rỗng
    if (current == nullptr) {
        return;
    }

    // Nếu nút cần xóa là head
    if (current == head) {
        head = current->next;
    }
    // Nếu nút cần xóa là tail
    if (current == tail) {
        tail = current->prev;
    }

    // Cập nhật con trỏ của nút liền trước
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }

    // Cập nhật con trỏ của nút liền sau
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current; // Giải phóng bộ nhớ
}

// Duyệt từ đầu đến cuối
void DoublyLinkedList::printForward() {
    Node* current = head;
    std::cout << "Forward:  head -> ";
    while (current != nullptr) {
        std::cout << current->data << " <-> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Duyệt từ cuối về đầu
void DoublyLinkedList::printBackward() {
    Node* current = tail;
    std::cout << "Backward: tail -> ";
    while (current != nullptr) {
        std::cout << current->data << " <-> ";
        current = current->prev;
    }
    std::cout << "nullptr" << std::endl;
}


int main() {
    DoublyLinkedList ddl;
    
    ddl.insertAtEnd(10);
    ddl.insertAtEnd(20);
    ddl.insertAtEnd(30);
    ddl.insertAtBeginning(5);

    ddl.printForward();
    ddl.printBackward();

    std::cout << "\n--- Xoa nut co gia tri 20 ---\n";
    ddl.deleteByValue(20);
    ddl.printForward();

    std::cout << "\n--- Xoa nut dau (5) ---\n";
    ddl.deleteByValue(5);
    ddl.printForward();

    std::cout << "\n--- Xoa nut cuoi (30) ---\n";
    ddl.deleteByValue(30);
    ddl.printForward();
    ddl.printBackward();

    return 0;
}

