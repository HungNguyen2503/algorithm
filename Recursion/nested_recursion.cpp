#include <iostream>
using namespace std;

int ackerman(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackerman(m - 1, 1);
    else
        return ackerman(m - 1, ackerman(m, n - 1));
}

int main() {
    cout << ackerman(3, 1) << endl;
    return 0;
}
