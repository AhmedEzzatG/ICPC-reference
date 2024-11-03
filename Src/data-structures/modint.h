#include <bits/stdc++.h>

using namespace std;

struct modint {
#define CUR (*this)
    static const int MOD = 1e9 + 7;
    int val;

    modint() {
        val = 0;
    }

    modint(const long long &a) {
        val = a % MOD;
        if (val < 0)
            val += MOD;
    }

    modint &operator+=(const modint &a) {
        if ((val += a.val) >= MOD)
            val -= MOD;
        return CUR;
    }

    modint operator+(const modint &a) const {
        modint c = CUR;
        c += a;
        return c;
    }

    modint &operator-=(const modint &a) {
        if ((val -= a.val) < 0)
            val += MOD;
        return CUR;
    }

    modint operator-(const modint &a) const {
        modint c = CUR;
        c -= a;
        return c;
    }

    modint operator*(const modint &a) const {
        return modint(1LL * this->val * a.val);
    }

    modint &operator*=(const modint &a) {
        CUR = CUR * a;
        return CUR;
    }

    modint operator/(const modint &a) {
        return CUR * power(a, MOD - 2);
    }

    modint &operator/=(const modint &a) {
        CUR = CUR / a;
        return CUR;
    }

    static modint power(modint x, long long y) {
        modint res = 1;
        while (y > 0) {
            if (y & 1)
                res *= x;
            x *= x;
            y >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &out, const modint &a) {
        out << a.val;
        return out;
    }

#undef CUR
};

