class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        // cnt[g] = numbers divisible by g
        vector<long long> cnt(mx + 1, 0);
        for (int g = 1; g <= mx; g++) {
            for (int j = g; j <= mx; j += g)
                cnt[g] += freq[j];
        }

        // exact[g] = pairs whose gcd is exactly g
        vector<long long> exact(mx + 1, 0);
        for (int g = mx; g >= 1; g--) {
            long long c = cnt[g];
            exact[g] = c * (c - 1) / 2;

            for (int j = 2 * g; j <= mx; j += g)
                exact[g] -= exact[j];
        }

        // prefix counts in sorted gcd array
        vector<long long> pref(mx + 1, 0);
        for (int g = 1; g <= mx; g++)
            pref[g] = pref[g - 1] + exact[g];

        vector<int> ans;
        for (long long k : queries) {
            // k is 0-indexed
            int g = lower_bound(pref.begin() + 1, pref.end(), k + 1) - pref.begin();
            ans.push_back(g);
        }

        return ans;
    }
};