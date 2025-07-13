#include <iostream> // Dành cho std::cout, std::endl
#include <vector>   // Dành cho std::vector để biểu diễn đồ thị và mảng visited
#include <queue>    // Dành cho std::queue
#include <map>      // Dành cho std::map để ánh xạ tên đỉnh thành chỉ số (tùy chọn)

// Class Graph để biểu diễn đồ thị
class Graph {
private:
    int numVertices; // Số lượng đỉnh
    std::vector<std::vector<int>> adj; // Danh sách kề (Adjacency List)

public:
    // Constructor
    Graph(int V) : numVertices(V) {
        adj.resize(V); // Khởi tạo danh sách kề cho tất cả các đỉnh
    }

    // Hàm thêm cạnh vào đồ thị
    // u và v là chỉ số của các đỉnh (từ 0 đến numVertices - 1)
    void addEdge(int u, int v) {
        adj[u].push_back(v); // Thêm cạnh từ u đến v
        adj[v].push_back(u); // Thêm cạnh từ v đến u (đồ thị vô hướng)
        // Nếu là đồ thị có hướng, chỉ cần adj[u].push_back(v);
    }

    // Hàm thực hiện thuật toán BFS
    // startVertex: đỉnh bắt đầu duyệt (chỉ số của đỉnh)
    void BFS(int startVertex) {
        // Kiểm tra đỉnh bắt đầu hợp lệ
        if (startVertex < 0 || startVertex >= numVertices) {
            std::cout << "Dinh bat dau khong hop le!" << std::endl;
            return;
        }

        // Mảng để theo dõi các đỉnh đã được thăm
        // Khởi tạo tất cả là false (chưa thăm)
        std::vector<bool> visited(numVertices, false);

        // Hàng đợi cho BFS
        std::queue<int> q;

        // 1. Đưa đỉnh bắt đầu vào hàng đợi và đánh dấu đã thăm
        visited[startVertex] = true;
        q.push(startVertex);

        std::cout << "Thu tu duyet BFS bat dau tu dinh " << startVertex << ": ";

        // 2. Lặp chừng nào hàng đợi còn phần tử
        while (!q.empty()) {
            // Lấy đỉnh ở đầu hàng đợi
            int u = q.front();
            q.pop();

            // Xử lý đỉnh u (ví dụ: in ra)
            std::cout << u << " ";

            // Duyệt qua tất cả các đỉnh kề với u
            for (int v : adj[u]) {
                // Nếu đỉnh kề v chưa được thăm
                if (!visited[v]) {
                    visited[v] = true; // Đánh dấu đã thăm
                    q.push(v);         // Đưa vào hàng đợi
                }
            }
        }
        std::cout << std::endl;
    }

    // Hàm BFS có thể tìm đường đi ngắn nhất (không trọng số)
    // Trả về một vector chứa khoảng cách từ đỉnh nguồn đến mỗi đỉnh khác
    // Nếu không thể đến được, khoảng cách là -1 (hoặc một số lớn nào đó)
    std::vector<int> shortestPathBFS(int startVertex) {
        std::vector<int> distance(numVertices, -1); // Khoảng cách từ startVertex
        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;

        visited[startVertex] = true;
        distance[startVertex] = 0; // Khoảng cách từ đỉnh nguồn đến chính nó là 0
        q.push(startVertex);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    distance[v] = distance[u] + 1; // Khoảng cách của v = khoảng cách của u + 1
                    q.push(v);
                }
            }
        }
        return distance;
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
    g.addEdge(2, 5); // Using a more direct add_edge for simplicity, previously addEdge

    std::cout << "--- Thuat toan BFS (Duyet do thi) ---\n\n";

    // Thực hiện BFS từ đỉnh 0
    g.BFS(0); // Expected Output: Thu tu duyet BFS bat dau tu dinh 0: 0 1 2 3 4 5

    std::cout << "\n--- Tim duong di ngan nhat bang BFS (khong trong so) ---\n";
    std::vector<int> distances = g.shortestPathBFS(0);
    std::cout << "Khoang cach tu dinh 0 den:\n";
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] != -1) {
            std::cout << "  Dinh " << i << ": " << distances[i] << std::endl;
        } else {
            std::cout << "  Dinh " << i << ": Khong the den duoc" << std::endl;
        }
    }
    // Expected Output:
    // Dinh 0: 0
    // Dinh 1: 1
    // Dinh 2: 1
    // Dinh 3: 2
    // Dinh 4: 2
    // Dinh 5: 2

    std::cout << "\n--- Test voi do thi khong lien thong ---\n";
    Graph g_disconnected(4);
    g_disconnected.addEdge(0, 1);
    g_disconnected.addEdge(2, 3); // 2 và 3 là một thành phần riêng biệt
    g_disconnected.BFS(0); // Expected: 0 1
    g_disconnected.BFS(2); // Expected: 2 3

    return 0;
}