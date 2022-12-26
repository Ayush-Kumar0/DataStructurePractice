#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

// Recursion
ll lootHouses1Helper(int n, int *arr, bool in)
{
    if (n <= 0)
        return 0;

    ll include = 0, exclude = 0;

    exclude = lootHouses1Helper(n - 1, arr + 1, false);

    if (in == true)
        return exclude;

    ll a = *arr + lootHouses1Helper(n - 1, arr + 1, true);
    ll b = lootHouses1Helper(n - 1, arr + 1, true);
    include = max(a, b);

    return max(include, exclude);
}
ll lootHouses1(int n, int *arr)
{
    return max(lootHouses1Helper(n, arr, true), lootHouses1Helper(n, arr, false));
}

// Memoization
ll lootHousesMemoization(int n, int *arr, bool in, vector<vector<int>> &output)
{
    if (n <= 0)
        return 0;
    int i = (in) ? 1 : 0;

    if (output[i][n] != -1)
        return output[i][n];

    ll include = 0, exclude = 0;

    exclude = lootHousesMemoization(n - 1, arr + 1, false, output);
    if (in == true)
        return exclude;

    ll a = *arr + lootHousesMemoization(n - 1, arr + 1, true, output);
    ll b = lootHousesMemoization(n - 1, arr + 1, true, output);
    include = max(a, b);

    return output[i][n] = max(include, exclude);
}
ll lootHouses2(int n, int *arr)
{
    vector<vector<int>> output(2, vector<int>(n + 1, -1));
    return max(lootHousesMemoization(n, arr, true, output), lootHousesMemoization(n, arr, false, output));
}

// Dynamic Programming
ll lootHouses3(int n, int *arr)
{
    int output[n + 1];
    output[0] = 0;
    output[1] = *arr;
    output[2] = max(*(arr), *(arr + 1));
    for (int i = 3; i <= n; i++)
    {
        output[i] = max(output[i - 1], *(arr + i - 1) + output[i - 2]);
    }
    return output[n];
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int n;
        cout << "Enter the size of the array: ";
        cin >> n;
        cout << "Enter the array: ";
        int arr[n];
        for (int i = 0; i < n; i++)
            cin >> *(arr + i);
        cout << "Maximum loot: " << lootHouses3(n, arr) << "\n";
    }
    return 0;
}