class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int base = 0;
        for (char c : s)
            if (c == '1') base++;

        string t = "1" + s + "1";
        int n = t.size();

        vector<pair<char, int>> runs;

        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && t[j] == t[i]) j++;
            runs.push_back({t[i], j - i});
            i = j;
        }

        int ans = base;

        for (int i = 1; i + 1 < (int)runs.size(); i++) {
            if (runs[i].first == '1' &&
                runs[i - 1].first == '0' &&
                runs[i + 1].first == '0') {

                ans = max(ans, base + runs[i - 1].second + runs[i + 1].second);
            }
        }

        return ans;
    }
};