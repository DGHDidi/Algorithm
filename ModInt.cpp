template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        b >>= 1;
        a = a * a;
    }
    return res;
}

template<i64 P>
struct ModInt {
    i64 x;
    constexpr ModInt() : x{} {}
    constexpr ModInt(i64 x) : x{norm(x % P)} {}
    constexpr i64 norm(i64 x) const {
        if (x >= P) {
            x -= P;
        } else if (x < 0) {
            x += P;
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(P - x);
        return res;
    }
    constexpr ModInt inv() const {
        return power(*this, P - 2);
    }
    constexpr ModInt operator+=(ModInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr ModInt operator-=(ModInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr ModInt operator*=(ModInt rhs) & {
        x = norm(x * rhs.x % P);
        return *this;
    }
    constexpr ModInt operator/=(ModInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr ModInt operator+(ModInt lhs, ModInt rhs) {
        ModInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr ModInt operator-(ModInt lhs, ModInt rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr ModInt operator*(ModInt lhs, ModInt rhs) {
        ModInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr ModInt operator/(ModInt lhs, ModInt rhs) {
        ModInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr bool operator==(ModInt lhs, ModInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(ModInt lhs, ModInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr istream &operator>>(istream &is, ModInt &a) {
        i64 v;
        is >> v;
        a = ModInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const ModInt &a) {
        return os << a.val();
    }
};

using mint = ModInt<998244353>;
