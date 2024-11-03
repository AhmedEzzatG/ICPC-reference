// 1-based,if value in node,just update it after build chains 
// don't forget to call build_chains after add edges.

class heavy_light_decomposition { 
	int n, is_value_in_edge;
	vector<int> parent, depth, heavy, root, pos_in_array, pos_to_node, size;
	const static int merge(int a, int b); //implement it
	struct array_ds { //implement it
		int n;
		array_ds(int n) :
				n(n) {
		}
		void update(int pos, int value);
		int query(int l, int r);
	} seg;
	struct TREE {
		int cnt_edges = 1;
		vector<vector<int>> adj;
		//need for value in edges
		vector<vector<int>> edge_idx;
		//edge_to need for undirected tree //end of edge in directed tree
		vector<int> edge_to, edge_cost;
		TREE(int n) :
				adj(n + 1), edge_idx(n + 1), edge_to(n + 1), edge_cost(n + 1) {
		}
		void add_edge(int u, int v, int c) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			edge_idx[u].push_back(cnt_edges);
			edge_idx[v].push_back(cnt_edges);
			edge_cost[cnt_edges] = c;
			cnt_edges++;
		}
	} tree;
	int dfs_hld(int node) {
		int size = 1, max_sub_tree = 0;
		for (int i = 0; i < (int) tree.adj[node].size(); i++) {
			int ch = tree.adj[node][i], edge_idx = tree.edge_idx[node][i];
			if (ch != parent[node]) {
				tree.edge_to[edge_idx] = ch;
				parent[ch] = node;
				depth[ch] = depth[node] + 1;
				int child_size = dfs_hld(ch);
				if (child_size > max_sub_tree)
					heavy[node] = ch, max_sub_tree = child_size;
				size += child_size;
			}
		}
		return size;
	}
	vector<tuple<int, int, bool>> get_path(int u, int v) { //l,r,must_reverse?
		vector<pair<int, int>> tmp[2];
		bool idx = 1;
		while (root[u] != root[v]) {
			if (depth[root[u]] > depth[root[v]]) {
				swap(u, v);
				idx = !idx;
			}
			//if value in edges ,you need value of root[v] also (connecter edge)
			tmp[idx].push_back( { pos_in_array[root[v]], pos_in_array[v] });
			v = parent[root[v]];
		}
		if (depth[u] > depth[v]) {
			swap(u, v);
			idx = !idx;
		}
		if (!is_value_in_edge || u != v)
			tmp[idx].push_back( { pos_in_array[u] + is_value_in_edge,
					pos_in_array[v] });
		reverse(all(tmp[1]));
		vector<tuple<int, int, bool>> rt;
		for (int i = 0; i < 2; i++)
			for (auto &it : tmp[i])
				rt.emplace_back(it.first, it.second, i == 0);
		return rt; //u is LCA
	}
public:
	heavy_light_decomposition(int n, bool is_value_in_edge) :
			n(n), is_value_in_edge(is_value_in_edge), seg(n + 1), tree(n + 1) {
		heavy = vector<int>(n + 1, -1);
		parent = depth = root = pos_in_array = pos_to_node = size = vector<int>(
				n + 1);
	}
	void add_edge(int u, int v, int c = 0) {
		tree.add_edge(u, v, c);
	}
	void build_chains(int src = 1) {
		parent[src] = -1;
		dfs_hld(src);
		for (int chain_root = 1, pos = 1; chain_root <= n; chain_root++) {
			if (parent[chain_root] == -1
					|| heavy[parent[chain_root]] != chain_root)
				for (int j = chain_root; j != -1; j = heavy[j]) {
					root[j] = chain_root;
					pos_in_array[j] = pos++;
					pos_to_node[pos_in_array[j]] = j;
				}
		}
		if (is_value_in_edge)
			for (int i = 1; i < n; i++)
				update_edge(i, tree.edge_cost[i]);
	}
	void update_node(int node, int value) {
		seg.update(pos_in_array[node], value);
	}
	void update_edge(int edge_idx, int value) {
		update_node(tree.edge_to[edge_idx], value);
	}
	void update_path(int u, int v, ll c) {
		vector<tuple<int, int, bool>> intervals = get_path(u, v);
		for (auto &it : intervals)
			seg.update(get<0>(it), get<1>(it), c);
	}
	node query_in_path(int u, int v) {
		vector<tuple<int, int, bool>> intervals = get_path(u, v);
		//initial value,check if handling u == v
		node query_res = 0;
		for (auto &it : intervals) {
			int l, r;
			bool rev;
			tie(l, r, rev) = it;
			node cur = seg.query(l, r);
			if (rev)
				cur.reverse();
			query_res = node(query_res, cur);
		}
		return query_res;
	}
};
