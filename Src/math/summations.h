#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define numOfDigit(x) 1+(int)(floor(log10(x)))
#define numOfBits(x) 1+(int)(floor(log2(x)))

//return sum of sequence a, a+x , a+2x .... b
ll sumSequence(ll a, ll b, ll x) {
	a = ((a + x - 1) / x) * x;
	b = (b / x) * x;
	return (b + a) * (b - a + x) / (2 * x);
}

ll sumPower(ll x, ll y) { //x^0 + x^1 + x^2 ... x^y
	return (power(x, y + 1) - 1) / (x - 1);
}


// return sum of divisors for all number from 1 to n
//O(n)
ll sumRangeDivisors(int n) {
	ll ans = 0;
	for (int x = 1; x <= n; x++)
		ans += (n / x) * x;
	return ans;
}

// return sum of divisors for all number from 1 to x
// calc 1e9 in 42ms,can calc more but need big integer
ll sumRangeDivisors(ll x) {
	ll ans = 0, left = 1, right;
	for (; left <= x; left = right + 1) {
		right = x / (x / left);
		ans += (x / left) * (left + right) * (right - left + 1) / 2;
	}
	return ans;
}

/*
 * sum of q^0 + q^1 + q^2 ... q^INF = 1/q if (0<q<1)
 */
