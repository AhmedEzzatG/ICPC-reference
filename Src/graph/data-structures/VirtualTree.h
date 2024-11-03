int subsize[N], depth[N], dfs_num[N], id[N], have[N], timer, n;
vector<vector<int>> adj;

void calc(int node) {
    dfs_num[node] = ++timer;
    subsize[node] = 1;
    for (auto ch: adj[node]) {
        adj[ch].erase(find(all(adj[ch]), node));
        depth[ch] = depth[node] + 1;
        calc(ch);
        subsize[node] += subsize[ch];
    }
}

bool parent(int node, int par) {
    return dfs_num[par] <= dfs_num[node] && dfs_num[node] < dfs_num[par] + subsize[par];
}

struct virtual_tree {
    vector<int> nodes;
    vector<vector<int>> adj;

    virtual_tree(const vector<int> &v) : nodes(v) {
        for (auto &it: nodes) have[it] = true;

        sort(all(nodes), [&](int a, int b) {
            return dfs_num[a] < dfs_num[b];
        });

        int tmp = nodes.size();
        for (int j = 0; j + 1 < tmp; j++) {
            int lca = tree.get_LCA(nodes[j], nodes[j + 1]);
            nodes.push_back(lca);
        }
        nodes.push_back(1);
        sort(all(nodes));
        nodes.erase(unique(all(nodes)), nodes.end());

        sort(all(nodes), [&](int a, int b) {
            return dfs_num[a] < dfs_num[b];
        });

        int cnt = 0;
        for (auto &it: nodes)id[it] = cnt++;


        stack<int> stk;
        adj = vector<vector<int>>(cnt);
        for (auto &it: nodes) {
            while (!stk.empty() && !(parent(it, stk.top())))
                stk.pop();
            if (stk.size()) {
                adj[id[stk.top()]].push_back(it); // it or id[it] ??
            }
            stk.push(it);
        }
        dfs(1);

        for (auto &it: nodes)have[it] = false;
    }
    
};
