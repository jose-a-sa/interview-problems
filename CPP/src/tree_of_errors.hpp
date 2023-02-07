#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
public:
    const string possibleNodes = "ABCDEFGHIJKLMNOPQRSTUVXWYZ";
    void treeErrors(string pairs)
    {
        unordered_set<char> nodes;
        unordered_map<char, int> inDegree;
        unordered_map<char, unordered_set<char>> tree;

        istringstream iss(pairs);
        string pair;
        while (iss >> pair)
        {
            bool fail1 = false, fail2 = false, fail3 = false;

            fail1 |= pair[0] != '(' || pair[2] != ',' || pair[4] != ')';
            fail1 |= possibleNodes.find(pair[1]) == -1 || possibleNodes.find(pair[3]) == -1;
            if (fail1)
            {
                cout << "E1";
                return;
            }

            char parent = pair.at(1);
            char child = pair.at(3);
            nodes.insert(parent);
            nodes.insert(child);

            fail2 |= tree[parent].count(child) > 0;
            if (fail2)
            {
                cout << "E2";
                return;
            }

            tree[parent].insert(child);
            inDegree[child]++;

            fail3 |= tree[parent].size() > 2;
            if (fail3)
            {
                cout << "E3";
                return;
            }
        }
        // run bfs

        queue<char> bfs;
        vector<int> visited(26, 0);

        for (char c : possibleNodes)
            if (inDegree[c] == 0 && nodes.count(c))
            {
                bfs.push(c);
                visited[c - 'A'] = 1;
            }

        if (bfs.size() > 1)
        {
            cout << "E4";
            return;
        }
        if (bfs.size() == 0)
        {
            cout << "E5";
            return;
        }

        while (!bfs.empty())
        {
            char p = bfs.front();
            bfs.pop();

            for (char c : tree[p])
            {
                if (!visited[c - 'A'])
                {
                    visited[c - 'A'] = 1;
                    bfs.push(c);
                }
                else if (inDegree[c] > 1)
                {
                    cout << "E5";
                    return;
                }
            }
        }
    }
};
