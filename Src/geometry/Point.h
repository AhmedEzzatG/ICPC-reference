#include <bits/stdc++.h>
using namespace std;
#define ll long long
typedef complex<double> point;  // it can be long long not double
template<class T>
istream& operator>>(istream& is, complex<T>& p) {
	T value;
	is >> value;
	p.real(value);
	is >> value;
	p.imag(value);
	return is;
}
#define PI acos(-1.0)
#define EPS 1e-8
#define X real()
#define Y imag()
#define angle(a)  (atan2((a).imag(), (a).real())) // angle with orignial
#define length(a)   (hypot((a).imag(), (a).real()))
#define vec(a,b)  ((b)-(a)) // return diff x1-x2 , y1-y2
#define dp(a,b)   ( (conj(a)*(b)).real() )	
// a*b cos(T), if zero -> prep dot product A.B
#define cp(a,b)   ( (conj(a)*(b)).imag() )	
// a*b sin(T), if zero -> parllel cross product = area of parllelogram
#define normalize(a)    (a)/length(a)
// norm(a)  // return x^2 + y^2 //a is point //can use dp(a,a)


bool same(point p1, point p2) {// check to points same or not
	return dp(vec(p1, p2), vec(p1, p2)) < EPS;
}

point rotate(point p, double angle, point around = point(0, 0)) {
	p -= around;
	return (p * exp(point(0, angle))) + around;
}

// Refelect v around m
point reflectO(point v, point m) {
	return conj(v / m) * m;
}

// Refelect point p around l1-l2
point reflect(point p, point l1, point l2) {
	point z = p - l1, w = l2 - l1;
	return conj(z / w) * w + l1;
}
