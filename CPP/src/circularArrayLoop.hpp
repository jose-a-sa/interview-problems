#include <bitset>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution
{

private:
    const uint32_t VISITED = 0b0001;
    const uint32_t ON_STACK = 0b0010;
    const uint32_t HAS_CYCLE = 0b0100;

    int arrayAdjacency(const vector<int> &nums, const int v)
    {
        vector<int>::size_type V = nums.size();
        int next = (v + nums[v]);
        while (next < 0)
            next += V;
        return (next % V);
    }

    bool check(const uint32_t st, const uint32_t bit)
    {
        return ((st & bit) == bit);
    }

    void set(uint32_t &st, const uint32_t bit)
    {
        st |= bit;
    }

    void unset(uint32_t &st, const uint32_t bit)
    {
        st &= ~bit;
    }

public:
    bool circularArrayLoop(vector<int> &nums)
    {
        vector<int>::size_type V = nums.size();
        vector<uint32_t> state(V, 0);
        stack<int> st;

        for (int v = 0; v < V; v++)
        {
            printf("START ANOTHER SOURCE: %d\n", v);

            if (check(state[v], VISITED))
                continue;

            bool circular = true;
            st.push(v);

            while (!st.empty())
            {
                int s = st.top();
                int w = arrayAdjacency(nums, s);

                printf("Stack top: %d\n", s);

                // stack not empty but visited, i.e path backtracking
                if (check(state[s], VISITED))
                {
                    unset(state[s], ON_STACK);
                    st.pop();

                    circular &= !(nums[s] * nums[w] < 0 || w == s);

                    if (check(state[s], HAS_CYCLE) && circular)
                    {
                        cout << "STACK RETURN TO CYCLE AT " << s << endl;
                        return true;
                    }

                    continue;
                }

                set(state[s], VISITED | ON_STACK);

                if (!check(state[w], VISITED))
                {
                    st.push(w);
                }
                else if (check(state[w], ON_STACK))
                {
                    cout << "FOUND CYCLE AT " << w << endl;
                    set(state[w], HAS_CYCLE);
                }
            }

            for (int k = 0; k < V; ++k)
            {
                cout << bitset<3>(state[k]) << " ";
            }
            cout << endl;
        }
        return false;
    }
};
