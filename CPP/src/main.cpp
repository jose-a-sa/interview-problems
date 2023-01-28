#include <iostream>
using namespace std;

#include "glassBallThrows.hpp"

int main()
{
    // Lit* foo = new Lit("5");
    // cout << foo->Mul(Lit("2"))->Add(Lit("2"))->Mul(Lit("4"))->simplify()->toString() << endl;
    size_t mm = 0, height = 100;
    for (int i = 1; i <= height; i++)
    {
        size_t count = glassBallMinThrows(height, i);
        mm = max(mm, count);
    }
    cout << "Max count: " << mm << endl;
    return 0;
}