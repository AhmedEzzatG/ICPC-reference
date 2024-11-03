#define ll long long

ll power(ll x, ll y, int mod) {
	if (y == 0)
		return 1;
	if (y == 1)
		return x % mod;
	ll r = power(x, y >> 1, mod);
	return (((r * r) % mod) * power(x, y & 1, mod)) % mod;
}

// return a ^ 1 + a ^ 2 + a ^ 3 + .... a ^ k
ll sumPower(ll a, ll k, int mod) {
	if (k == 1) return a % mod;
	ll half = sumPower(a, k / 2, mod);
	ll p = half * power(a, k / 2, mod) % mod;
	p = (p + half) % mod;
	if (k & 1) p = (p + power(a, k, mod)) % mod;
	return p;
}

ll modInverse(ll b, ll mod) { // if mod is Prime
	return power(b, mod - 2, mod);
}

ll modInverse(ll b, ll mod) { // if mod is not Prime,gcd(a,b) must be equal 1
	return power(b, phi_function(mod) - 1, mod);
}

// (a^n)%p=result,return n
int getPower(int a, int result, int mod) {
	int sq = sqrt(mod);
	map<int, int> mp;
	ll r = 1;
	for (int i = 0; i < sq; i++) {
		if (mp.find(r) == mp.end())
			mp[r] = i;
		r = (r * a) % mod;
	}
	ll tmp = modInverse(r, mod);
	ll cur = result;
	for (int i = 0; i <= mod; i += sq) {
		if (mp.find(cur) != mp.end())
			return i + mp[cur];
		cur = (cur * tmp) % mod;//val/(a^sq)
	}
	return INF;
}
