// return false if there is no solution
// return true if there exist a solution
// x, y are the solutions and g is the gcd between a and b
bool Diophantine_Solution(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
    if (!a && !b) {
        if (c) return false;
        x = y = g = 0;
        return true;
    }
    g = egcd(a, b, x, y);
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    return true;
}
void shift_solution(ll& x, ll& y, ll a, ll b, ll cnt) {
    x += b * cnt;
    y -= a * cnt;
}



// find all number of solutions of ax + by = c
// x in range {minx, maxx}
// y in range {miny, maxy}
ll Diophantine_Solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    if (minx > maxx || miny > maxy) return 0;
    if (!a && !b && !c)
        return (maxx - minx + 1) * (maxy - miny + 1);
    if (!a && !b) return 0;
    if (!a) {
        if (c % b) return 0;
        ll num = c / b;
        return (num >= miny && num <= maxy) * (maxx - minx + 1);
    }
    if (!b) {
        if (c % a) return 0;
        ll num = c / a;
        return (num >= minx && num <= maxx) * (maxy - miny + 1);
    }
    ll x, y, g;
    if (!Diophantine_Solution(a, b, c, x, y, g))
        return 0;
    ll lx1, lx2, rx1, rx2;
    // a * x + b * y = c
    // (a / g) * x + (b / g) * y = c / g
    a /= g, b /= g, c /= g;
    g = 1;
    int sign_a = (a > 0 ? 1 : -1);
    int sign_b = (b > 0 ? 1 : -1);
    // x + k * b >= minx
    // k * b >= minx - x
    // k >= (minx - x) / b
    // k >= ceil((minx - x) / b)
    shift_solution(x, y, a, b, (minx - x) / b);
    // if x is less than minx so we need to increase it by one step only
    // from the upove equation x + k * b >= minx
    // if b is positive so choose k equal to 1 to increase x one
    // if b is negattive so choose k equal to -1 because -1 * -1 = 1 ans also increase x
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx) return 0;
    lx1 = x;

    // x + k * b <= maxx
    // k * b <= maxx - x
    // k <= (maxx - x) / b
    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    rx1 = x;
    // y - k * a >= miny
    // y - miny >= k * a
    // k * a <= y - miny
    // k <= (y - miny) / a
    shift_solution(x, y, a, b, (y - miny) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy) return 0;
    lx2 = x;
    // y - k * a <= maxy
    // y - maxy <= k * a
    // k * a >= y - maxy
    // k >= (y - maxy) / a
    shift_solution(x, y, a, b, (y - maxy) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    rx2 = x;
    if (lx2 > rx2) swap(lx2, rx2);
    // becuase we calculate the equations lx2, rx2 from shifting y
    // not from shifting x directly
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);
    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}