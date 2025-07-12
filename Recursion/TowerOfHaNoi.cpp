#include <bits/stdc++.h>
using namespace std;

void towerOfHanoi(int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << destination << endl;
        return;
    }
    towerOfHanoi(n - 1, source, destination, auxiliary);
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;
    towerOfHanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int n = 3; // Số lượng đĩa
    towerOfHanoi(n, 'A', 'B', 'C'); // A là nguồn, B là trung gian, C là đích
    return 0;
}
