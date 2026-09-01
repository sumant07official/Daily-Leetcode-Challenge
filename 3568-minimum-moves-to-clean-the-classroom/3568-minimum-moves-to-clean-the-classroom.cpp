class Solution {
public:
    struct State {
        int r, c, mask, energy, dist;
    };

    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        int k = 0;

        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litterId[i][j] = k++;
                }
            }
        }

        int fullMask = (1 << k) - 1;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n,
                vector<int>(1 << k, -1))
        );

        queue<State> q;
        q.push({sr, sc, 0, energy, 0});
        best[sr][sc][0] = energy;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            if (cur.mask == fullMask)
                return cur.dist;

            for (int d = 0; d < 4; d++) {
                int nr = cur.r + dr[d];
                int nc = cur.c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                char cell = classroom[nr][nc];

                if (cell == 'X')
                    continue;

                if (cur.energy == 0)
                    continue;

                int ne = cur.energy - 1;
                int nmask = cur.mask;

                if (cell == 'R')
                    ne = energy;

                if (cell == 'L')
                    nmask |= (1 << litterId[nr][nc]);

                if (best[nr][nc][nmask] >= ne)
                    continue;

                best[nr][nc][nmask] = ne;

                q.push({
                    nr,
                    nc,
                    nmask,
                    ne,
                    cur.dist + 1
                });
            }
        }

        return -1;
    }
};