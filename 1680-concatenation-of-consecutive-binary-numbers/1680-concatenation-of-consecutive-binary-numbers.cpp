class Solution {
public:
    int concatenatedBinary(int n) {
        const long long MOD = 1e9 + 7;
        
        long long ans = 0;
        int len = 0;

        for (int i = 1; i <= n; i++) {
            if ((i & (i - 1)) == 0) { // power of 2
                len++;
            }

            ans = ((ans << len) + i) % MOD;
        }

        return (int)ans;
    }
};