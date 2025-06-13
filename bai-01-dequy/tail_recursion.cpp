#include <bits/stdc++.h>
using namespace std;
int gcd(int m, int n) {
    if(m<n) return gcd(n,m);
    int r=m%n;
    cout << r << " \n";
    if(r==0) return n;
    else return gcd(n,r);
}
int main() {
    int m=5, n=25  ;
    int result = gcd(m, n);
    cout << "GCD of " << m << " and " << n << " is: " << result << endl;
    return 0;
}