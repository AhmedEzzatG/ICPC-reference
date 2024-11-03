void add(int node, int par, int big);
void remove(int node, int par, int big);

void dfs(int node, int par, bool keep) {
    int mx = -1, big = -1;
    for (int ch: adj[node]) {
        if (ch != par && subsize[ch] > mx)
            mx = subsize[ch], big = ch;
    }
    for (int ch: adj[node]) {
        if (ch != par && ch != big)
            dfs(ch, node, false);
    }
    if (big != -1) dfs(big, node, true);
    add(node, par, big);
    // SOLVE
    if (!keep) {
        remove(node, par, -1);
    }
}