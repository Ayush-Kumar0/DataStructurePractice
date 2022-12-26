#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

// Recursion
ll knapsack1(int n, int *W, int *V, int maxW)
{
    if (n == 0)
        return 0;

    ll maxValue = 0;
    ll a = 0, b = 0;
    a = knapsack1(n - 1, W + 1, V + 1, maxW);
    if (*W <= maxW)
        b = *V + knapsack1(n - 1, W + 1, V + 1, maxW - *W);
    maxValue = max(a, b);
    return maxValue;
}

// Memoization
ll knapsackMemoization(int n, int *W, int *V, int maxW, ll *output)
{
    if (n == 0)
        return (*(output + maxW) = 0);

    ll maxValue = 0;
    ll a = 0, b = 0;

    if (*(output + maxW) == -1)
        a = knapsackMemoization(n - 1, W + 1, V + 1, maxW, output);
    else
        a = *(output + maxW);
    if (*W <= maxW)
    {
        if (*(output + maxW - *W) == -1)
            b = *V + knapsackMemoization(n - 1, W + 1, V + 1, maxW - *W, output);
        else
            b = *V + *(output + maxW - *W);
    }
    maxValue = max(a, b);
    *(output + maxW) = maxValue;
    return maxValue;
}
ll knapsack2(int n, int *W, int *V, int maxW)
{
    ll output[maxW + 1];
    for (ll &x : output)
        x = -1;
    return knapsackMemoization(n, W, V, maxW, output);
}

// Dynamic Programming
ll knapsack3(int n, int *W, int *V, int maxW)
{
    vector<vector<int>> output(n + 1, vector<int>(maxW + 1, 0));
    for (int i = 1; i <= n; i++) // Rows are indices of array of items
    {
        for (int j = 1; j <= maxW; j++) // Columns indices are maximum carrying weight
        {
            // In case of excluding current item
            int a = output[i - 1][j];
            // In case of including current item
            int b = 0;
            if (j - *(W + i - 1) >= 0)
                b = *(V + i - 1) + output[i - 1][j - *(W + i - 1)];

            output[i][j] = max(a, b);

            // cout << output[i][j] << "  ";
        }
        // cout << endl;
    }
    return output[n][maxW];
}

// More optimised Dynamic Programming
ll knapsack4(int n, int *W, int *V, int maxW)
{
    vector<int> output(maxW + 1, 0);
    for (int i = 1; i <= n; i++) // Rows are indices of array of items
    {
        for (int j = maxW; j >= 1; j--) // Columns indices are maximum carrying weight
        {
            // In case of excluding current item
            int a = output[j];
            // In case of including current item
            int b = 0;
            if (j - *(W + i - 1) >= 0)
                b = *(V + i - 1) + output[j - *(W + i - 1)];

            output[j] = max(a, b);
        }
    }
    return output[maxW];
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int size;
        cout << "Enter the size: ";
        cin >> size;
        cout << "Enter item Weights: ";
        int W[size];
        for (int &x : W)
            cin >> x;
        cout << "Enter item Values: ";
        int V[size];
        for (int &x : V)
            cin >> x;
        cout << "Enter total weight: ";
        int maxW = 0;
        cin >> maxW;
        cout << "Maximum item value is: " << knapsack4(size, W, V, maxW) << "\n\n";
    }
    return 0;
}