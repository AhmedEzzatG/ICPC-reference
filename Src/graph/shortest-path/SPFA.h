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

vector<vector<edge>> adj;

void spfa(int src) {
	enum visit {
		finished, in_queue, not_visited
	};
	int n = adj.size();
	vector<int> dis(n, INF), prev(n, -1), state(n, not_visited);
	dis[src] = 0;
	deque<int> q;
	q.push_back(src);
	while (!q.empty()) {
		int u = q.front();
		q.pop_front();
		state[u] = finished;
		for (auto &e : adj[u]) {
			if (dis[e.to] > dis[e.from] + e.cost) {
				dis[e.to] = dis[e.from] + e.cost;
				prev[e.to] = e.from;
				if (state[e.to] == not_visited) {
					q.push_back(e.to);
				} else if (state[e.to] == finished) {
					q.push_front(e.to);
				}
				state[e.to] = in_queue;
			}
		}
	}
}
