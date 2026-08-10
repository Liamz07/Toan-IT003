# THUẬT TOÁN EUCLID MỞ RỘNG

## 1. Khái niệm

Thuật toán Euclid mở rộng (Extended Euclidean Algorithm) là phiên bản mở rộng
của thuật toán Euclid.

Ngoài việc tìm:

    gcd(a, b)

thuật toán còn tìm hai số nguyên `x, y` sao cho:

    a*x + b*y = gcd(a, b)

Đây là **đẳng thức Bezout**.

---

## 2. Tư tưởng thuật toán

Thuật toán Euclid dựa trên tính chất:

    gcd(a, b) = gcd(b, a % b)

Vì vậy, ta tiếp tục gọi đệ quy:

    extendedGCD(a, b)
        ↓
    extendedGCD(b, a % b)
        ↓
    ...
        ↓
    extendedGCD(g, 0)

Khi `b = 0`:

    gcd(a, 0) = a

Đây là trường hợp cơ sở.

Sau đó, khi đệ quy quay ngược, ta tính lại `x, y`.

---

## 3. Trường hợp cơ sở

Khi:

    b = 0

Ta có:

    gcd(a, 0) = a

Cần tìm `x, y` sao cho:

    a*x + 0*y = a

Chọn:

    x = 1
    y = 0

Do đó:

    a*1 + 0*0 = a

Code:

    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

---

## 4. Công thức truy hồi

Giả sử lời gọi đệ quy nhỏ hơn trả về:

    b*x1 + (a % b)*y1 = g

Ta có:

    a % b = a - (a / b)*b

Thay vào:

    b*x1 + [a - (a / b)*b]*y1 = g

Khai triển:

    a*y1 + b*[x1 - (a / b)*y1] = g

So sánh với:

    a*x + b*y = g

Suy ra:

    x = y1
    y = x1 - (a / b)*y1

Code:

    x = y1;
    y = x1 - (a / b) * y1;

---

## 5. Code đầy đủ

    long long extendedGCD(long long a, long long b,
                          long long &x, long long &y) {

        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }

        long long x1, y1;

        long long g = extendedGCD(b, a % b, x1, y1);

        x = y1;
        y = x1 - (a / b) * y1;

        return g;
    }

Kết quả của hàm:

    g = gcd(a, b)

và:

    a*x + b*y = g

---

## 6. Ý nghĩa của `return g`

Dòng:

    long long g = extendedGCD(b, a % b, x1, y1);

nhận giá trị `return` từ lời gọi đệ quy bên dưới.

Giá trị `g` cuối cùng được tạo ra ở trường hợp cơ sở:

    if (b == 0)
        return a;

Sau đó `g` được truyền ngược lên qua các lần gọi đệ quy.

Ví dụ:

    extendedGCD(30, 18)
            ↓
    extendedGCD(18, 12)
            ↓
    extendedGCD(12, 6)
            ↓
    extendedGCD(6, 0)
            ↓
          return 6

Sau đó:

    extendedGCD(12, 6)  → return 6
    extendedGCD(18, 12) → return 6
    extendedGCD(30, 18) → return 6

Vì vậy:

    g = gcd(30, 18) = 6

Lưu ý:

- `g` được truyền ngược lên và không thay đổi.
- `x, y` được tính lại ở từng tầng khi đệ quy quay ngược.

---

## 7. Ví dụ

Tìm `gcd(30, 18)` và `x, y`.

Euclid:

    30 = 18*1 + 12
    18 = 12*1 + 6
    12 = 6*2 + 0

Suy ra:

    gcd(30, 18) = 6

Euclid mở rộng:

    6 = 18 - 12
      = 18 - (30 - 18)
      = 2*18 - 30

Do đó:

    30*(-1) + 18*(2) = 6

Kết quả:

    g = 6
    x = -1
    y = 2

---

# 8. Ứng dụng: Nghịch đảo modulo

Muốn tìm nghịch đảo modulo của `a mod m`, cần tìm `x` sao cho:

    a*x ≡ 1 (mod m)

Nghịch đảo modulo tồn tại khi:

    gcd(a, m) = 1

Euclid mở rộng tìm được:

    a*x + m*y = gcd(a, m)

Nếu:

    gcd(a, m) = 1

thì:

    a*x + m*y = 1

Lấy modulo `m` hai vế:

    a*x + m*y ≡ 1 (mod m)

Vì:

    m*y ≡ 0 (mod m)

nên:

    a*x ≡ 1 (mod m)

Do đó:

    x = a^(-1) mod m

---

## 9. Ví dụ tìm nghịch đảo

Tìm:

    3^(-1) mod 10

Euclid mở rộng cho:

    3*(-3) + 10*(1) = 1

Vậy:

    x = -3

Ta có:

    3*(-3) ≡ 1 (mod 10)

Đưa `x` về khoảng `[0, m-1]`:

    x = (-3 % 10 + 10) % 10
      = 7

Vậy:

    3^(-1) ≡ 7 (mod 10)

Kiểm tra:

    3*7 = 21
    21 % 10 = 1

---

## 10. Code tìm nghịch đảo modulo

    long long modInverse(long long a, long long m) {
        long long x, y;

        long long g = extendedGCD(a, m, x, y);

        // Không tồn tại nghịch đảo
        if (g != 1)
            return -1;

        // Đưa x về [0, m - 1]
        x = (x % m + m) % m;

        return x;
    }

Ví dụ:

    long long x = modInverse(3, 10);

Kết quả:

    x = 7

---

## 11. Tại sao phải kiểm tra `gcd(a, m) == 1`?

Nghịch đảo modulo của `a mod m` tồn tại khi và chỉ khi:

    gcd(a, m) = 1

Nếu:

    gcd(a, m) != 1

thì không thể tìm được `x` thỏa mãn:

    a*x ≡ 1 (mod m)

Ví dụ:

    a = 6
    m = 10

Ta có:

    gcd(6, 10) = 2 != 1

⇒ `6` không có nghịch đảo modulo `10`.

---

# 12. Tóm tắt

### Euclid thường

    gcd(a, b)
        ↓
    gcd(b, a % b)
        ↓
    ...
        ↓
    gcd

### Euclid mở rộng

    gcd(a, b)
        ↓
    gcd(b, a % b)
        ↓
    ...
        ↓
    gcd + x + y

Sao cho:

    a*x + b*y = gcd(a, b)

### Tìm nghịch đảo modulo

    extendedGCD(a, m, x, y)

Nếu:

    gcd(a, m) == 1

thì:

    a*x + m*y = 1

Lấy modulo `m`:

    a*x ≡ 1 (mod m)

Suy ra:

    x = a^(-1) mod m

Nếu `x < 0`, chuẩn hóa:

    x = (x % m + m) % m

---

## 13. Công thức cần nhớ

    gcd(a, b) = gcd(b, a % b)

    a*x + b*y = gcd(a, b)

    x = y1

    y = x1 - (a / b)*y1

    gcd(a, m) = 1
        ⇒ a^(-1) tồn tại mod m

    a*x + m*y = 1
        ⇒ a*x ≡ 1 (mod m)
        ⇒ x là nghịch đảo của a mod m
