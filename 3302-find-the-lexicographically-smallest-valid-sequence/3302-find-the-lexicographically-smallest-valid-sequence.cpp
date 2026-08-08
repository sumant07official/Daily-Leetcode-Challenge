class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        vector<int> suf(n + 1, m);
        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) j--;
            suf[i] = j + 1;
        }

        vector<int> ans;
        bool usedMismatch = false;
        int p = 0;

        for (int i = 0; i < n && p < m; i++) {

            if (word1[i] == word2[p]) {
                ans.push_back(i);
                p++;
            }
            else if (!usedMismatch) {
                int need = m - (p + 1);

                if (suf[i + 1] <= p + 1) {
                    usedMismatch = true;
                    ans.push_back(i);
                    p++;
                }
            }
        }

        if (p < m) return {};

        return ans;
    }
};