#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

// Recursion
int longestSubsequence1(int n, int *arr, int prev = -1)
{
    if (n <= 0)
        return 0;

    int a = 0, b = 0;
    if (prev < *arr)
        a = 1 + longestSubsequence1(n - 1, arr + 1, *arr);
    b = longestSubsequence1(n - 1, arr + 1);
    return max(a, b);
}

// Memoization
int longestSubsequenceMemoization(int n, int *arr, int prev, vector<int> &output)
{
    if (n <= 0)
        return 0;
    if (output[n] != -1)
    {
        return output[n];
    }

    int a = 0, b = 0;
    if (prev < *arr)
        a = 1 + longestSubsequenceMemoization(n - 1, arr + 1, *arr, output);
    b = longestSubsequenceMemoization(n - 1, arr + 1, -1, output);

    return output[n] = max(a, b);
}
int longestSubsequence2(int n, int *arr)
{
    vector<int> output(n + 1, -1);
    return longestSubsequenceMemoization(n, arr, -1, output);
}

// Dynamic Programming
int longestSubsequence3(int n, int *arr)
{
    int output[n];

    for (int i = 0; i < n; i++)
    {
        int maximum = 0;
        int x = i;
        while (--x >= 0)
        {
            if (*(arr + x) < *(arr + i))
            {
                if (output[x] > maximum)
                    maximum = output[x];
            }
        }
        output[i] = maximum + 1;
    }

    int ls = 0;
    for (int i = 0; i < n; i++)
    {
        if (output[i] > ls)
            ls = output[i];
    }
    return ls;
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
        cout << "Longest Subsequence length: " << longestSubsequence3(n, arr) << "\n";
    }
    return 0;
}