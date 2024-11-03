template<typename T>
struct fenwick_tree {
    int n;
    vector<T> BIT;
    fenwick_tree(int n) : n(n), BIT(n + 1) {}
    T getAccum(int idx) {
        T sum = 0;
        while (idx) {
            sum += BIT[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
    void add(int idx, T val) {
        assert(idx != 0);
        while (idx <= n) {
            BIT[idx] += val;
            idx += (idx & -idx);
        }
    }
    T getValue(int idx) {
        return getAccum(idx) - getAccum(idx - 1);
    }
    // ordered statistics tree
    // get index that has value >= accum
    // values must be positive
    int getIdx(T accum) {
        int start = 1, end = n, rt = -1;
        while (start <= end) {
            int mid = start + end >> 1;
            T val = getAccum(mid);
            if (val >= accum)
                rt = mid, end = mid - 1;
            else
                start = mid + 1;
        }
        return rt;
    }
    //need review (from topcoder)
    //last index less than or equal accum  O(logn)
    int find(T accum) {
        int i = 1, idx = 0;
        while ((1 << i) <= n)
            i <<= 1;
        for (; i > 0; i >>= 1) {
            int tidx = idx + i;
            if (tidx > n)
                continue;
            if (accum >= BIT[tidx]) {
                idx = tidx;
                accum -= BIT[tidx];
            }
        }
        if (!accum || idx + 1 > n)return -1;
        return idx + 1;
    }
};
