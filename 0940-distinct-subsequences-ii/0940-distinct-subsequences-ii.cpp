class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        vector<long long> last(26, 0);
        long long dp = 1; // empty subsequence

        for (char c : s) {
            long long oldDp = dp;
            dp = (2 * dp % MOD - last[c - 'a'] + MOD) % MOD;
            last[c - 'a'] = oldDp;
        }

        return (dp - 1 + MOD) % MOD; // exclude empty subsequence
    }
};