#pragma once

#include <string>

using namespace std;

class Lit
{
private:
    string expr;
public:
    Lit(string x);
    Lit *Add(const Lit &rhs);
    Lit *Sub(const Lit &rhs);
    Lit *Mul(const Lit &rhs);
    Lit *simplify();
    string toString() const;
};
