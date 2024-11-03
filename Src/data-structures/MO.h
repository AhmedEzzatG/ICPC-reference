
int sqrtN; //use a constent value
struct query {
	int l, r, qIdx, block;
	query(int l, int r, int qIdx) :
			l(l), r(r), qIdx(qIdx), block(l / sqrtN) {
	}
	bool operator <(const query &o) const {
		if (block != o.block)
			return block < o.block;
		return (block % 2 == 0 ? r < o.r : r > o.r);
	}
};

int curL, curR, ans;
vector<query> q;
void add(int index);
void remove(int index);

void solve(int l, int r) {
	while (curL > l)
		add(--curL);
	while (curR < r)
		add(++curR);
	while (curL < l)
		remove(curL++);
	while (curR > r)
		remove(curR--);
}

vector<int> MO() {
	vector<int> rt(q.size());
	ans = curL = curR = 0;
	add(0);//v[0]
	sort(q.begin(), q.end());
	for (auto it : q) {
		solve(it.l, it.r);
		rt[it.qIdx] = ans;
	}
	return rt;
}
