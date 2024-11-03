const int ITER = 4;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

__int128 power(__int128 x, __int128 y, ll mod) {
    if (y == 0)
        return 1;
    if (y & 1)return (x * power(x, y - 1, mod)) % mod;
    __int128 r = power(x, y >> 1, mod);
    return (r * r) % mod;
}

bool millerTest(ll n, ll d) {
    __int128 a = uniform_int_distribution<ll>(2, n - 2)(rng);
    a = power(a, d, n);
    if (a == 1 || a == n - 1)
        return true;
    d <<= 1;
    while (d != n - 1) {
        a = a * a % n;
        if (a == 1) return false;
        if (a == n - 1) return true;
        d <<= 1;
    }
    return false;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (!(n & 1)) return false;
    ll d = n - 1;
    while (!(d & 1))
        d >>= 1;
    for (int i = 0; i < ITER; i++)
        if (!millerTest(n, d))
            return false;
    return true;
}

bool isPrimeSquare(ll n) {
    ll sq = sqrt(n);
    if (sq * sq < n) {
        sq++;
        if (sq * sq != n)return false;
    }
    return is_prime(sq);
}
