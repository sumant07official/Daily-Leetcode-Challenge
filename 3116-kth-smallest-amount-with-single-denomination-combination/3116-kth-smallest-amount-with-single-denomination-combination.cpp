class Solution {
public:
    long long lcmLL(long long a, long long b) {
        return a / gcd(a, b) * b;
    }

    long long countNums(vector<int>& coins, long long x) {
        int n = coins.size();
        long long cnt = 0;

        for (int mask = 1; mask < (1 << n); mask++) {
            long long l = 1;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    l = lcmLL(l, coins[i]);

                    if (l > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid) continue;

            int bits = __builtin_popcount(mask);

            if (bits & 1)
                cnt += x / l;
            else
                cnt -= x / l;
        }

        return cnt;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1e15;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countNums(coins, mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};