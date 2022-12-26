#include <iostream>
using namespace std;
using ll = long long int;

ll moduloExp(ll a, ll n, ll m)
{
    ll result = 1;
    while (n > 0)
    {
        if (n & 1)
            result = (result % m) * (a % m) % m;
        n >>= 1;
        a = (a % m) * (a % m) % m;
    }
    return result;
}

int main(int argc, char *argv[])
{
    cout << moduloExp(29495734985793, 1699994776565056491, 11);
    return 0;
}