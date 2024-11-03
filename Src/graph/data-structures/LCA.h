class LCA {
	int n, logN, root = 1;
	vector<int> depth;
	vector<vector<int>> adj, lca;
	void dfs(int node, int parent) {
		lca[node][0] = parent;
		depth[node] = (~parent ? depth[parent] + 1 : 0);
		for (int k = 1; k <= logN; k++) {
			int up_parent = lca[node][k - 1];
			if (~up_parent)
				lca[node][k] = lca[up_parent][k - 1];
		}
		for (int child : adj[node])
			if (child != parent)
				dfs(child, node);
	}
public:
	LCA(const vector<vector<int>> &_adj, int root = 1) :
			root(root), adj(_adj) {
		adj = _adj;
		n = adj.size() - 1;
		logN = log2(n);
		lca = vector<vector<int>>(n + 1, vector<int>(logN + 1, -1));
		depth = vector<int>(n + 1);
		dfs(root, -1);
	}
	int get_LCA(int x, int y) {
		if (depth[x] < depth[y])
			swap(x, y);
		for (int k = logN; k >= 0; k--)
			if (depth[x] - (1 << k) >= depth[y])
				x = lca[x][k];
		if (x == y)
			return x;
		for (int k = logN; k >= 0; k--) {
			if (lca[x][k] != lca[y][k]) {
				x = lca[x][k];
				y = lca[y][k];
			}
		}
		return lca[x][0];
	}
	int get_distance(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[get_LCA(u, v)];
	}
	int kth_ancestor(int node, int dist) {
		for (int i = logN; i >= 0 && ~node; i--)
			if (dist & (1 << i))
				node = lca[node][i];
		return node;
	}
	edge get_path(int u, int LCA) {
		edge rt;
		for (int k = logN; k >= 0; k--)
			if (depth[u] - (1 << k) >= depth[LCA]) {
				rt = merge(rt, lca[u][k]);
				u = lca[u][k].to;
			}
		return rt;
	}
};
