#include <iostream>
using namespace std;

long long EMR(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = EMR(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
int main() {
    int a, b, x, y;
    cout << "Nhap a: ";
    cin >> a;
    cout << "Nhap b: ";
    cin >> b;
    cout << "UCLN cua a va b: " << EMR(a, b, x, y) << "\n";
    cout << "Gia tri x sao cho ax + by = gcd(a,b): " << x << "\n";
    cout << "Gia tri y sao cho ax + by = gcd(a,b): " << y << "\n";
    return 0;
}
