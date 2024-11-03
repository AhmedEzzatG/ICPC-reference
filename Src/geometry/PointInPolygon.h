ll cross(point a, point b, point c) {
	return cp(vec(a,b), vec(a,c));
}

void prepare(vector<point> &polygon) {
	int pos = 0;
	for (int i = 0; i < sz(polygon); i++) {
		if (make_pair(polygon[i].X, polygon[i].Y)
				< make_pair(polygon[pos].X, polygon[pos].Y))
			pos = i;
	}
	rotate(polygon.begin(), polygon.begin() + pos, polygon.end());
}

bool isPointOnSegment(point a, point b, point c) {
	double acb = length(a - b), ac = length(a - c), cb = length(b - c);
	return dcmp(acb - (ac + cb), 0) == 0;
}

bool pointInConvexPolygon(const vector<point> &polygon, point pt) {
	if (isPointOnSegment(polygon[0], polygon.back(), pt))
		return true;
	if (cross(polygon[0], polygon.back(), pt) > 0)
		return false;
	if (cross(polygon[0], polygon[1], pt) < 0)
		return false;
	if (polygon.size() == 2)
		return false;
	int st = 2, ed = sz(polygon) - 2, ans = 1;
	while (st <= ed) {
		int md = st + ed >> 1;
		if (cross(polygon[0], polygon[md], pt) >= 0)
			st = md + 1, ans = md;
		else
			ed = md - 1;
	}
	return cross(polygon[ans], polygon[ans + 1], pt) >= 0;
}
