#include"Lines.h" //isPointOnSegment, CCW
struct cmp {
	point about;
	cmp(point c) {
		about = c;
	}
	bool operator()(const point &p, const point &q) const {
		double cr = cp(vec(about, p), vec(about, q));
		if (fabs(cr) < EPS)
			return make_pair(p.Y, p.X) < make_pair(q.Y, q.X);
		return cr < 0;
	}
};
void sortAntiClockWise(vector<point> &pnts) {
	point mn = pnts[0];
	for (int i = 0; i < sz(pnts); i++)
		if (make_pair(pnts[i].Y, pnts[i].X) < make_pair(mn.Y, mn.X))
			mn = pnts[i];
	sort(all(pnts), cmp(mn));
}

// CCW function must return 0 if the 3 points are collinear
bool isConvex(vector<point>& v) {
	int n = v.size(), m = n, sum = 0;
	v.push_back(v[0]);
	v.push_back(v[1]);
	char tmp;
	for (int i = 0; i < n; i++) {
		tmp = ccw(v[i], v[i + 1], v[i + 2]);
		if (tmp) sum += tmp;
		else m--;
	}
	v.pop_back();
	v.pop_back();
	return abs(sum) == m;
}


//Area(p) = interal_points + (boundry_point/2) - 1
//2*interal_points = 2*Area(p) - 2*(boundry_point/2) + 2
ll picksTheorm(vector<point> &p) { //point = complex<int>
	ll area = 0;
	ll bound = 0;
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1 < sz(p) ? i + 1 : 0);
		area += cp(p[i], p[j]);
		point v = vec(p[i], p[j]);
		bound += abs(__gcd(v.X, v.Y));
	}
	return (abs(area) - 2 * (bound / 2) + 2) / 2;
}

bool pointInPolygon(const vector<point> &p, point p0) {
	int wn = 0;  // the winding number counter

	for (int i = 0; i < sz(p); i++) {
		point cur = p[i], nxt = p[(i + 1) % sz(p)];
		if (isPointOnSegment(cur, nxt, p0))
			return true;
		if (cur.Y <= p0.Y) {    // Upward edge
			if (nxt.Y > p0.Y && cp(nxt - cur, p0 - cur) > EPS)
				++wn;
		} else {                // Downward edge
			if (nxt.Y <= p0.Y && cp(nxt - cur, p0 - cur) < -EPS)
				--wn;
		}
	}
	return wn != 0;
}

//to check if the points are sorted anti-clockwise or clockwise
//remove the fabs at the end and it will return -ve value if clockwise
double polygonArea(const vector<point> &p) {
	double res = 0;
	for (int i = 0; i < sz(p); i++) {
			int j = (i + 1) % sz(p);
			res += cp(p[i],p[j]);
	}
	return fabs(res) / 2;
}

// return the centroid point of the polygon
// The centroid is also known as the "centre of gravity" or the "center of mass". The position of the centroid
// assuming the polygon to be made of a material of uniform density.
point polygonCentroid(vector<point> &polygon) {
    point res(0, 0);
    double a = 0;
    for (int i = 0; i < (int) polygon.size(); i++) {
        int j = (i + 1) % polygon.size();
        res = res + (polygon[i] + polygon[j]) * cp(polygon[i], polygon[j]);
        a += cp(polygon[i], polygon[j]);
    }
    return res / 3.0 / a;
}

// P need to be counterclockwise convex polygon
pair<vector<point>,vector<point>> polygonCut(vector<point> &p, point A, point B) {

    vector<point> left, right;
    point intersect;

    for (int i = 0; i < sz(p); ++i) {
        point cur = p[i], nxt = p[(i + 1) % sz(p)];

		bool in1 = cp(B-A, cur-A) >= 0;
		bool in2 = cp(B-A, nxt-A) >= 0;

        if (in1) right.push_back(cur);

        //NOTE adust intersectSegments should handled AB as line
        if (intersectSegments(A, B, cur, nxt, intersect)) {
            right.push_back(intersect);
            left.push_back(intersect);
        }

        if (in2)left.push_back(cur);
    }
    return make_pair(left, right);
}