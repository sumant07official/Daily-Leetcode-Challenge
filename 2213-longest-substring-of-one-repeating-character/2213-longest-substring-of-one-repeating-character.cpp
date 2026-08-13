class Solution {
public:
    struct Node {
        int len;
        int pref;
        int suff;
        int best;
        char leftChar;
        char rightChar;

        Node() : len(0), pref(0), suff(0), best(0),
                 leftChar('#'), rightChar('#') {}
    };

    vector<Node> seg;

    Node merge(Node &L, Node &R) {
        if (L.len == 0) return R;
        if (R.len == 0) return L;

        Node res;
        res.len = L.len + R.len;

        res.leftChar = L.leftChar;
        res.rightChar = R.rightChar;

        res.pref = L.pref;
        if (L.pref == L.len && L.rightChar == R.leftChar)
            res.pref = L.len + R.pref;

        res.suff = R.suff;
        if (R.suff == R.len && L.rightChar == R.leftChar)
            res.suff = R.len + L.suff;

        res.best = max(L.best, R.best);

        if (L.rightChar == R.leftChar)
            res.best = max(res.best, L.suff + R.pref);

        return res;
    }

    void build(int idx, int l, int r, string &s) {
        if (l == r) {
            seg[idx].len = 1;
            seg[idx].pref = 1;
            seg[idx].suff = 1;
            seg[idx].best = 1;
            seg[idx].leftChar = seg[idx].rightChar = s[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, s);
        build(idx * 2 + 1, mid + 1, r, s);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, char ch) {
        if (l == r) {
            seg[idx].leftChar = seg[idx].rightChar = ch;
            seg[idx].pref = seg[idx].suff = seg[idx].best = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, ch);
        else
            update(idx * 2 + 1, mid + 1, r, pos, ch);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    vector<int> longestRepeating(string s,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {

        int n = s.size();
        seg.resize(4 * n + 5);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int pos = queryIndices[i];
            char ch = queryCharacters[i];

            update(1, 0, n - 1, pos, ch);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};