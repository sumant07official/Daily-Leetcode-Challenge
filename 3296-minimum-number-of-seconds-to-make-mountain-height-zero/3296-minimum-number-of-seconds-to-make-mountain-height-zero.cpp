class Solution {
public:
    bool can(long long T, int mountainHeight, vector<int>& workerTimes) {
        long long total = 0;

        for (long long w : workerTimes) {
            long double val = 1.0L + (8.0L * T) / w;

            long long x = (long long)((sqrtl(val) - 1.0L) / 2.0L);

            while (w * x * (x + 1) / 2 > T) x--;

            while (w * (x + 1) * (x + 2) / 2 <= T) x++;

            total += x;

            if (total >= mountainHeight)
                return true;
        }

        return false;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long low = 0;
        long long high = 1e18;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (can(mid, mountainHeight, workerTimes)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};