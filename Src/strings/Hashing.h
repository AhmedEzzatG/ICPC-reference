struct hashing {
    int MOD, BASE;
    vector<int> Hash, modInv;
    hashing(string s, int MOD, int BASE, char first_char = 'a') :
            MOD(MOD), BASE(BASE), Hash(sz(s) + 1), modInv(sz(s) + 1) {
        ll BASE_INV = power(BASE, MOD - 2, MOD);
        modInv[0] = 1;
        ll base = 1;
        for (int i = 1; i <= sz(s); i++) {
            Hash[i] = (Hash[i - 1] + (s[i - 1] - first_char + 1) * base) % MOD;
            modInv[i] = (modInv[i - 1] * BASE_INV) % MOD;
            base = (base * BASE) % MOD;
        }
    }
    int getHash(int l, int r) { //1-based
        return (1LL * (Hash[r] - Hash[l - 1] + MOD) % MOD * modInv[l - 1]) % MOD;
    }
};

//MOD = 1e9 + 9 ,BASE = 31
//MOD = 2000000011 ,BASE = 53 ->careful of overflow
//MOD = 998634293,BASE = 953
//MOD = 986464091,BASE = 1013
