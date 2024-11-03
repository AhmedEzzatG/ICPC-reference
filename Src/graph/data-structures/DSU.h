struct DSU {
	vector<int> rank, parent, size;
	int forsets;
	DSU(int n) {
		size = rank = parent = vector<int>(n + 1, 1);
		forsets = n;
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
		}
	}
	int find_set(int v) {
		if (v == parent[v])
			return v;
		return parent[v] = find_set(parent[v]);
	}
	void link(int par, int node) {
		parent[node] = par;
		size[par] += size[node];
		if (rank[par] == rank[node])
			rank[par]++;
		forsets--;
	}
	bool union_sets(int v, int u) {
		v = find_set(v), u = find_set(u);
		if (v != u) {
			if (rank[v] < rank[u])
				swap(v, u);
			link(v, u);
		}
		return v != u;
	}
};
