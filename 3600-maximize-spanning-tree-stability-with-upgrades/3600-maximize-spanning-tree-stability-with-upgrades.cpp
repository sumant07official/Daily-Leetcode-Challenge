class Solution {
public:
    struct DSU {
        vector<int> p, sz;

        DSU(int n) {
            p.resize(n);
            sz.assign(n, 1);
            iota(p.begin(), p.end(), 0);
        }

        int find(int x) {
            return p[x] == x ? x : p[x] = find(p[x]);
        }

        bool unite(int a, int b) {
            a = find(a);
            b = find(b);

            if (a == b) return false;

            if (sz[a] < sz[b]) swap(a, b);

            p[b] = a;
            sz[a] += sz[b];
            return true;
        }
    };

    bool can(int n, vector<vector<int>>& edges, int k, long long X) {
        DSU dsu(n);

        int comps = n;

        // mandatory edges
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            long long s = e[2];
            int must = e[3];

            if (must) {
                if (s < X) return false;

                if (!dsu.unite(u, v))
                    return false; // cycle among mandatory edges

                comps--;
            }
        }

        vector<pair<int,int>> freeEdges;
        vector<pair<int,int>> upgradeEdges;

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            long long s = e[2];
            int must = e[3];

            if (must) continue;

            if (s >= X)
                freeEdges.push_back({u, v});
            else if (2 * s >= X)
                upgradeEdges.push_back({u, v});
        }

        for (auto &[u, v] : freeEdges) {
            if (dsu.unite(u, v))
                comps--;
        }

        int used = 0;

        for (auto &[u, v] : upgradeEdges) {
            if (comps == 1) break;

            if (dsu.unite(u, v)) {
                comps--;
                used++;
            }
        }

        return comps == 1 && used <= k;
    }

    int maxStability(int n, vector<vector<int>>& edges, int k) {
        long long lo = 0, hi = 2000000000LL;
        long long ans = -1;

        while (lo <= hi) {
            long long mid = (lo + hi) >> 1;

            if (can(n, edges, k, mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return (int)ans;
    }
};