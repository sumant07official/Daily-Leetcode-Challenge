class Solution {
public:
    static const int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        const int MAXG = 200;

        vector<vector<long long>> dp(MAXG + 1, vector<long long>(MAXG + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<long long>> ndp = dp;

            for (int g1 = 0; g1 <= MAXG; g1++) {
                for (int g2 = 0; g2 <= MAXG; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    int ng1 = std::gcd(g1, x);
                    int ng2 = std::gcd(g2, x);

                    ndp[ng1][g2] = (ndp[ng1][g2] + dp[g1][g2]) % MOD;
                    ndp[g1][ng2] = (ndp[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= MAXG; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};