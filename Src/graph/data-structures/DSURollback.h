struct dsu_save {
    int v, rnkv, u, rnku;
 
    dsu_save() {}
 
    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};
 
struct dsu_with_rollbacks {
    vector<int> p, rnk;
    int comps;
    stack<dsu_save> op;
 
    dsu_with_rollbacks() {}
 
    dsu_with_rollbacks(int n) {
        p.resize(n + 1);
        rnk.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }
 
    int find_set(int v) {
        return (v == p[v]) ? v : find_set(p[v]);
    }
 
    bool same_group(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u)
            return false;
        comps--;
        if (rnk[v] > rnk[u])
            swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        if (rnk[u] == rnk[v])
            rnk[u]++;
        return true;
    }
    void snapshot() {
        // this function save the current trees (merged) and don't rollback them any more
        while (!op.empty())
            op.pop();
    }
    void rollback() {
        // you can erase the while loop if you want to rollback just the last merge
        while (!op.empty()) {
            dsu_save x = op.top();
            op.pop();
            comps++;
            p[x.v] = x.v;
            rnk[x.v] = x.rnkv;
            p[x.u] = x.u;
            rnk[x.u] = x.rnku;
        }
    }
};
