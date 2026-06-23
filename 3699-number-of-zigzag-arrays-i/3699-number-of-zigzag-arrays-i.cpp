class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int MOD = 1000000007;
        int m = r - l + 1;

        if (n == 1) return m;

        vector<long long> up(m + 1), down(m + 1);
        vector<long long> nup(m + 1), ndown(m + 1);
        vector<long long> pref(m + 1);

        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        if (n == 2) {
            long long ans = 0;
            for (int v = 1; v <= m; v++) {
                ans = (ans + up[v] + down[v]) % MOD;
            }
            return (int)ans;
        }

        for (int len = 3; len <= n; len++) {

            pref[0] = 0;
            for (int i = 1; i <= m; i++) {
                pref[i] = (pref[i - 1] + down[i]) % MOD;
            }
            for (int i = 1; i <= m; i++) {
                nup[i] = pref[i - 1];
            }

            pref[0] = 0;
            for (int i = 1; i <= m; i++) {
                pref[i] = (pref[i - 1] + up[i]) % MOD;
            }

            long long totalUp = pref[m];
            for (int i = 1; i <= m; i++) {
                ndown[i] = (totalUp - pref[i] + MOD) % MOD;
            }

            up.swap(nup);
            down.swap(ndown);
        }

        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            ans = (ans + up[i] + down[i]) % MOD;
        }

        return (int)ans;
    }
};