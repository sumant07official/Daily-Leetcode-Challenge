class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> dp1(MAXX, false);
        vector<bool> dp2(MAXX, false);
        vector<bool> dp3(MAXX, false);

        for (int v : nums) {
            // Update in reverse order to avoid reusing the same element
            for (int x = 0; x < MAXX; x++) {
                if (dp2[x])
                    dp3[x ^ v] = true;
            }

            for (int x = 0; x < MAXX; x++) {
                if (dp1[x])
                    dp2[x ^ v] = true;
            }

            dp1[v] = true;
        }

        int ans = 0;
        for (int x = 0; x < MAXX; x++) {
            if (dp1[x] || dp3[x])
                ans++;
        }

        return ans;
    }
};