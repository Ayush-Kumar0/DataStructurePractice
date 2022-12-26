#include <iostream>
using namespace std;
using ll = long long int;
ll M = 1000000000 + 7;

// Recursion
ll noOfBlBTs1(int h)
{
    if (h < 1)
        return 0;
    else if (h == 1)
        return 1;
    else if (h == 2)
        return 3;

    ll x = noOfBlBTs1(h - 1) % M;
    ll y = noOfBlBTs1(h - 2) % M;
    return (x * x % M + x * y * 2 % M) % M;
}

// Memoization
ll noOfBlBTsMemoization(int h, ll *arr)
{
    if (h < 0)
        return -1;
    else if (h == 0)
    {
        *(arr + 0) = 0;
        return 0;
    }
    else if (h == 1)
    {
        *(arr + 1) = 1;
        return 1;
    }
    else if (h == 2)
    {
        *(arr + 2) = 3;
        return 3;
    }
    else
    {
        ll x, y;
        x = *(arr + h - 1);
        y = *(arr + h - 2);
        if (x == 0)
            x = noOfBlBTsMemoization(h - 1, arr) % M;
        if (y == 0)
            y = noOfBlBTsMemoization(h - 2, arr) % M;

        *(arr + h) = (x * x % M + x * y * 2 % M) % M;
        return *(arr + h);
    }
}
ll noOfBlBTs2(int h)
{
    ll arr[h + 1];
    for (ll &x : arr)
        x = 0;
    return noOfBlBTsMemoization(h, arr);
}

// Dynamic Programming
ll noOfBlBTs3(int h)
{
    if (h < 0)
        return -1;
    // ll arr[h + 1];
    ll *arr = new ll[h + 1];
    *(arr + 0) = 0;
    *(arr + 1) = 1;
    *(arr + 2) = 3;
    for (int i = 3; i <= h; i++)
    {
        ll x = *(arr + i - 1);
        ll y = *(arr + i - 2);
        *(arr + i) = (x * x % M + x * y * 2 % M) % M;
    }
    return *(arr + h);
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int n;
        cout << "Enter the height of the tree: ";
        cin >> n;
        cout << "Number of Balanced BTs are: " << noOfBlBTs3(n) << "\n";
    }

    return 0;
}