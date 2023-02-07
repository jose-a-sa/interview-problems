#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    const unsigned int M = 1000000007;
    size_t recUtil(int n, int m, int i, int j, int k, const vector<vector<int>> &acc, vector<vector<vector<int>>> &memo)
    {
        if (memo[i][j][k] != INT_MIN)
            return memo[i][j][k];
        if (acc[i][j] == 0)
            return 0;
        if (k == 0)
            return 1;

        size_t res = 0;

        for (size_t r = i + 1; r < n; ++r)
            if (acc[i][j] - acc[r][j] > 0)
                res = (res + recUtil(n, m, r, j, k - 1, acc, memo)) % M;

        for (size_t c = j + 1; c < m; ++c)
            if (acc[i][j] - acc[i][c] > 0)
                res = (res + recUtil(n, m, i, c, k - 1, acc, memo)) % M;

        return memo[i][j][k] = res;
    }

public:
    int ways(vector<string> &pizza, int k)
    {
        size_t n = pizza.size();
        size_t m = pizza.front().size();

        vector<vector<int>> acc(n, vector<int>(m, 0));

        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = m - 1; j >= 0; --j)
            {
                acc[i][j] = (pizza[i][j] == 'A');
                acc[i][j] += (i + 1 < n) ? acc[i + 1][j] : 0;
                acc[i][j] += (j + 1 < m) ? acc[i][j + 1] : 0;
                acc[i][j] += (i + 1 < n && j + 1 < m) ? -acc[i + 1][j + 1] : 0;
            }
        }

        vector<vector<vector<int>>> memo(n, vector<vector<int>>(m, vector<int>(k, INT_MIN)));

        return recUtil(n, m, 0, 0, k - 1, acc, memo);
    }
};
