#include <algorithm>
#include <iostream>
using namespace std;

size_t glassBallMinThrows(size_t height, size_t point)
{
    size_t cnt = 0;
    int lo = 0;
    int hi = height;
    while (hi - lo > 1)
    {
        cnt++;
        int mid = lo + (hi - lo) / 2;
        if (mid < point)
            lo = mid;
        else
            hi = mid;
    }
    cout << "Final: " << cnt;
    cout << ", Check: " << ((hi == point) ? "true" : "false") << endl;

    return cnt;
}
