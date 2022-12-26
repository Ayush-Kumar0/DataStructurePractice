#include <iostream>
#include <cmath>
using namespace std;
using ll = long long int;

// Recursion
ll minimumSums1(ll n)
{
    if (n < 0)
        return -1;
    else if (n == 0)
        return 0;

    ll rootN = (ll)sqrt(n);
    if (rootN * rootN == n)
        return 1;

    return 1 + minimumSums1(n - rootN * rootN);
}

// Memoization
ll minimumSumsMemoization(ll n, ll *arr)
{
    ll rootN = (ll)sqrt(n);
    if (rootN * rootN == n)
    {
        *(arr + n) = 1;
        return 1;
    }

    ll count = 1 + *(arr + n);
    if (count == 1)
    {
        count = 1 + minimumSumsMemoization(n - rootN * rootN, arr);
        *(arr + n) = count;
    }

    return count;
}
ll minimumSums2(ll n)
{
    if (n < 0)
        return -1;
    else if (n == 0)
        return 0;

    ll arr[n + 1];
    for (ll &x : arr)
        x = 0;

    return minimumSumsMemoization(n, arr);
}

// Dynamic Programming
ll minimumSums3(ll n)
{
    if (n < 0)
        return -1;

    ll arr[n + 1];
    *(arr + 0) = 0;

    for (ll i = 1; i <= n; i++)
    {
        ll rootI = (ll)sqrt(i);
        if (rootI * rootI == i)
            *(arr + i) = 1;
        else
            *(arr + i) = 1 + *(arr + i - rootI * rootI);
    }

    return *(arr + n);
}

int main(int argc, char *argv[])
{
    ll n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Minimum numbers required are: " << minimumSums3(n) << endl;

    return 0;
}