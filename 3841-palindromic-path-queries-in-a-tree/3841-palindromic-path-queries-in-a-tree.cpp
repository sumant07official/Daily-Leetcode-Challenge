
class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n, 0);
        vector<int> sz(n, 1), heavy(n, -1), order;
        order.reserve(n);

        // Build parent and depth iteratively.
        vector<int> st = {0};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        // Compute subtree sizes and heavy children.
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            int best = 0;

            for (int v : adj[u]) {
                if (parent[v] != u) continue;

                sz[u] += sz[v];
                if (sz[v] > best) {
                    best = sz[v];
                    heavy[u] = v;
                }
            }
        }

        // Assign HLD chain heads and positions.
        vector<int> head(n), pos(n);
        int timer = 0;
        vector<pair<int, int>> chains = {{0, 0}};

        while (!chains.empty()) {
            auto [start, h] = chains.back();
            chains.pop_back();

            for (int u = start; u != -1; u = heavy[u]) {
                head[u] = h;
                pos[u] = timer++;

                for (int v : adj[u]) {
                    if (parent[v] == u && v != heavy[u]) {
                        chains.push_back({v, v});
                    }
                }
            }
        }

        // Segment tree storing XOR of character masks.
        int base = 1;
        while (base < n) base <<= 1;

        vector<int> seg(2 * base, 0);

        for (int u = 0; u < n; ++u) {
            seg[base + pos[u]] = 1 << (s[u] - 'a');
        }

        for (int i = base - 1; i >= 1; --i) {
            seg[i] = seg[i * 2] ^ seg[i * 2 + 1];
        }

        auto update = [&](int p, int value) {
            p += base;
            seg[p] = value;

            for (p >>= 1; p > 0; p >>= 1) {
                seg[p] = seg[p * 2] ^ seg[p * 2 + 1];
            }
        };

        auto rangeXor = [&](int l, int r) {
            int result = 0;
            l += base;
            r += base;

            while (l < r) {
                if (l & 1) result ^= seg[l++];
                if (r & 1) result ^= seg[--r];
                l >>= 1;
                r >>= 1;
            }

            return result;
        };

        auto pathXor = [&](int u, int v) {
            int mask = 0;

            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]]) {
                    swap(u, v);
                }

                mask ^= rangeXor(pos[head[u]], pos[u] + 1);
                u = parent[head[u]];
            }

            if (depth[u] > depth[v]) swap(u, v);

            mask ^= rangeXor(pos[u], pos[v] + 1);
            return mask;
        };

        vector<bool> answer;

        for (const string& q : queries) {
            string type;
            int u;
            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                s[u] = c;
                update(pos[u], 1 << (c - 'a'));
            } else {
                int v;
                ss >> v;

                int mask = pathXor(u, v);
                answer.push_back((mask & (mask - 1)) == 0);
            }
        }

        return answer;
    }
};
