#include <bits/stdc++.h>
using namespace std;


struct edge {
	int from, to, weight;
	edge() {
		from = to = weight = 0;
	}
	edge(int from, int to, int weight) :
			from(from), to(to), weight(weight) {
	}
	bool operator <(const edge &other) const {
		return weight > other.weight;
	}
};

vector<vector<edge>> adj;
vector<edge> prim(int node) {
	vector<bool> vis(adj.size());
	priority_queue<edge> q;
	vector<edge> edges;
	q.push(edge(-1, node, 0));
	while (!q.empty()) {
		edge e = q.top();
		q.pop();
		if (vis[e.to])
			continue;
		vis[e.to] = true;
		if (e.from != -1)
			edges.push_back(e);
		for (edge ch : adj[e.to])
			if (!vis[ch.to])
				q.push(ch);
	}
	return edges;//check it connected or not
}

