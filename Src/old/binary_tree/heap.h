#include<bits/stdc++.h>
using namespace std;
template<class T, class cmp = less<T>>
class heap {
	vector<T> v;
	void check() const {
		assert(size() > 0);
	}
	int parent(const int &node) const {
		return (node == 0 ? -1 : (node - 1) / 2);
	}
	int right(const int &node) const {
		int r = 2 * node + 2;
		return (r < size() ? r : -1);
	}
	int left(const int &node) const {
		int l = 2 * node + 1;
		return (l < size() ? l : -1);
	}
	void reheapUp(const int &node) {
		if (node == 0 || cmp()(v[parent(node)], v[node]))
			return;
		swap(v[node], v[parent(node)]);
		reheapUp(parent(node));

	}
	void reheapDown(const int &node) {
		int child = left(node);
		if (child == -1)
			return;
		int rightChild = right(node);
		if (rightChild != -1 && cmp()(v[rightChild], v[child]))
			child = rightChild;
		if (cmp()(v[node], v[child]))
			return;
		swap(v[node], v[child]);
		reheapDown(child);
	}
public:
	int size() const {
		return v.size();
	}
	void push(const int &val) {
		v.push_back(val);
		reheapUp((int) v.size() - 1);
	}
	const T& top() const {
		check();
		return v[0];
	}
	void pop() {
		check();
		v[0] = v.back();
		v.pop_back();
		reheapDown(0);
	}
};
