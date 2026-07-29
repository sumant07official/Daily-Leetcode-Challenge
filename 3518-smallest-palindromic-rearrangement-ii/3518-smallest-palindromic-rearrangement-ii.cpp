class Solution {
public:
    static const long long LIM = 1000001;

    long long C(int n, int r) {
        if (r > n) return 0;
        r = min(r, n - r);
        long long ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - i + 1) / i;
            if (ans >= LIM) return LIM;
        }
        return ans;
    }

    long long ways(vector<int> &cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = 1;
        int rem = total;

        for (int x : cnt) {
            if (x == 0) continue;
            ans *= C(rem, x);
            if (ans >= LIM) return LIM;
            rem -= x;
        }
        return ans;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        char mid = 0;
        vector<int> half(26);

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2)
                mid = char('a' + i);
            half[i] = freq[i] / 2;
        }

        if (ways(half) < k)
            return "";

        int len = 0;
        for (int x : half) len += x;

        string left = "";

        while ((int)left.size() < len) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;

                long long cnt = ways(half);

                if (cnt >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= cnt;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid)
            return left + string(1, mid) + right;
        return left + right;
    }
};