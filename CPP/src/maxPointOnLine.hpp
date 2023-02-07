// #include <hash_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

template <class T1, class T2>
struct pair_hash
{
    size_t operator()(const pair<T1, T2> &p) const
    {
        size_t seed = 0;
        // BOOST hash_combine algorithm
        seed ^= hash<T1>{}(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash<T2>{}(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

template <class Key, class Value, class Compare = std::less<Value>>
struct by_value
{
    size_t operator()(const pair<Key, Value> &x, const pair<Key, Value> &y) const
    {
        return Compare()(x.second, y.second);
    }
};

class Solution
{
public:
    pair<int, int> normalize_gcd(int x, int y)
    {
        int div = gcd(x, y);
        if (div == 0)
            return {0, 0};

        return {x / div, y / div};
    }

    int maxPoints(vector<vector<int>> &points)
    {
        size_t res = 0;
        size_t n = points.size();

        if (n < 2)
            return n;

        for (int i = 0; i < n; ++i)
        {
            unordered_map<pair<int, int>, size_t, pair_hash<int, int>> cnt;

            for (int j = 0; j < n; ++j)
                if (i != j)
                    cnt[normalize_gcd(points[j][0] - points[i][0], points[j][1] - points[i][1])]++;

            auto max_count_kv = *max_element(cnt.begin(), cnt.end(),
                                             by_value<pair<int, int>, size_t>());

            res = max(res, max_count_kv.second + 1);
        }

        return res;
    }
};