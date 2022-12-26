#include <iostream>
using namespace std;

// Recursion
// true means Beerus and false means Whis
bool coinTower1(int n, int x, int y)
{
    if (n == 1 || n == x || n == y)
        return true;

    bool a, b, c;
    a = b = c = true;
    a = coinTower1(n - 1, x, y);
    if (n > x)
        b = coinTower1(n - x, x, y);
    if (n > y)
        c = coinTower1(n - y, x, y);

    if ((a && b && c) == false)
        return true;
    else
        return false;
}

// Dynamic Programming
bool coinTower3(int n, int x, int y)
{
    bool dp[n + 1];
    for (int i = 1; i <= n; i++)
    {
        if (i == 1 || i == x || i == y)
        {
            dp[i] = true;
            continue;
        }
        bool a, b, c;
        a = b = c = true;
        a = dp[i - 1];
        if (i > x)
            b = dp[i - x];
        if (i > y)
            c = dp[i - y];

        dp[i] = !(a && b && c);
    }
    return *(dp + n);
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int n, x, y;
        cout << "Enter N, X, Y : ";
        cin >> n >> x >> y;
        if (coinTower1(n, x, y))
            cout << "Beerus\n";
        else
            cout << "Whis\n";
        if (coinTower3(n, x, y))
            cout << "Beerus\n";
        else
            cout << "Whis\n";
    }
    return 0;
}