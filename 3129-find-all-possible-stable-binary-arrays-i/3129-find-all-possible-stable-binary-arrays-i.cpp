class Solution {
public:
    static const int MOD = 1e9 + 7;

    int dp[201][201][2][201];

    int solve(int z, int o, int last, int cnt, int limit) {
        if (z == 0 && o == 0) return 1;

        int &ans = dp[z][o][last][cnt];
        if (ans != -1) return ans;

        ans = 0;

        if (last == 0) {
            if (z > 0 && cnt < limit)
                ans = (ans + solve(z - 1, o, 0, cnt + 1, limit)) % MOD;

            if (o > 0)
                ans = (ans + solve(z, o - 1, 1, 1, limit)) % MOD;
        } else {
            if (o > 0 && cnt < limit)
                ans = (ans + solve(z, o - 1, 1, cnt + 1, limit)) % MOD;

            if (z > 0)
                ans = (ans + solve(z - 1, o, 0, 1, limit)) % MOD;
        }

        return ans;
    }

    int numberOfStableArrays(int zero, int one, int limit) {
        memset(dp, -1, sizeof(dp));

        long long ans = 0;

        if (zero > 0)
            ans += solve(zero - 1, one, 0, 1, limit);

        if (one > 0)
            ans += solve(zero, one - 1, 1, 1, limit);

        return ans % MOD;
    }
};