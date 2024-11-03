typedef unsigned long long ull;

// nCr = n!/((n-r)! * r!)
// nCr(n,r) = nCr(n,n-r)
// nPr = n!/(n-r)!
// nPr_circle = nPr/r
// nCr(n,r) = pascal[n][r]
// catalan[n] = nCr(2n,n)/(n+1)

ull nCr(int n, int r) {
	if (r > n)
		return 0;
	r = max(r, n - r);
	ull ans = 1, div = 1, i = r + 1;
	while (i <= n) {
		ans *= i++;
		ans /= div++;
	}
	return ans;
}

ull nPr(int n, int r) {
	if (r > n)
		return 0;
	ull p = 1, i = n - r + 1;
	while (i <= n)
		p *= i++;
	return p;
}

vector<vector<ull>> pascalTriangle(int n) {
	vector<vector<ull>> pascal(n + 1, vector<ull>(n + 1));
	for (int i = 0; i <= n; i++) {
		pascal[i][i] = pascal[i][0] = 1;
		for (int j = 1; j < n; j++)
			pascal[i][j] = pascal[i - 1][j] + pascal[i - 1][j - 1];
	}
	return pascal;
}

// return catalan number n-th using dp O(n^2)//max = 35 then overflow
vector<ull> catalanNumber(int n) {
	vector<ull> catalan(n + 1);
	catalan[0] = catalan[1] = 1;
	for (int i = 2; i <= n; i++) {
		ull &rt = catalan[i];
		for (int j = 0; j < n; j++)
			rt += catalan[j] * catalan[n - j - 1];
	}
	return catalan;
}

// count number of paths in matrix n*m 
// go to right or down only
ull countNumberOfPaths(int n, int m) {
	return nCr(n + m - 2, n - 1);
}

const int N = 1e5 + 100;
const int MOD = 1e9 + 7;
ll fact[N];
ll inv[N]; //mod inverse for i
ll invfact[N]; //mod inverse for i!
void factInverse() {
	fact[0] = inv[1] = fact[1] = invfact[0] = invfact[1] = 1;
	for (long long i = 2; i < N; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
		inv[i] = MOD - (inv[MOD % i] * (MOD / i) % MOD);
		invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
	}
}

ll nCr(int n, int r) {
	if (r > n)
		return 0;
	return (((fact[n] * invfact[r]) % MOD) * invfact[n - r]) % MOD;
}