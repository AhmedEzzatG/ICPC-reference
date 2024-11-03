
struct Dinic {
	struct flowEdge {
		int from, to;
		ll cap, flow = 0;
		flowEdge(int from, int to, ll cap) :
				from(from), to(to), cap(cap) {
		}
	};
	vector<flowEdge> edges;
	int n, m = 0, source, sink;
	vector<vector<int>> adj;
	vector<int> level, ptr;
	Dinic(int n, int source, int sink) :
			n(n), source(source), sink(sink), adj(n), level(n), ptr(n) {
	}
	void addEdge(int u, int v, ll cap) {
		edges.emplace_back(u, v, cap);
		edges.emplace_back(v, u, 0);
		adj[u].push_back(m);
		adj[v].push_back(m + 1);
		m += 2;
	}
	bool bfs() {
		queue<int> q;
		level = vector<int>(n, -1);
		level[source] = 0;
		q.push(source);
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			for (auto &id : adj[cur]) {
				if (edges[id].cap - edges[id].flow <= 0)
					continue;
				int nxt = edges[id].to;
				if (level[nxt] != -1)
					continue;
				level[nxt] = level[cur] + 1;
				q.push(nxt);
			}
		}
		return level[sink] != -1;
	}
	ll dfs(int node, ll cur_flow) {
		if (cur_flow == 0 || node == sink)
			return cur_flow;
		for (int &cid = ptr[node]; cid < adj[node].size(); cid++) {
			int id = adj[node][cid];
			int nxt = edges[id].to;
			if (level[node] + 1 != level[nxt]
					|| edges[id].cap - edges[id].flow <= 0)
				continue;
			ll tmp = dfs(nxt, min(cur_flow, edges[id].cap - edges[id].flow));
			if (tmp == 0)
				continue;
			edges[id].flow += tmp;
			edges[id ^ 1].flow -= tmp;
			return tmp;
		}
		return 0;
	}
	ll flow() {
		ll max_flow = 0;
		while (bfs()) {
			fill(ptr.begin(), ptr.end(), 0);
			while (ll pushed = dfs(source, INF))
				max_flow += pushed;
		}
		return max_flow;
	}
};
