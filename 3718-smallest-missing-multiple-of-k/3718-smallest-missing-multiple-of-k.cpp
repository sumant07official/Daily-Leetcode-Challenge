class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> st(nums.begin(), nums.end());

        int curr = k;

        while (st.count(curr)) {
            curr += k;
        }

        return curr;
    }
};