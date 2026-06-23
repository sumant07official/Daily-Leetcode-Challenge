class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> zeros(n);

        // Count trailing zeros in each row
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--) {
                cnt++;
            }
            zeros[i] = cnt;
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int need = n - 1 - i;

            int j = i;
            while (j < n && zeros[j] < need) {
                j++;
            }

            if (j == n) return -1;

            ans += (j - i);

            while (j > i) {
                swap(zeros[j], zeros[j - 1]);
                j--;
            }
        }

        return ans;
    }
};