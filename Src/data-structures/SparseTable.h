template<typename T>
struct sparse_table {
	vector<vector<T>> sparseTable;
	using F = function<T(T,T)>;
	F merge;
	static int LOG2(int x) { //floor(log2(x))
		return 31 - __builtin_clz(x);
	}
	sparse_table(vector<T> &v, F merge) :
			merge(merge) {
		int n = v.size();
		int logN = LOG2(n);
		sparseTable = vector < vector < T >> (logN + 1);
		sparseTable[0] = v;
		for (int k = 1, len = 1; k <= logN; k++, len <<= 1) {
			sparseTable[k].resize(n);
			for (int i = 0; i + len < n; i++)
				sparseTable[k][i] = merge(sparseTable[k - 1][i],
						sparseTable[k - 1][i + len]);
		}
	}
	T query(int l, int r) {
		int k = LOG2(r - l + 1); // max k ==> 2^k <= length of range
		//check first 2^k from left and last 2^k from right //overlap
		return merge(sparseTable[k][l], sparseTable[k][r - (1 << k) + 1]);
	}
	T query_shifting(int l, int r) {
		T res;
		bool first = true;
		for (int i = (int) sparseTable.size() - 1; i >= 0; i--)
			if (l + (1 << i) - 1 <= r) {
				if (first)
					res = sparseTable[i][l];
				else
					res = merge(res, sparseTable[i][l]);
				first = false;
				l += (1 << i);
			}
		return res;
	}
};
