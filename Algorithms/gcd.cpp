#include <iostream>
using namespace std;

int Gcd(int a, int b)
{
    if (b == 0)
        return a;

    while (b > 0)
    {
        a = a % b;
        a = a ^ b ^ (b = a);
    }
    return a;
}

int extendedGcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

int main(int argc, char *argv[])
{
    int x1, y1;
    cout << extendedGcd(5, 2, x1, y1);
    cout << "\n"
         << x1 << "  " << y1 << "\n";
    return 0;
}