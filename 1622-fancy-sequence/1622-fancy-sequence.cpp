class Fancy {
public:
    static const long long MOD = 1e9 + 7;

    vector<pair<long long, long long>> seq;
    long long mul = 1, add = 0;

    long long modPow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    long long modInv(long long x) {
        return modPow(x, MOD - 2);
    }

    Fancy() {}

    void append(int val) {
        long long invMul = modInv(mul);
        long long original = ((val - add + MOD) % MOD) * invMul % MOD;
        seq.push_back({original, 0});
    }

    void addAll(int inc) {
        add = (add + inc) % MOD;
    }

    void multAll(int m) {
        mul = mul * m % MOD;
        add = add * m % MOD;
    }

    int getIndex(int idx) {
        if (idx >= seq.size()) return -1;

        long long val = seq[idx].first;
        return (val * mul + add) % MOD;
    }
};