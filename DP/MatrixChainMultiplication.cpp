#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

// Recursion
ll mcm1(int n, int *arr, int start, int end)
{
    if (end - start <= 1)
        return 0;

    ll res = -1;
    for (int i = start + 1; i < end; i++)
    {
        ll a = mcm1(n, arr, start, i);
        ll b = mcm1(n, arr, i, end);

        ll x = a + b + arr[start] * arr[i] * arr[end];
        if (res == -1 || res > x)
            res = x;
    }
    return res;
}

// Dynamic Programming
ll mcm3(int n, int *arr)
{

    // vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
    // for (int i = n - 1; i >= 1; i--) // start
    // {
    //     for (int j = i + 1; j <= n; j++) // end
    //     {
    //         ll res = -1;
    //         for (int k = i; k < j; k++) // partition index
    //         {
    //             ll a = dp[i][k];
    //             ll b = dp[k + 1][j];
    //             ll x = a + b + arr[i - 1] * arr[k] * arr[j];
    //             if (res == -1 || res > x)
    //                 res = x;
    //         }
    //         dp[i][j] = res;
    //     }
    // }
    // return dp[1][n];

    vector<vector<ll>> dp(n, vector<ll>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--) // start
    {
        for (int j = i + 1; j <= n; j++) // end
        {
            ll res = -1;
            for (int k = i + 1; k < j; k++) // partition index
            {
                ll a = dp[i][k];
                ll b = dp[k][j];
                ll x = a + b + arr[i] * arr[k] * arr[j];
                if (res == -1 || res > x)
                    res = x;
            }
            if (res == -1)
                res = 0;
            dp[i][j] = res;
        }
    }
    return dp[0][n];
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int n;
        cout << "Enter the number of matrices: ";
        cin >> n;
        cout << "Enter the array: ";
        int arr[n];
        for (int i = 0; i <= n; i++)
            cin >> *(arr + i);
        cout << "Minimum multiplications are : " << mcm1(n, arr, 0, n) << "\n";
        cout << "Minimum multiplications are : " << mcm3(n, arr) << "\n";
    }
    return 0;
}