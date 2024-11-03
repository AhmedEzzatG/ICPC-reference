#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define endl "\n"
#define ll long long
#define sz(s) (int)(s.size())
#define INF 0x3f3f3f3f3f3f3f3fLL
#define all(v) v.begin(),v.end()
#define watch(x) cout<<(#x)<<" = "<<x<<endl
const int dr[] { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] { 0, 1, 1, 1, 0, -1, -1, -1 };
#if __cplusplus >= 201402L
template<typename T>
vector<T> create(size_t n) {
	return vector<T>(n);
}
template<typename T, typename ... Args>
auto create(size_t n, Args ... args) {
	return vector<decltype(create<T>(args...))>(n, create<T>(args...));
}
#endif
void run() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
#ifdef EZZAT
	freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
#else
#endif
}

struct edge {
	int from, to;
	ll weight;
	edge() {
		from = to = weight = 0;
	}
	edge(int from, int to, ll weight) :
			from(from), to(to), weight(weight) {
	}
	bool operator <(const edge &other) const {
		return weight < other.weight;
	}
};

struct DSU {
	vector<int> rank, parent, size;
	int forsets;
	DSU(int n) {
		size = rank = parent = vector<int>(n + 1, 1);
		forsets = n;
		for (int i = 0; i <= n; i++)
			parent[i] = i;
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
		if (v == u)
			return false;
		if (rank[v] < rank[u])
			swap(v, u);
		link(v, u);
		return true;
	}
	bool same_set(int v, int u) {
		return find_set(v) == find_set(u);
	}
	int size_set(int v) {
		return size[find_set(v)];
	}
};

int MST_Kruskal(int n, vector<edge> edgeList, vector<edge> &take,
		vector<edge> &leave) {
	DSU uf(n);
	vector<edge> edges;
	sort(edgeList.begin(), edgeList.end());
	int mst_cost = 0;
	for (auto e : edgeList)
		if (uf.union_sets(e.from, e.to)) {
			take.push_back(e);
			mst_cost += e.weight;
		} else
			leave.push_back(e);
	return mst_cost;
}

struct LCA {
#define INIT { -1, -2 }
	struct data {
		int lca = -1;
		pair<int, int> max_edges = INIT; //first max,second max (distinct)
	};
	pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
		if (a.first < b.first)
			swap(a, b);
		if (b.first == a.first)
			a.second = max(a.second, b.second);
		else if (b.first > a.second)
			a.second = b.first;
		return a;
	}
	int logN;
	vector<vector<data>> lca;
	vector<vector<edge>> adj;
	vector<int> depth;
	void dfs(int node, int par) {
		for (edge e : adj[node])
			if (e.to != par) {
				depth[e.to] = depth[node] + 1;
				lca[e.to][0].max_edges.first = e.weight;
				lca[e.to][0].lca = node;
				dfs(e.to, node);
			}
	}
	LCA(int n, vector<edge> &edges) :
			adj(n + 1) {
		for (auto &e : edges) {
			adj[e.from].push_back(e);
			adj[e.to].push_back(edge(e.to, e.from, e.weight));
		}
		logN = log2(n);
		depth = vector<int>(n + 1);
		lca = vector<vector<data>>(n + 1, vector<data>(logN + 1));
		dfs(1, -1);
		for (int k = 1; k <= logN; k++)
			for (int node = 1; node <= n; node++) {
				int par = lca[node][k - 1].lca;
				if (~par) {
					lca[node][k].lca = lca[par][k - 1].lca;
					lca[node][k].max_edges = merge(lca[node][k - 1].max_edges,
							lca[par][k - 1].max_edges);
				}
			}
	}
	pair<int, int> max_two_edges(int u, int v) {
		pair<int, int> ans = INIT;
		if (depth[u] < depth[v])
			swap(u, v);
		for (int i = logN; i >= 0; i--)
			if (depth[u] - (1 << i) >= depth[v]) {
				ans = merge(ans, lca[u][i].max_edges);
				u = lca[u][i].lca;
			}
		if (u == v)
			return ans;
		for (int i = logN; i >= 0; i--)
			if (lca[u][i].lca != lca[v][i].lca) {
				ans = merge(ans, lca[u][i].max_edges);
				ans = merge(ans, lca[v][i].max_edges);
				u = lca[u][i].lca;
				v = lca[v][i].lca;
			}
		ans = merge(ans, lca[u][0].max_edges);
		ans = merge(ans, lca[v][0].max_edges);
		return ans;
	}
};

int main() {
	run();
	int t;
	cin >> t;
	for (int I = 1; I <= t; I++) {
		cout << "Case #" << I << " : ";
		int n, e;
		cin >> n >> e;
		vector<edge> edgeList(e);
		for (auto &it : edgeList)
			cin >> it.from >> it.to >> it.weight;
		vector<edge> take, leave;
		int mst_cost = MST_Kruskal(n, edgeList, take, leave);
		if (take.size() != n - 1) {
			cout << "No way\n";
			continue;
		}
		LCA tree(n, take);
		ll rt = INF;
		for (edge e : leave) {
			pair<int, int> p = tree.max_two_edges(e.from, e.to);
			rt = min(rt, mst_cost - p.first + e.weight);
		}
		if (rt == INF)
			cout << "No second way\n";
		else
			cout << rt << endl;
	}
}
