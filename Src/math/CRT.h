
ll CRT(vector<ll>& a, vector<ll>& m){
	ll lcm = m[0], rem = a[0];
	int n = a.size();
	for(int i = 1; i < n; i++){
		ll x, y;
		ll gcd = extended_euclidean(lcm, m[i], x, y);
		if((a[i] - rem) % gcd) return -1;
		ll tmp = m[i] / gcd, f = (a[i] - rem) / gcd;
        	x = ((x % tmp) * (f % tmp)) % tmp;
		rem += lcm * x;
		lcm = lcm * m[i] / gcd;
		rem = (rem % lcm + lcm) % lcm;
	}
	return rem;
}
