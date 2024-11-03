//Shortest cycle starting from node O(n^2)
int get_shortest_cycle(int start) {
    vector<int> dist(n + 1, INF), parent(n + 1), group(n + 1);
    vector<bool> vis(n + 1);
    dist[start] = 0;
    group[start] = start;
    while (true) {
        int cur = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && dist[i] < dist[cur])cur = i;
        if (dist[cur] == (int) INF)break;
        vis[cur] = true;
        for (int ch = 1; ch <= n; ch++) {
            if (dist[ch] > dist[cur] + adj[cur][ch]) {
                dist[ch] = dist[cur] + adj[cur][ch];
                parent[ch] = cur;
                group[ch] = (cur == start ? ch : group[cur]);
            }
        }
    }
    int mn = INF;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            if (parent[i] == j || parent[j] == i)continue;
            if (group[i] == group[j]) continue;
            if (dist[i] == (int) INF || dist[j] == (int) INF)continue;
            mn = min(mn, dist[i] + dist[j] + adj[i][j]);
        }
    return mn;
}
