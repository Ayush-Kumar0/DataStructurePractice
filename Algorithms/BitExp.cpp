#include <iostream>
using namespace std;
using ll = long long int;

ll binExp(ll a, ll n)
{
    if (n == 0)
        return 1;
    else
    {
        if (n % 2 == 0)
            return (binExp(a, n / 2) * binExp(a, n / 2));
        else
            return (binExp(a, n / 2) * binExp(a, n / 2) * a);
    }
}

ll binExp2(ll a, ll n)
{
    ll ans = 1;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a;
        a = a * a;
        n = n >> 1;
    }
    return ans;
}

int main(int argc, char *argv[])
{
    cout << binExp2(2, 62);
    return 0;
}