#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define endl "\n"
#define ll long long
#define sz(s) (int)(s.size())
#define INF 0x3f3f3f3f3f3f3f3fLL
#define all(v) v.begin(),v.end()
#define watch(x) cout<<(#x)<<" = "<<x<<endl
const int dr[] { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] { 0, 1, 1, 1, 0, -1, -1, -1 };
#if __cplusplus >= 201402L
template<typename T>
vector<T> create(size_t n) {
	return vector<T>(n);
}
template<typename T, typename ... Args>
auto create(size_t n, Args ... args) {
	return vector<decltype(create<T>(args...))>(n, create<T>(args...));
}
#endif
void run() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
#ifndef ONLINE_JUDGE
	//freopen("input.in", "r", stdin);
#else
	//freopen("groups.in", "r", stdin);
#endif
}

// The following rules should be considered before using this function:
// 	1. No two line segment endpoints or crossings have the same x-coordinate
// 	2. No line segment endpoint lies upon another line segment
// 	3. No three line segments intersect at a single point
typedef complex<int> point;
template<class T>
istream& operator>>(istream &is, complex<T> &p) {
	T value;
	is >> value;
	p.real(value);
	is >> value;
	p.imag(value);
	return is;
}
#define PI acos(-1)
#define EPS 1e-8
#define X real()
#define Y imag()
#define vec(a,b) (b - a)
#define length(a) (hypot((a).Y,(a).X))
#define angle(a) (atan2(a.Y,a.X))
#define cp(a,b)   ( (conj(a)*(b)).imag() )
int dcmp(double x, double y) {
	if (fabs(x - y) < EPS)
		return 0;
	return (x < y ? -1 : 1);
}

struct segment {
	point p, q;
	int idx;
	segment() {
	}
	segment(point a, point b, int idx) :
			p(a), q(b), idx(idx) {
	}
	double CY(int x) const {
		if (p.X == q.X)
			return p.Y;
		double t = 1.0 * (x - p.X) / (q.X - p.X);
		return p.Y + (q.Y - p.Y) * t;
	}
	bool operator<(const segment &o) const {
		if (p == o.p && q == o.q)
			return idx < o.idx;
		int maxX = max(p.X, o.p.X);
		int res = dcmp(CY(maxX), o.CY(maxX));
		if (res == 0)
			return idx < o.idx;
		return res < 0;
	}
};

struct event {
	bool entry;
	point p;
	int idx;
	event(point p, bool entry, int idx) :
			p(p), entry(entry), idx(idx) {
	}
	bool operator<(const event &o) const {
		if (p.X != o.p.X)
			return p.X < o.p.X;
		if (entry != o.entry)
			return entry > o.entry;
		return idx < o.idx;
	}
};

int ccw(point a, point b, point c) {
	point v1(b - a), v2(c - a);
	double t = cp(v1, v2);

	if (t > EPS)
		return 1;
	if (t < -EPS)
		return -1;
	if (v1.X * v2.X < -EPS || v1.Y * v2.Y < -EPS)
		return -1;
	if (norm(v1) < norm(v2) - EPS)
		return 1;
	return 0;
}

bool intersect(point p1, point p2, point p3, point p4) {
	// special case handling if a segment is just a point
	bool x = (p1 == p2), y = (p3 == p4);
	if (x && y)
		return p1 == p3;
	if (x)
		return ccw(p3, p4, p1) == 0;
	if (y)
		return ccw(p1, p2, p3) == 0;
	return ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0
			&& ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
}

vector<segment> v;
vector<event> events;
pair<int, int> solve() {
	sort(all(events));
	set<segment> st;
	auto before = [&](set<segment>::iterator it) {
		if (it == st.begin())
			return st.end();
		return --it;
	};
	auto check = [&](set<segment>::iterator x,
			set<segment>::iterator y) -> bool {
		if (x == st.end() || y == st.end())
			return false;
		return intersect(x->p, x->q, y->p, y->q);
	};
	for (auto &cur : events) {
		if (cur.entry) {
			auto it = st.insert(v[cur.idx]).first;
			auto below = before(it);
			auto above = next(it);
			if (check(below, it))
				return {below->idx,it->idx};
			if (check(above, it))
				return {above->idx,it->idx};
		} else {
			auto it = st.find(v[cur.idx]);
			auto below = before(it);
			auto above = next(it);
			if (check(below, above))
				return {below->idx,above->idx};
			st.erase(it);
		}
	}
	return {-1,-1};
}
int main() {
	run();
	int n;
	cin >> n;
	v = vector<segment>(n);
	for (int i = 0; i < n; i++) {
		point p, q;
		cin >> p >> q;
		if (q.X < p.X || (q.X == p.X && q.Y < p.Y))
			swap(p, q);
		v[i] = segment(p, q, i);
		events.push_back(event(p, true, i));
		events.push_back(event(q, false, i));
	}
	pair<int, int> p = solve();
	if (p.first == -1)
		cout << "NO\n";
	else {
		cout << "YES\n";
		cout << p.first + 1 << ' ' << p.second + 1 << endl;
	}
}
