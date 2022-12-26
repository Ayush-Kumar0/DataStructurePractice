#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void sievePrimes(int n)
{
    vector<bool> v(n + 1, true);

    for (int i = 2; i * i <= n; i++)
    {
        if (v.at(i) == true)
            // for (int j = 2 * i; j <= n; j = j + i)
            for (int j = i * i; j <= n; j = j + i)
                v[j] = false;
    }

    for (int i = 2; i < n + 1; i++)
        if (v.at(i) == true)
            cout << i << "  ";
    cout << "\n";
}

void segmentedSieve(int l, int h)
{
    vector<int> u(sqrt(h) + 1, true), v(h - l + 1, true);

    for (int i = 2; i * i <= sqrt(h); i++)
        if (u.at(i))
            for (int j = 2 * i; j <= sqrt(h); j++)
                u.at(j) = false;

    for (int i = 2; i <= sqrt(h); i++)
    {
        if (u.at(i) == true)
            for (int j = l / i * i; j <= h; j += i)
                if (j - l >= 0)
                    v.at(j - l) = false;
    }

    for (int i = l; i <= h; i++)
        if (v.at(i - l))
            cout << (i) << "  ";
    cout << "\n";
}

int main(int argc, char *argv[])
{
    segmentedSieve(1000000000, 1000000090);
    // segmentedSieve(53, 97);
    return 0;
}