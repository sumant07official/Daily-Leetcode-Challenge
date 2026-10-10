
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();
        vector<int> diff(n);
        int mx = 0;
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
            sum += diff[i];
        }

        if (sum <= k) return 0;

        int left = 0, right = mx;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid) need += d - mid;
            }

            if (need <= k)
                right = mid;
            else
                left = mid + 1;
        }

        int level = left;
        long long ans = 0;

        for (int d : diff) {
            if (d > level) {
                long long x = level;
                ans += x * x;
                k -= d - level;
            } else {
                ans += 1LL * d * d;
            }
        }

        // Use remaining operations to reduce level-valued differences.
        for (int d : diff) {
            if (d >= level && level > 0 && k > 0) {
                ans -= 2LL * level - 1;
                k--;
            }
        }

        return ans;
    }
};
