class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        string t = s + s;

        int diff1 = 0, diff2 = 0;
        int ans = n;

        for (int i = 0; i < 2 * n; i++) {
            char p1 = (i % 2 == 0) ? '0' : '1';
            char p2 = (i % 2 == 0) ? '1' : '0';

            if (t[i] != p1) diff1++;
            if (t[i] != p2) diff2++;

            if (i >= n) {
                char old1 = ((i - n) % 2 == 0) ? '0' : '1';
                char old2 = ((i - n) % 2 == 0) ? '1' : '0';

                if (t[i - n] != old1) diff1--;
                if (t[i - n] != old2) diff2--;
            }

            if (i >= n - 1) {
                ans = min(ans, min(diff1, diff2));
            }
        }

        return ans;
    }
};