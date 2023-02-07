#include "calculator.hpp"

#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

Lit::Lit(string x) : expr(x)
{
}

Lit *Lit::Add(const Lit &rhs)
{
    this->expr = "(" + this->toString() + " + " + rhs.toString() + ")";
    return this;
}
Lit *Lit::Sub(const Lit &rhs)
{
    this->expr = "(" + this->toString() + " - " + rhs.toString() + ")";
    return this;
}
Lit *Lit::Mul(const Lit &rhs)
{
    this->expr = "(" + this->toString() + " * " + rhs.toString() + ")";
    return this;
}

Lit *Lit::simplify()
{
    stack<string> st;
    string num;
    for (char c : this->toString())
    {
        // handle spaces
        if (c == ' ')
            continue;

        // handle digits
        if (isdigit(c))
        {
            num.push_back(c);
            continue;
        }
        if (num.size() > 0)
            st.push(num);
        num = "";
        // end handle numbers

        st.push(string(1, c));

        while (st.top() == ")")
        {
            st.pop(); // ")"
            int x2 = stoi(st.top());
            st.pop();
            string op = st.top();
            st.pop();
            int x1 = stoi(st.top());
            st.pop();
            st.pop(); // "("

            if (op == "+")
                st.push(to_string(x1 + x2));
            else if (op == "-")
                st.push(to_string(x1 - x2));
            else if (op == "*")
                st.push(to_string(x1 * x2));
        }
    }

    this->expr = st.top();
    return this;
}

string Lit::toString() const
{
    return this->expr;
}

int main()
{
    Lit *foo = new Lit("5");
    Lit *bar = foo->Mul(Lit("2"))->Add(Lit("2"))->Mul(Lit("4"));
    cout << bar->toString() << endl;
    cout << bar->simplify()->toString() << endl;
    return 0;
}