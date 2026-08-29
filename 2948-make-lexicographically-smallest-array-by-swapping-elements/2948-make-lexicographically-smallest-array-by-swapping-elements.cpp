class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> vp; // {value, index}
        for (int i = 0; i < n; i++) {
            vp.push_back({nums[i], i});
        }

        sort(vp.begin(), vp.end());

        vector<int> ans(n);

        int i = 0;
        while (i < n) {
            int j = i;

            // Find one connected group
            while (j + 1 < n &&
                   vp[j + 1].first - vp[j].first <= limit) {
                j++;
            }

            vector<int> indices;
            vector<int> values;

            for (int k = i; k <= j; k++) {
                indices.push_back(vp[k].second);
                values.push_back(vp[k].first);
            }

            sort(indices.begin(), indices.end());

            for (int k = 0; k < indices.size(); k++) {
                ans[indices[k]] = values[k];
            }

            i = j + 1;
        }

        return ans;
    }
};