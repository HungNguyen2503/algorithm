#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000; // hoặc giới hạn bạn cần
unsigned long long f[MAX];

unsigned long long fibonacci(int n) {
    if (f[n] != 0) {
        return f[n];
    }
    if (n<=2) {
        return 1;
    }
    f[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return f[n];
}

int main() {
    int n=9990;
    memset(f, 0, sizeof(f)); // Khởi tạo mảng f = 0
    cout << "F("<<n<<") = "<<fibonacci(n) << endl;
    return 0;
}