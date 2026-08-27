class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char ch : s) cnt[ch - 'a']++;

        // Walk left to right, staying "tight" to target, and remember the
        // latest position where we can place a char strictly greater than target[i].
        vector<int> rem = cnt;      // letters still unused as we match target
        int bestK = -1, bestChar = -1;

        for (int i = 0; i < n; i++) {
            int ti = target[i] - 'a';

            // Can we break here? Find smallest available letter > target[i].
            for (int c = ti + 1; c < 26; c++) {
                if (rem[c] > 0) { bestK = i; bestChar = c; break; }
            }

            // Consume target[i] to keep the prefix equal to target.
            if (rem[ti] > 0) rem[ti]--;
            else break;             // can't match target any further
        }

        if (bestK == -1) return ""; // no permutation is strictly greater

        // Reconstruct: target[0..bestK-1] + bestChar + remaining sorted ascending.
        vector<int> left = cnt;
        string ans;
        for (int i = 0; i < bestK; i++) {
            ans += target[i];
            left[target[i] - 'a']--;
        }
        ans += char('a' + bestChar);
        left[bestChar]--;
        for (int c = 0; c < 26; c++)
            ans.append(left[c], char('a' + c));

        return ans;
    }
};