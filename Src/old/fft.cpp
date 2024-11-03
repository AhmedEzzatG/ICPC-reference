#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef valarray<complex<double>> polynomial;
polynomial fft(const polynomial &x, int sign = -1) {
	int N = x.size();
	if (N == 1)
		return x;
	polynomial even = x[slice(0, N / 2, 2)];
	polynomial odd = x[slice(1, N / 2, 2)];
	even = fft(even, sign);
	odd = fft(odd, sign);
	polynomial res(N);
	complex<double> cm1 = 1, cm2 = exp(
			complex<double>(0, sign * 2 * acos(-1) / N));
	for (int k = 0; k < N / 2; k++) {
		res[k] = even[k] + cm1 * odd[k];
		res[k + N / 2] = even[k] - cm1 * odd[k];
		cm1 *= cm2;//the best is to calc it in preprocessing
	}
	return res;
}

polynomial inv_fft(const polynomial &x) {
	complex<double> N = x.size();
	return fft(x, 1) / N;
}

valarray<int> mul(const valarray<int> &a, const valarray<int> &b) {
	int adeg = (int) a.size() - 1, bdeg = (int) b.size() - 1;
	int N = 1;
	while (N <= adeg + bdeg)
		N <<= 1;
	polynomial A(N), B(N);
	for (int i = 0; i < a.size(); i++)
		A[i] = a[i];
	for (int i = 0; i < b.size(); i++)
		B[i] = b[i];
	polynomial m = inv_fft(fft(A) * fft(B));

	while (N > 1 && (int) round(m[N - 1].real()) == 0)
		N--;
	valarray<int> rt(N);
	for (int i = 0; i < N; i++)
		rt[i] = (int) round(m[i].real());
	return rt;
}
