#include <algorithm>
#include <iostream>
using namespace std;

#include "calculator.hpp"

size_t countMinThrows(size_t height, size_t point)
{
    size_t cnt = 0;
    int lo = 0;
    int hi = height;
    while (hi - lo > 1)
    {
        cnt++;
        int mid = lo + (hi - lo) / 2;
        if (mid == point)
            break;
        else if (point < mid)
            hi = mid;
        else
            lo = mid;
    }

    return cnt;
}

int main()
{
    // Lit* foo = new Lit("5");
    // cout << foo->Mul(Lit("2"))->Add(Lit("2"))->Mul(Lit("4"))->simplify()->toString() << endl;
    size_t mm = 0, height = 10000;
    for (int i = 1; i <= height; i++)
    {
        size_t count = countMinThrows(height, i);
        mm = max(mm, count);
    }
    cout << "Max count: " << mm << endl;
    return 0;
}