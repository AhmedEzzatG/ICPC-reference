bool cmp(point a, point b) {
	return a.X < b.X || (a.X == b.X && a.Y < b.Y);
}

ll cross(point a, point b, point c) {
	return cp(vec(a,b), vec(a,c));
}

bool cw(point a, point b, point c) {
	return cp(vec(a,b), vec(b,c)) < 0;
}

bool ccw(point a, point b, point c) {
	return cp(vec(a,b), vec(b,c)) > 0;
}

//with collinear points, to remove collinears check if cross == 0 when pop 
vector<point> convex_hull(vector<point> &p) {
	if (p.size() == 1)
		return p;

	sort(p.begin(), p.end(), &cmp);
	point p1 = p[0], p2 = p.back();
	vector<point> up, down;
	up.push_back(p1);
	down.push_back(p1);
	for (int i = 1; i < (int) p.size(); i++) {
		if (i == p.size() - 1 || cw(p1, p[i], p2)) {
			while (up.size() >= 2
					&& !cw(up[up.size() - 2], up[up.size() - 1], p[i]))
				up.pop_back();
			up.push_back(p[i]);
		}
		if (i == p.size() - 1 || ccw(p1, p[i], p2)) {
			while (down.size() >= 2
					&& !ccw(down[down.size() - 2], down[down.size() - 1], p[i]))
				down.pop_back();
			down.push_back(p[i]);
		}
	}

	vector<point> convex;
	for (int i = 0; i < (int) down.size(); i++)
		convex.push_back(down[i]);
	for (int i = up.size() - 2; i > 0; i--)
		convex.push_back(up[i]);
	return convex;
}