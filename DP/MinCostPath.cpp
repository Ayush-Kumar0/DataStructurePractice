#include <iostream>
using namespace std;
using ll = long long int;

ll minCost1(int M, int N, int *arr, int i = 0, int j = 0)
{
    if (i == M - 1 && j == N - 1)
        return *(arr + M * N - 1);

    ll a, b, c;
    a = b = c = INT32_MAX;
    if (i != M - 1)
        a = minCost1(M, N, arr, i + 1, j);
    if (j != N - 1)
        b = minCost1(M, N, arr, i, j + 1);
    if (i != M - 1 && j != N - 1)
        c = minCost1(M, N, arr, i + 1, j + 1);

    ll minimum = min(a, min(b, c));
    return *(arr + N * i + j) + minimum;
}

// Memoization
ll minCostMemoization(int M, int N, int *arr, pair<ll, bool> *store, int i = 0, int j = 0)
{
    if (i == M - 1 && j == N - 1)
    {
        (store + N * i + j)->second = true;
        return ((store + N * i + j)->first = *(arr + N * i + j));
    }
    ll a, b, c;
    bool x, y, z;
    x = y = z = true;
    pair<ll, bool> *storeEle = store + N * i + j;

    if (i != M - 1)
    {
        if ((storeEle + N)->second == false)
        {
            a = minCostMemoization(M, N, arr, store, i + 1, j);
        }
        else
            a = (storeEle + N)->first;
    }
    else
    {
        x = false;
    }

    if (j != N - 1)
    {
        if ((storeEle + 1)->second == false)
        {
            b = minCostMemoization(M, N, arr, store, i, j + 1);
        }
        else
            b = (storeEle + 1)->first;
    }
    else
    {
        y = false;
    }

    if (i != M - 1 && j != N - 1)
    {
        if ((storeEle + N + 1)->second == false)
        {
            c = minCostMemoization(M, N, arr, store, i + 1, j + 1);
        }
        else
            c = (storeEle + N + 1)->first;
    }
    else
    {
        z = false;
    }

    if (x == true && y == true && z == true)
    {
        storeEle->first = min(a, min(b, c));
    }
    else if (x == true && y == true)
    {
        storeEle->first = min(a, b);
    }
    else if (y == true && z == true)
    {
        storeEle->first = min(b, c);
    }
    else if (z == true && x == true)
    {
        storeEle->first = min(c, a);
    }
    else if (x == true)
    {
        storeEle->first = a;
    }
    else if (y == true)
    {
        storeEle->first = b;
    }
    else if (z == true)
    {
        storeEle->first = c;
    }
    storeEle->second = true;

    return (storeEle->first = *(arr + N * i + j) + storeEle->first);
}
ll minCost2(int M, int N, int *arr)
{
    pair<ll, bool> store[M][N];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            store[i][j] = make_pair(0, false);

    return minCostMemoization(M, N, arr, *store);
}

// Dynamic Programming
ll minCost3(int M, int N, int *arr)
{
    // Fill last row
    for (int i = N - 2; i >= 0; i--)
        *(arr + N * (M - 1) + i) += *(arr + N * (M - 1) + i + 1);
    // Fill last column
    for (int i = M - 2; i >= 0; i--)
        *(arr + N * i + N - 1) += *(arr + N * (i + 1) + N - 1);

    // Filling rows from bottom-right to top-left
    for (int i = M - 2; i >= 0; i--)
    {
        for (int j = N - 2; j >= 0; j--)
        {
            ll a = *(arr + N * (i + 1) + j);
            ll b = *(arr + N * i + j + 1);
            ll c = *(arr + N * (i + 1) + j + 1);
            *(arr + N * i + j) += min(a, min(b, c));
        }
    }

    ll sum = *arr;
    return sum;
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int M, N;
        cin >> M >> N;
        int arr[M][N];
        for (int i = 0; i < M * N; i++)
            cin >> *(*(arr + i / N) + i % N);
        cout << "Minimum Cost is : " << minCost3(M, N, *arr) << "\n";
    }

    return 0;
}