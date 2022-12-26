#include <iostream>
using namespace std;
using ll = long long int;

// Recursion
ll staircase1(int n)
{
    if (n < 1)
        return -1;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (n == 3)
        return 4;

    ll steps = 0;
    steps += staircase1(n - 3) + staircase1(n - 2) + staircase1(n - 1);

    return steps;
}

// Memoization
ll staircaseMemoization(int n, ll *arr)
{
    if (n < 1)
        return -1;
    if (n == 1)
    {
        *(arr + 1) = 1;
        return 1;
    }
    if (n == 2)
    {
        *(arr + 2) = 2;
        return 2;
    }
    if (n == 3)
    {
        *(arr + 3) = 4;
        return 4;
    }

    ll steps = 0;

    if (*(arr + n - 3) != -1)
        steps += *(arr + n - 3);
    else
        steps += staircaseMemoization(n - 3, arr);
    if (*(arr + n - 2) != -1)
        steps += *(arr + n - 2);
    else
        steps += staircaseMemoization(n - 2, arr);
    if (*(arr + n - 1) != -1)
        steps += *(arr + n - 1);
    else
        steps += staircaseMemoization(n - 1, arr);

    return steps;
}
ll staircase2(int n)
{
    ll arr[n + 1];
    for (ll &x : arr)
        x = -1;
    return staircaseMemoization(n, arr);
}

// Dynamic Programming
ll staircase3(int n)
{
    if (n < 1)
        return -1;
    ll arr[n + 1];
    *(arr + 0) = -1;
    *(arr + 1) = 1;
    *(arr + 2) = 2;
    *(arr + 3) = 4;

    for (int i = 4; i <= n; i++)
    {
        *(arr + i) = *(arr + i - 3) + *(arr + i - 2) + *(arr + i - 1);
    }
    return *(arr + n);
}

int main(int argc, char *argv[])
{
    int n;
    cout << "Enter number of steps: ";
    cin >> n;
    cout << "Number of ways are: " << staircase3(n) << "\n";

    return 0;
}