class Solution {
public:
    int numberOfSubstrings(string s) {

        int n = s.size();
        vector<int> cnt(3, 0);

        int left = 0;
        int ans = 0;

        for (int i = 0; i < n; i++) {

            cnt[s[i] - 'a']++;

            while (cnt[0] > 0 && cnt[1] > 0 && cnt[2] > 0) {

                ans += n - i;

                cnt[s[left] - 'a']--;

                left++;
            }
        }

        

        return ans;
    }
};