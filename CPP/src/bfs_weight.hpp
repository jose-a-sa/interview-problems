#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
public:
    struct VertexData
    {
        int cost, time, node;
        VertexData(int c, int t, int n) : cost(c), time(t), node(n){};
    };

    struct GreaterVertex
    {
        bool operator()(const VertexData &lhs, const VertexData &rhs)
        {
            if (lhs.cost > rhs.cost)
                return true;
            if (lhs.cost == rhs.cost && lhs.time > rhs.time)
                return true;
            if (lhs.cost == rhs.cost && lhs.time == rhs.time && lhs.node > rhs.node)
                return true;

            return false;
        }
    };

    int minCost(int maxTime, vector<vector<int>> &edges, vector<int> &passingFees)
    {
        size_t V = passingFees.size();
        size_t E = edges.size();

        unordered_map<int, vector<pair<int, int>>> adj;
        for (size_t i = 0; i < V; ++i)
            adj[i] = vector<pair<int, int>>();

        for (auto e : edges)
        {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        vector<int> cost(V, INT_MAX);
        vector<int> time(V, INT_MAX);

        cost[0] = passingFees[0];
        time[0] = 0;

        priority_queue<VertexData, vector<VertexData>, GreaterVertex> pq;
        pq.push(VertexData(cost[0], time[0], 0));

        while (!pq.empty())
        {
            VertexData cur = pq.top();
            pq.pop();

            for (const pair<int, int> &e : adj[cur.node])
            {
                int n = e.first;
                int cost_e = cur.cost + passingFees[n];
                int time_e = cur.time + e.second;

                if (time_e <= maxTime)
                {
                    if (cost[n] > cost_e) // prioritize edges with minumum cost of the dest node
                    {
                        cost[n] = cost_e;
                        time[n] = time_e;
                        pq.push(VertexData(cost_e, time_e, n));
                    }
                    else if (time[n] > time_e) // prioritize edges with minumum time added for optimization
                    {
                        time[n] = time_e;
                        pq.push(VertexData(cost_e, time_e, n));
                    }
                }
            }
        }
        printf("Time: %d\n", (time[V - 1] == INT_MAX) ? -1 : time[V - 1]);
        return (cost[V - 1] == INT_MAX) ? -1 : cost[V - 1];
    }
};