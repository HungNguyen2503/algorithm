#include <bits/stdc++.h>

// Cấu trúc của một Nút
struct Node {
    int data;     // Dữ liệu của nút
    Node* next;   // Con trỏ tới nút kế tiếp

    // Constructor để tạo nút mới dễ dàng
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head; // Con trỏ tới nút đầu tiên

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor để giải phóng bộ nhớ
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // Các phương thức sẽ được định nghĩa bên dưới
    void printList();
    void insertAtBeginning(int data);
    void insertAtEnd(int data);
    void deleteFromBeginning();
    void deleteFromEnd();
    void deleteByValue(int key);
    bool search(int key);
};

void LinkedList::printList() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

void LinkedList::insertAtBeginning(int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

void LinkedList::insertAtEnd(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = newNode;
}

void LinkedList::deleteFromBeginning() {
    if (head == nullptr) {
        return; // Danh sách rỗng
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

void LinkedList::deleteFromEnd() {
    if (head == nullptr) return; // Rỗng

    if (head->next == nullptr) { // Chỉ có một nút
        delete head;
        head = nullptr;
        return;
    }

    // Tìm nút kế cuối
    Node* second_last = head;
    while (second_last->next->next != nullptr) {
        second_last = second_last->next;
    }

    delete second_last->next; // Xóa nút cuối
    second_last->next = nullptr;
}

void LinkedList::deleteByValue(int key) {
    if (head == nullptr) return;

    Node* temp = head;
    Node* prev = nullptr;

    // Nếu nút cần xóa là head
    if (temp != nullptr && temp->data == key) {
        head = temp->next;
        delete temp;
        return;
    }

    // Tìm nút cần xóa
    while (temp != nullptr && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy
    if (temp == nullptr) return;

    // Nối nút trước với nút sau
    prev->next = temp->next;
    delete temp; // Xóa nút hiện tại
}

bool LinkedList::search(int key) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == key) {
            return true; // Tìm thấy
        }
        current = current->next;
    }
    return false; // Không tìm thấy
}

int main() {
    LinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtBeginning(5);
    list.printList();

    list.insertAtEnd(30); 

    std::cout << "Tim kiem 10: " << (list.search(10) ? "Tim thay" : "Khong tim thay") << std::endl;
    std::cout << "Tim kiem 99: " << (list.search(99) ? "Tim thay" : "Khong tim thay") << std::endl;

    list.deleteByValue(10); 
    list.printList();

    list.deleteFromBeginning();

    list.deleteFromEnd();
    list.printList();

    return 0;
}