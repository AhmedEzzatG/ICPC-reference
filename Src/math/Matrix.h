#define ll long long
#define sz(s) (int)s.size()
#define REP(i,n) for(int i = 0;i<n;i++)
struct matrix {
	using T = int;
	using row = vector<T>;
	vector<vector<T>> v;
	matrix() {

	}
	matrix(int n, int m, T val = 0) :
			v(n, row(m, val)) {
	}
	int size() const {
		return v.size();
	}
	int cols() const {
		return v[0].size();
	}
	matrix operator*(T a) const {
		matrix rt = *this;
		REP(i,rt.size())
			REP(j,rt.cols())
				rt.v[i][j] *= a;
		return rt;
	}
	friend matrix operator*(T a, const matrix &b) {
		return (b * a);
	}
	friend matrix operator+(const matrix &a, const matrix &b) {
		assert(a.size() == b.size() && a.cols() == b.cols());
		matrix rt(a.size(), a.cols());
		REP(i,rt.size())
			REP(j,rt.cols())
				rt.v[i][j] = a.v[i][j] + b.v[i][j];
		return rt;
	}
	friend matrix operator*(const matrix &a, const matrix &b) {
		assert(a.cols() == b.size());
		matrix rt(a.size(), b.cols());
		REP(i,rt.size())
			REP(k,a.cols())
			{
				if (a.v[i][k] == 0)
					continue;
				REP(j,rt.cols())
					rt.v[i][j] += a.v[i][k] * b.v[k][j];
			}
		return rt;
	}
};

matrix identity(int n) {
	matrix r(n, n);
	for (int i = 0; i < n; i++)
		r.v[i][i] = 1;
	return r;
}

matrix addIdentity(const matrix &a) {
	matrix rt = a;
	REP(i,a.size())
		rt.v[i][i]++;
	return rt;
}

matrix power(matrix a, long long y) {
	assert(y >= 0 && a.size() == a.cols());
	matrix rt = identity(a.size());
	while (y > 0) {
		if (y & 1)
			rt = rt * a;
		a = a * a;
		y >>= 1;
	}
	return rt;
}

matrix sumPower(const matrix &a, ll k) {
	if (k == 0)
		return matrix(sz(a), sz(a));
	if (k & 1)
		return a * addIdentity(sumPower(a, k - 1));
	return (sumPower(a, k >> 1) * addIdentity(power(a, k >> 1)));
}

/* return matrix contains
	a^k         0
a^1+a^2.. a^k   I
*/

matrix sumPowerV2(const matrix &a, ll k) {
	int n = sz(a);
	matrix rt(2 * n, 2 * n);
	REP(i,n)
		REP(j,n)
		{
			rt.v[i][j] = a.v[i][j];
			rt.v[i + n][j] = a.v[i][j];
		}
	for (int i = n; i < 2 * n; i++)
		rt.v[i][i] = 1;
	return power(rt, k);
}
