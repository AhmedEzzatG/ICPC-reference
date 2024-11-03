

struct node {
	node() { //set Default value

	}
	node(const node &a, const node &b) {

	}
	void apply(int val) {

	}
};

struct segment_tree {
	int n; //0 to n-1
	vector<node> tree;
	segment_tree(int n) {
		resize(n);
		build();
	}
	template<typename T>
	segment_tree(const vector<T> &arr) {
		resize(arr.size());
		for (int i = 0; i < arr.size(); i++)
			tree[n + i] = arr[i];
		build();
	}
	void resize(int n) {
		int p = 1;
		while (p < n)
			p <<= 1;
		this->n = p;
		tree = vector < node > (p << 1);
	}
	void build() {
		for (int i = n - 1; i > 0; i--)
			tree[i] = node(tree[i << 1], tree[i << 1 | 1]);
	}
	template<typename T>
	void update(int p, const T &value) {
		tree[p += n].apply(value);
		for (int i = p / 2; i > 0; i >>= 1)
			tree[i] = node(tree[i << 1], tree[i << 1 | 1]);
	}
	node query(int l, int r) {  //[l, r]
		node resl, resr;  //set default value in node
		for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
				resl = node(resl, tree[l]);
				l++;
			}
			if (r & 1) {
				r--;
				resr = node(tree[r], resr);
			}
		}
		return node(resl, resr);
	}
	int kth_one(int k, int i = 1) {
		if (k > tree[i])
			return -1;
		if (i >= n)
			return i - n;
		if (tree[i << 1] >= k)
			return kth_one(k, i << 1);
		return kth_one(k - tree[i << 1], i << 1 | 1);
	}
};

