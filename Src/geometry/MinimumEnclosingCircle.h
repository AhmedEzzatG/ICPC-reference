//init p array with the points and ps with the number of points
//cen and rad are result circle
//you must call random_shuffle(p,p+ps); before you call mec
typedef complex<double> point;
#define perp(a) 	(point(-(a).Y, (a).X))
#define vec(a,b) 	((b) - (a))
#define mid(a,b)	(((a) + (b)) / point(2, 0))

enum STATE {
    IN, OUT, BOUNDRY
};


STATE circlePoint(const point &cen, const double &r, const point &p) {
    double lensqr = lengthSqr(vec(cen,p));
    if (fabs(lensqr - r * r) < EPS)
        return BOUNDRY;
    if (lensqr < r * r)
        return IN;
    return OUT;
}


void circle2(const point &p1, const point &p2, point &cen, double &r) {
    cen = mid(p1, p2);
    r = length(vec(p1, p2)) / 2;
}


bool circle3(const point &p1, const point &p2, const point &p3,
             point& cen, double& r) {
    point m1 = mid(p1, p2);
    point m2 = mid(p2, p3);
    point perp1 = perp(vec(p1, p2));
    point perp2 = perp(vec(p2, p3));
    bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
    r = length(vec(cen,p1));
    return res;
}


#define MAXPOINTS 100000
point p[MAXPOINTS], r[3], cen;
int ps, rs;
double rad;
//init p array with the points and ps with the number of points
//cen and rad are result circle
//you must call random_shuffle(p,p+ps); before you call mec
void mec() {
    if (rs == 3) {
        circle3(r[0], r[1], r[2], cen, rad);
        return;
    }
    if (rs == 2 && ps == 0) {
        circle2(r[0], r[1], cen, rad);
        return;
    }
    if (!ps) {
        cen = r[0];
        rad = 0;
        return;
    }
    ps--;
    mec();
    if (circlePoint(cen, rad, p[ps]) == OUT) {
        r[rs++] = p[ps];
        mec();
        rs--;
    }
    ps++;
}