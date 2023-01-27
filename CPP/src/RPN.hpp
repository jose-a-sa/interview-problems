#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool is_op(string s)
    {
        return s=="+" || s=="*" || s=="-" || s=="/";
    }
    string operate(string x, string y, string op)
    {
        int res = 0;
        if(op == "+")
            res = stoi(x) + stoi(y);
        else if(op == "*")
            res = stoi(x) * stoi(y);
        else if(op == "-")
            res = stoi(x) - stoi(y);
        else if(op == "/")
            res = stoi(x) / stoi(y);
        return to_string(res);
    }

    int evalRPN(vector<string>& v) {
        size_t n = v.size();
        size_t st_n = 0;
        vector<string> st;
        int i = v.size()-1;
        while(st_n > 1 || i>=0)
        {
            if(st_n>=3)
            {
                if(!is_op(st[st_n-1]) && !is_op(st[st_n-2]) && is_op(st[st_n-3]))
                {
                    string res = operate(st[st_n-1], st[st_n-2], st[st_n-3]);
                    st.pop_back();
                    st.pop_back();
                    st.pop_back();
                    st.push_back(res);
                    st_n-=2;
                    continue;
                }
            }

            st.push_back(v[i--]);
            st_n++;

            for(const string &ss : st)
            {
                cout << ss << " ";
            }
            cout << endl;
        }
        return stoi(st.front());
    }
};