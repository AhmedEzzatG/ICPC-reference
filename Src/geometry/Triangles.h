#include"point.h"

// sin(A)/a = sin(B)/b = sin(C)/c
// a^2 = b^2 + c^2 - 2b*c*cos(A
// sin(A+B) = sin(A) * cos(B) + sin(B) * cos(A)
// sin(A-B) = sin(A) * cos(B) - sin(B) * cos(A)
// cos(A+B) = cos(A) * cos(B) - sin(A) * sin(B)
// cos(A-B) = cos(A) * cos(B) + sin(A) * sin(B)
// tan(A+B) = (tan(A) + tan(B))/(1 - tan(A) * tan(B))
// tan(A-B) = (tan(A) - tan(B))/(1 - tan(A) * tan(B))

double fixAngle(double A) {
	return A > 1 ? 1 : (A < -1 ? -1 : A);
}
// return min angle: aOb / bOa
// dp(v1, v2) = |v1|*|v2|*cos(theta)
double angleO(point a, point O, point b) {
	point v1(a - O), v2(b - O);
	return acos(fixAngle(dp(v1, v2) / dist(v1) / dist(v2)));
}

double getSide_a_bAB(double b, double A, double B) {
	return (sin(A) * b) / sin(B);
}

double getAngle_A_abB(double a, double b, double B) {
	return asin(fixAngle((a * sin(B)) / b));
}

// wr answer in team formation :D
double getAngle_A_abc(double a, double b, double c) {
	return acos(fixAngle((b * b + c * c - a * a) / (2 * b * c)));
}

double triangleArea(double a, double b, double c) {
	double s = (a + b + c) / 2.0;
	return sqrt((s - a) * (s - b) * (s - c) * s);
}

double triangleArea(point p0, point p1, point p2) {
	double a = length(vec(p1, p0)), b = length(vec(p2, p0)), 
		c = length(vec(p2, p1));
	return triangleArea(a, b, c);
}

double triangleArea3points(const point &a, const point &b, const point &c) {
	return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2;
}

bool pointInTriangle(point a, point b, point c, point pt) {
	ll s1 = fabs(cp(vec(a,b), vec(a,c)));
	ll s2 = fabs(cp(vec(pt,a), vec(pt,b))) 
		+ fabs(cp(vec(pt, b), vec(pt, c)))
		+ fabs(cp(vec(pt, a), vec(pt, c)));
	return s1 == s2;
}

// largest circle inside a triangle
//A triangle with area A and semi-perimeter s has an inscribed circle (incircle) with
//radius r = A/s
bool circleInTriangle(point a, point b, point c, point& ctr, double& r) {
	double ab = length(a - b), bc = length(b - c),
		ca = length(c - a);
	double s = 0.5 * (ab + bc + ca);
	r = triangleArea(ab, bc, ca) / s;

	if (fabs(r) < EPS) return 0; // no inCircle center
	double ratio = length(a - b) / length(a - c);
	point p1 = b + (vec(b, c) * (ratio / (1 + ratio)));
	ratio = length(b - a) / length(b - c);
	point p2 = a + (vec(a, c) * (ratio / (1 + ratio)));
	return intersectSegments(a, p1, b, p2, ctr); // get their intersection point
}

