#include <iostream>
using namespace std;

long long ltnp(int a, int b, int m) {
    long long kq = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) {
            kq = (kq * a) % m;
        }
        a = (a * a) % m;
        b /= 2;
    }
    return kq;
}

int main() {
    int a, b, m;
    cout << "Nhap a: ";
    cin >> a;
    cout << "Nhap b: ";
    cin >> b;
    cout << "Nhap m: ";
    cin >> m;
    cout << "Ket qua a^b % m: " << ltnp(a, b, m) << "\n";
    return 0;
}
