#include<bits/stdc++.h>
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

//O(E*log(v))
void dijkstra(int src, int dest = -1) {
	priority_queue<edge> q;
	vector<int> dis(adj.size(), INT_MAX), prev(adj.size(), -1);
	q.push(edge(-1, src, 0));
	dis[src] = 0;
	while (!q.empty()) {
		edge e = q.top();
		q.pop();
		if (e.weight > dis[e.to])
			continue;
		prev[e.to] = e.from;
		if (e.to == dest)
			break;
		for (edge ne : adj[e.to])
			if (dis[ne.to] > dis[e.to] + ne.weight) {
				ne.weight = dis[ne.to] = dis[e.to] + ne.weight;
				q.push(ne);
			}
	}
	vector<int> path;
	while (dest != -1) {
		path.push_back(dest);
		dest = prev[dest];
	}
	reverse(path.begin(), path.end());
}
