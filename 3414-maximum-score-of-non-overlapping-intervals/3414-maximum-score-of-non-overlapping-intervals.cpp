class Solution {
public:
    struct Node {
        long long score;
        vector<int> ids;
    };

    vector<vector<int>> arr;
    vector<int> nxt;
    vector<vector<Node>> memo;
    vector<vector<bool>> vis;
    int n;

    Node better(const Node& a, const Node& b) {
        if (a.score != b.score)
            return (a.score > b.score) ? a : b;

        return (a.ids < b.ids) ? a : b;
    }

    Node dfs(int i, int used) {
        if (i >= n || used == 4)
            return {0, {}};

        if (vis[i][used])
            return memo[i][used];

        vis[i][used] = true;

        Node skip = dfs(i + 1, used);

        Node take = dfs(nxt[i], used + 1);
        take.score += arr[i][2];

        take.ids.insert(take.ids.begin(), arr[i][3]);
        sort(take.ids.begin(), take.ids.end());

        memo[i][used] = better(skip, take);
        return memo[i][used];
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        n = intervals.size();

        arr.clear();

        for (int i = 0; i < n; i++) {
            arr.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(arr.begin(), arr.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        vector<int> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = arr[i][0];

        nxt.assign(n, n);

        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(
                         starts.begin(),
                         starts.end(),
                         arr[i][1]
                     ) - starts.begin();
        }

        memo.assign(n + 1, vector<Node>(5));
        vis.assign(n + 1, vector<bool>(5, false));

        Node ans = dfs(0, 0);

        sort(ans.ids.begin(), ans.ids.end());
        return ans.ids;
    }
};