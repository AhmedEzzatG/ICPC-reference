#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct fenwick_tree_2d {
#define Lbit(x) (x&-x)
	int n, m;
	vector<vector<T>> BIT;
	fenwick_tree_2d(int n, int m) :
			n(n), m(m), BIT(n + 1, vector<T>(m + 1)) {
	}
	T getAccum(int i, int j) {
		T sum = 0;
		for (; i; i -= Lbit(i))
			for (int idx = j; idx > 0; idx -= Lbit(idx))
				sum += BIT[i][idx];
		return sum;
	}
	void add(int i, int j, int val) {
		assert(i != 0 && j != 0);
		for (; i <= n; i += Lbit(i))
			for (int idx = j; idx <= m; idx += Lbit(idx))
				BIT[i][idx] += val;
	}
	T getRectangeSum(int x1, int y1, int x2, int y2) {
		if (y1 > y2)
			swap(y1, y2);
		if (x1 > x2)
			swap(x1, x2);
		return getAccum(x2, y2) - getAccum(x1 - 1, y2) - getAccum(x2, y1 - 1)
				+ getAccum(x1 - 1, y1 - 1);
	}
};
