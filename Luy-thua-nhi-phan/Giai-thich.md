# Lũy thừa nhị phân

## 1. Khái niệm

Lũy thừa nhị phân (Binary Exponentiation) là thuật toán tính `a^n` với độ phức tạp **O(log n)** thay vì **O(n)**.

## 2. Ý tưởng

Dựa vào:

- Nếu `n` lẻ: `a^n = a * a^(n-1)`

- Nếu `n` chẵn: `a^n = (a^(n/2))^2`

Trong cách cài đặt lặp:

- Nếu `n` lẻ → `res *= a`
- Mỗi vòng → `a *= a`
- Mỗi vòng → `n /= 2`

## 3. Code

```cpp
long long binaryPow(long long a, long long n) {
    long long res = 1;

    while (n > 0) {
        if (n % 2 == 1)
            res *= a;

        a *= a;
        n /= 2;
    }

    return res;
}
