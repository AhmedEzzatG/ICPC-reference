
// x[i] = a[i] - a[i-1] //a is original array
// y[i] = x[i]*(i-1)
// sum(1,3) = a[1] + a[2] + a[3] 
// = (x[1]) + (x[2] + x[1]) + (x[3] + x[2] + x[1])
// = 3*(x[1] + x[2] + x[3]) - 0*x[1] - 1*x[2] - 2*x[3] -> same equation but more complex
// = sumX(1,3) * 3 - sumY(1,3)
// so sum(1,n) = sumX(1,n)*n - sumY(1,n)
// update:
// x[l] += val,x[r+1] -= val
// y[l] += val *(l-1),y[r+1] -= r*val

template<typename T>
class fenwick_tree {
	int n;
	vector<T> x, y;
	T getAccum(vector<T> &BIT, int idx) {
		T sum = 0;
		while (idx) {
			sum += BIT[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}
	void add(vector<T> &BIT, int idx, T val) {
		assert(idx != 0);
		while (idx <= n) {
			BIT[idx] += val;
			idx += (idx & -idx);
		}
	}
	T prefix_sum(int idx) {
		return getAccum(x, idx) * idx - getAccum(y, idx);
	}
public:
	fenwick_tree(int n) :
			n(n), x(n + 1), y(n + 1) {
	}
	void update_range(int l, int r, T val) {
		add(x, l, val);
		add(x, r + 1, -val);
		add(y, l, val * (l - 1));
		add(y, r + 1, -val * r);
	}
	T range_sum(int l, int r) {
		return prefix_sum(r) - prefix_sum(l - 1);
	}
};
