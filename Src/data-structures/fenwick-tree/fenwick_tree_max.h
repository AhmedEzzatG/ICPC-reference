#include<bits/stdc++.h>
using namespace std;

//fenwick tree for get maximum from 1 to idx
// update a[idx] = max(a[idx],val)
//can't remove values
template<typename T>
struct fenwick_tree {
	vector<T> BIT;
	int n;
	fenwick_tree(int n) :
			n(n), BIT(n + 1) {
	}
	T getMax(int idx) {
		T mx = numeric_limits<T>::min();
		while (idx) {
			mx = max(mx, BIT[idx]);
			idx -= (idx & -idx);
		}
		return mx;
	}
	void add(int idx, T val) {
		assert(idx != 0);
		while (idx <= n) {
			BIT[idx] = max(BIT[idx], val);
			idx += (idx & -idx);
		}
	}
};
