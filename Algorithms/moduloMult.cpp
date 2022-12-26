#include <iostream>
using namespace std;
using ll = long long int;

/*
We can also use :
(a.b)%m = ((a%m).(b%m))%m
*/
ll moduloMultiplicaton(ll a, ll b, ll m)
{
    ll ans = 1;
    if (a == 0)
        return 0;
    if (a & 1)
    {
        ans = 2 * moduloMultiplicaton(a / 2, b, m) % m + b % m;
    }
    else
    {
        ans = 2 * moduloMultiplicaton(a / 2, b, m) % m;
    }
    return ans;
}

int main(int argc, char *argv[])
{
    cout << moduloMultiplicaton(5, 7, 12);
    return 0;
}