
ll egcd(ll a, ll b, ll& x, ll& y) {
    if (a < 0) {
        auto g = egcd(-a, b, x, y);
        x *= -1;
        return g;
    }
    if (b < 0) {
        auto g = egcd(a, -b, x, y);
        y *= -1;
        return g;
    }

    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a % b, x1, y1);
    x = y1, y = x1 - y1 * (a / b);
    return g;
}

//O(n * log(m)) Memory & Time; coefficients.size() <= n, coefficients[i] <= m
// 0-based implementation
template<typename T>
T extended_euclidean(const deque<T>& cof, deque<T>& var) {
    int n = cof.size();
    if (!cof.back()) {
        int cnt = 0, id = 0;
        for (int i = 0; i < n; i++)
            if (!cof[i]) {
                cnt++;
                var[i] = 0;
            } else id = i;
        if (cnt >= n - 1) {
            var[id] = 1;
            return cof[id];
        }
        deque<T> new_cof, new_var;
        for (int i = 0; i < n; i++)
            if (cof[i]) {
                new_cof.push_back(cof[i]);
                new_var.push_back(var[i]);
            }
        T g = extended_euclidean(new_cof, new_var);
        for (int i = 0; !new_var.empty(); i++)
            if (cof[i]) {
                var[i] = new_var.front();
                new_var.pop_front();
            }
        return g;
    }
    deque<T> new_cof = cof;
    for (int i = 0; i < n - 1; i++)
        new_cof[i] %= new_cof.back();
    new_cof.push_front(new_cof.back());
    new_cof.pop_back();
    var.push_front(var.back());
    var.pop_back();
    T g = extended_euclidean(new_cof, var);
    var.push_back(var.front());
    var.pop_front();
    for (int i = 0; i < n - 1; i++)
        var.back() -= cof[i] / cof.back() * var[i];
    return g;
}
template<typename T>
vector<T> find_any_solution(const vector<T>& cof, T rhs) {
    int n = cof.size();
    if (!n)
        return vector<T>();
    deque<T> deque_cof(cof.begin(), cof.end()), deque_var(n);
    T g = extended_euclidean(deque_cof, deque_var);
    if (g && rhs % g)
        return vector<T>();
    vector<T> var(deque_var.begin(), deque_var.end());
    if (g) {
        rhs /= g;
        for (auto& it : var)
            it *= rhs;
    }
    return var;
}