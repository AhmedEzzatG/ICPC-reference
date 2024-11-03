//linear sieve
const int N = 1e7;
int lpf[N + 1];
vector<int> prime;
void sieve() {
	for (int i = 2; i <= N; i++) {
		if (lpf[i] == 0) {
			lpf[i] = i;
			prime.push_back(i);
		}
		for (int j : prime) {
			if (j > lpf[i] || 1LL * i * j > N)break;
			lpf[i * j] = j;
		}
	}
}


// return number of Divisors(n) using prime factorization
ll numOfDivisors(primeFactors mp) {
	ll cnt = 1;
	for (auto it : mp) cnt *= (it.second + 1);
	return cnt;
}
// return sum of Divisors(n) using prime factorization
ll sumOfDivisors(primeFactors mp) {
	ll sum = 1;
	for (auto it : mp) sum *= sumPower(it.first, it.second);
	return sum;
}

ll phi_function(ll n) {
	ll result = n;
	primeFactors pf = prime_factors(n);
	for (auto &it : pf) {
		ll p = it.first;
		result -= (result / p);
	}
	return result;
}
void phi_1_to_n(int n) {
	for (int i = 0; i <= n; i++)
		phi[i] = i;
	for (int i = 2; i <= n; i++)
		if (phi[i] == i)
			for (int j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
}

char mob[N];
bool prime[N];
void moebius() {
	memset(mob, 1, sizeof mob);
	memset(prime + 2, 1, sizeof(prime) - 2);
	mob[0] = 0;
	mob[2] = -1;
	for (int i = 4; i < N; i += 2) {
		mob[i] *= (i & 3) ? -1 : 0;
		prime[i] = 0;
	}
	for (int i = 3; i < N; i += 2)
		if (prime[i]) {
			mob[i] = -1;
			for (int j = 2 * i; j < N; j += i) {
				mob[j] *= j % (1LL * i * i) ? -1 : 0;
				prime[j] = 0;
			}
		}
}
