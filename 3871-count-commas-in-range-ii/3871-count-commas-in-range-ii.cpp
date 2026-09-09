class Solution {
public:
    long long countCommas(long long n) {

        long long ans = 0;

        for (long long start = 1000, commas = 1;
             start <= n;
             start *= 1000, commas++) {

            long long end = min(n, start * 1000 - 1);

            ans += (end - start + 1) * commas;
        }

        return ans;
    }
};