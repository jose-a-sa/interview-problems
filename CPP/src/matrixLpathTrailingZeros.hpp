#include <iostream>
#include <vector>
#include <stack>

using namespace std;

pair<size_t, size_t> operator+(const pair<size_t, size_t> &l, const pair<size_t, size_t> &r)
{
    return {l.first + r.first, l.second + r.second};
}

pair<size_t, size_t> operator-(const pair<size_t, size_t> &l, const pair<size_t, size_t> &r)
{
    return {l.first - r.first, l.second - r.second};
}

size_t min(pair<size_t, size_t> p)
{
    return p.first < p.second ? p.first : p.second;
}

class Solution
{
public:
    template <class T>
    using matrix = vector<vector<T>>;

    pair<size_t, size_t> factorize(int x)
    {
        size_t x2 = 0, x5 = 0;
        while (x % 2 == 0)
        {
            x /= 2;
            x2++;
        }
        while (x % 5 == 0)
        {
            x /= 5;
            x5++;
        }
        return {x2, x5};
    }

    int maxTrailingZeros(vector<vector<int>> &grid)
    {
        const size_t n = grid.size();
        const size_t m = grid.front().size();
        matrix<pair<size_t, size_t>> left(n, vector<pair<size_t, size_t>>(m));
        matrix<pair<size_t, size_t>> top(n, vector<pair<size_t, size_t>>(m));

        for (size_t i = 0; i < n; ++i)
        {
            left[i][0] = factorize(grid[i][0]);
            for (size_t j = 1; j < m; ++j)
                left[i][j] = factorize(grid[i][j]) + left[i][j - 1];
        }

        for (size_t j = 0; j < m; ++j)
        {
            top[0][j] = factorize(grid[0][j]);
            for (size_t i = 1; i < n; ++i)
                top[i][j] = factorize(grid[i][j]) + top[i - 1][j];
        }

        size_t count = 0;

        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
            {
                pair<size_t, size_t> curr = factorize(grid[i][j]);
                count = max(count, min(left[i][j] + top[i][j] - curr));
                count = max(count, min(left[i][m - 1] - left[i][j] + top[i][j]));
                count = max(count, min(left[i][j] + top[n - 1][j] - top[i][j]));
                count = max(count, min(left[i][m - 1] - left[i][j] + top[n - 1][j] - top[i][j] + curr));
            }

        return count;
    }
};