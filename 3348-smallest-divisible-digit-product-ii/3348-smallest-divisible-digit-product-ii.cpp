class Solution {
public:
    string smallestNumber(string num, long long t) {
        auto [primeCount, isDivisible] = getPrimeCount(t);

        if (!isDivisible)
            return "-1";

        unordered_map<int, int> factorCount = getFactorCount(primeCount);

        if (sumValues(factorCount) > (int)num.length())
            return construct(factorCount);

        unordered_map<int, int> primeCountPrefix = getPrimeCount(num);

        int firstZeroIndex = num.find('0');

        if (firstZeroIndex == string::npos) {
            firstZeroIndex = num.length();

            if (isSubset(primeCount, primeCountPrefix))
                return num;
        }

        for (int i = num.length() - 1; i >= 0; --i) {
            int d = num[i] - '0';

            primeCountPrefix =
                subtract(primeCountPrefix, kFactorCounts.at(d));

            int spaceAfterThisDigit = num.length() - 1 - i;

            if (i > firstZeroIndex)
                continue;

            for (int biggerDigit = d + 1; biggerDigit < 10; ++biggerDigit) {
                auto factorsAfterReplacement =
                    getFactorCount(
                        subtract(
                            subtract(primeCount, primeCountPrefix),
                            kFactorCounts.at(biggerDigit)));

                if (sumValues(factorsAfterReplacement) <= spaceAfterThisDigit) {
                    int fillOnes =
                        spaceAfterThisDigit -
                        sumValues(factorsAfterReplacement);

                    return num.substr(0, i) +
                           to_string(biggerDigit) +
                           string(fillOnes, '1') +
                           construct(factorsAfterReplacement);
                }
            }
        }

        auto factorsAfterExtension = getFactorCount(primeCount);

        return string(
                   num.length() + 1 -
                       sumValues(factorsAfterExtension),
                   '1') +
               construct(factorsAfterExtension);
    }

private:
    inline static const unordered_map<int,
        unordered_map<int, int>> kFactorCounts = {
        {0, {}},
        {1, {}},
        {2, {{2, 1}}},
        {3, {{3, 1}}},
        {4, {{2, 2}}},
        {5, {{5, 1}}},
        {6, {{2, 1}, {3, 1}}},
        {7, {{7, 1}}},
        {8, {{2, 3}}},
        {9, {{3, 2}}}
    };

    pair<unordered_map<int, int>, bool>
    getPrimeCount(long long t) {
        unordered_map<int, int> count{
            {2, 0}, {3, 0}, {5, 0}, {7, 0}
        };

        for (int prime : {2, 3, 5, 7}) {
            while (t % prime == 0) {
                t /= prime;
                ++count[prime];
            }
        }

        return {count, t == 1};
    }

    unordered_map<int, int>
    getPrimeCount(const string& num) {
        unordered_map<int, int> count{
            {2, 0}, {3, 0}, {5, 0}, {7, 0}
        };

        for (char c : num) {
            for (auto& [prime, freq]
                 : kFactorCounts.at(c - '0')) {
                count[prime] += freq;
            }
        }

        return count;
    }

    unordered_map<int, int>
    getFactorCount(const unordered_map<int, int>& count) {
        unordered_map<int, int> res;

        int count8 = count.at(2) / 3;
        int rem2 = count.at(2) % 3;

        int count9 = count.at(3) / 2;
        int count3 = count.at(3) % 2;

        int count4 = rem2 / 2;
        int count2 = rem2 % 2;

        int count6 = 0;

        if (count2 == 1 && count3 == 1) {
            count2 = 0;
            count3 = 0;
            count6 = 1;
        }

        if (count3 == 1 && count4 == 1) {
            count2 = 1;
            count6 = 1;
            count3 = 0;
            count4 = 0;
        }

        res[2] = count2;
        res[3] = count3;
        res[4] = count4;
        res[5] = count.at(5);
        res[6] = count6;
        res[7] = count.at(7);
        res[8] = count8;
        res[9] = count9;

        return res;
    }

    string construct(
        const unordered_map<int, int>& factors) {
        string res;

        for (int digit = 2; digit < 10; ++digit) {
            auto it = factors.find(digit);

            if (it != factors.end())
                res += string(it->second,
                              char('0' + digit));
        }

        return res;
    }

    bool isSubset(
        const unordered_map<int, int>& a,
        const unordered_map<int, int>& b) {
        for (auto& [k, v] : a) {
            auto it = b.find(k);

            if (it == b.end() || it->second < v)
                return false;
        }

        return true;
    }

    unordered_map<int, int>
    subtract(unordered_map<int, int> a,
             const unordered_map<int, int>& b) {
        for (auto& [k, v] : b)
            a[k] = max(0, a[k] - v);

        return a;
    }

    int sumValues(
        const unordered_map<int, int>& cnt) {
        int sum = 0;

        for (auto& [k, v] : cnt)
            sum += v;

        return sum;
    }
};