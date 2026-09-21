class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);
            int m = num % k;

            ndp[m] = 1;

            for (int r = 0; r < k; r++) {
                if (dp[r]) {
                    ndp[(r * m) % k] += dp[r];
                }
            }

            for (int r = 0; r < k; r++) {
                ans[r] += ndp[r];
            }

            dp = move(ndp);
        }

        return ans;
    }
};