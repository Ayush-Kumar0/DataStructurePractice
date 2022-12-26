#include <iostream>
#include <vector>
using namespace std;

// Recursion
int coinChange1(int n, int *arr, int ind, int coin)
{
    if (coin < 0)
        return 0;
    else if (coin == 0)
        return 1;
    else if (ind >= n)
        return 0;

    int res = 0;
    // Exclude
    int a = coinChange1(n, arr, ind + 1, coin);
    // Include
    int b = coinChange1(n, arr, ind, coin - *(arr + ind));

    res = a + b;
    return res;
}

// Memoization
int coinChange2Helper(int n, int *arr, int coin, int ind, vector<vector<int>> &dp)
{
    if (coin < 0)
        return 0;
    else if (coin == 0)
        return dp[ind][coin] = 1;
    else if (ind < 0)
        return 0;

    if (dp[ind][coin] != -1)
        return dp[ind][coin];

    int a = coinChange2Helper(n, arr, coin, ind - 1, dp);
    int b = coinChange2Helper(n, arr, coin - *(arr + ind), ind, dp);

    return dp[ind][coin] = a + b;
}
int coinChange2(int n, int *arr, int coin)
{
    vector<vector<int>> dp(n, vector<int>(coin + 1, -1));
    return coinChange2Helper(n, arr, coin, n - 1, dp);
}

// Dynamic Programming
int coinChange3(int n, int *arr, int coin)
{
    vector<vector<int>> dp(n + 1, vector<int>(coin + 1, 0));
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 1; j <= coin; j++)
        {
            dp[i][j] = dp[i + 1][j];
            if (j >= *(arr + i))
                dp[i][j] += dp[i][j - *(arr + i)];
        }
    }
    return dp[0][coin];
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int n;
        cout << "Enter the size of the array: ";
        cin >> n;
        cout << "Enter the array of Denominations: ";
        int arr[n];
        int coin = 0;
        for (int i = 0; i < n; i++)
            cin >> *(arr + i);
        cout << "Enter the money: ";
        cin >> coin;
        cout << "Ways to make coin change are: " << coinChange3(n, arr, coin) << "\n";
    }
    return 0;
}