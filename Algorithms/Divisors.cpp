#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void printAllDivisors(int n)
{
    int i;
    for (i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
            cout << i << " ";
    }
    for (; i >= 1; i--)
    {
        if (n % i == 0 && i != n / i)
            cout << n / i << " ";
    }
}

void print3DivNums(int l, int h)
{
    h = sqrt(h);
    l = sqrt(l);
    vector<bool> u(sqrt(h) + 1, true), v(h - l + 1, true);

    for (int i = 2; i * i <= sqrt(h); i++)
    {
        if (u.at(i) == true)
            for (int j = i + i; j <= sqrt(h); j += i)
                u.at(j) = false;
    }

    for (int i = 2; i <= sqrt(h); i++)
    {
        if (u.at(i) == true)
            for (int j = l / i * i; j <= h; j += i)
            {
                if (j - l >= 0)
                    v.at(j - l) = false;
            }
    }

    for (int i = l; i <= h; i++)
    {
        if (v.at(i - l) == true)
            cout << i * i << "  ";
    }
}

int main(int argc, char *argv[])
{
    // printAllDivisors(105);
    print3DivNums(49, 361);
    return 0;
}