#include <iostream> // Dành cho std::cout, std::endl
#include <vector>   // Dành cho std::vector để biểu diễn đồ thị và mảng visited
#include <list>     // Dùng std::list cho danh sách kề để minh họa (vector<vector> cũng được)

// Class Graph để biểu diễn đồ thị
class Graph {
private:
int numVertices; // Số lượng đỉnh
    // Danh sách kề: adj[u] chứa danh sách các đỉnh v mà có cạnh từ u đến v
    // Sử dụng std::vector<std::list<int>> để dễ hình dung
    std::vector<std::list<int>> adj; 

    // Hàm đệ quy hỗ trợ cho DFS
    // u: đỉnh hiện tại đang được thăm
    // visited: mảng theo dõi các đỉnh đã được thăm
    void DFSUtil(int u, std::vector<bool>& visited) {
        // Đánh dấu đỉnh hiện tại là đã thăm và in ra
        visited[u] = true;
        std::cout << u << " ";

        // Duyệt qua tất cả các đỉnh kề với u
        // for (int v : adj[u]) { // C++11 range-based for loop
        for (std::list<int>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = *it;
            // Nếu đỉnh kề v chưa được thăm, gọi đệ quy DFS cho v
            if (!visited[v]) {
                DFSUtil(v, visited);
            }
        }
    }

public:
    // Constructor
    Graph(int V) : numVertices(V) {
        adj.resize(V); // Khởi tạo danh sách kề cho tất cả các đỉnh
    }

    // Hàm thêm cạnh vào đồ thị (đồ thị vô hướng)
    // u và v là chỉ số của các đỉnh (từ 0 đến numVertices - 1)
    void addEdge(int u, int v) {
        adj[u].push_back(v); // Thêm cạnh từ u đến v
        adj[v].push_back(u); // Thêm cạnh từ v đến u (đồ thị vô hướng)
    }

    // Hàm thực hiện thuật toán DFS chính
    // startVertex: đỉnh bắt đầu duyệt (chỉ số của đỉnh)
    void DFS(int startVertex) {
        // Kiểm tra đỉnh bắt đầu hợp lệ
        if (startVertex < 0 || startVertex >= numVertices) {
            std::cout << "Dinh bat dau khong hop le!" << std::endl;
            return;
        }

        // Mảng để theo dõi các đỉnh đã được thăm
        // Khởi tạo tất cả là false (chưa thăm)
        std::vector<bool> visited(numVertices, false);

        std::cout << "Thu tu duyet DFS bat dau tu dinh " << startVertex << ": ";
        
        // Gọi hàm đệ quy bắt đầu từ đỉnh nguồn
        DFSUtil(startVertex, visited);
        std::cout << std::endl;
    }

    // Hàm này kiểm tra xem đồ thị có liên thông không
    bool isConnected() {
        if (numVertices == 0) return true;

        std::vector<bool> visited(numVertices, false);
        
        // Bắt đầu DFS từ đỉnh 0 (hoặc bất kỳ đỉnh nào)
        DFSUtil(0, visited);

        // Sau khi DFS kết thúc, kiểm tra xem tất cả các đỉnh đã được thăm chưa
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i] && !adj[i].empty()) { // Nếu có đỉnh chưa thăm và không phải đỉnh cô lập
                return false;
            }
        }
        return true;
    }
    int getNumVertices() const {
        return numVertices;
    }
};

// Hàm main để kiểm thử
int main() {
    // Tạo một đồ thị với 6 đỉnh (0, 1, 2, 3, 4, 5)
    Graph g(6);

    // Thêm các cạnh
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    std::cout << "--- Thuat toan DFS (Duyet do thi) ---\n\n";

    // Thực hiện DFS từ đỉnh 0
    g.DFS(0); // Expected Output: Thu tu duyet DFS bat dau tu dinh 0: 0 1 3 4 2 5 (có thể khác tùy thứ tự trong adj list)

    std::cout << "\n--- Kiem tra tinh lien thong ---\n";
    std::cout << "Do thi co lien thong khong? " << (g.isConnected() ? "Co" : "Khong") << std::endl; // Expected: Co

    std::cout << "\n--- Test voi do thi khong lien thong ---\n";
    Graph g_disconnected(7); // Đồ thị 7 đỉnh
    g_disconnected.addEdge(0, 1);
    g_disconnected.addEdge(0, 2);
    g_disconnected.addEdge(3, 4); // Một thành phần riêng biệt
    g_disconnected.addEdge(5, 6); // Một thành phần riêng biệt khác

    g_disconnected.DFS(0); // Chỉ duyệt thành phần chứa 0 (0 1 2)
    std::cout << "Do thi (ngat ket noi) co lien thong khong? " << (g_disconnected.isConnected() ? "Co" : "Khong") << std::endl; // Expected: Khong (vi khong duyet het 3,4,5,6 tu dinh 0)

    // Để duyệt toàn bộ đồ thị không liên thông, bạn cần gọi DFS cho từng đỉnh chưa được thăm.
    std::cout << "\n--- Duyet toan bo do thi khong lien thong (bang cach lap qua cac thanh phan) ---\n";
    std::vector<bool> global_visited(g_disconnected.getNumVertices(), false);
    for (int i = 0; i < g_disconnected.getNumVertices(); ++i) {
        if (!global_visited[i]) {
            std::cout << "Bat dau DFS tu dinh " << i << ": ";
            // Can co mot phuong thuc DFSUtil moi trong class Graph
            // de co the truyen global_visited.
            // Hoac chuyen DFSUtil thanh public.
            // De don gian, ta se go lai cach goi.
            g_disconnected.DFS(i); // Goi lai ham DFS co san
        }
    }


    return 0;
}