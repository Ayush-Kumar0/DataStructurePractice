#include <iostream>
#include <vector>
using namespace std;

/*
If we use brute force(deciding start point and length of square for every cell, then checking
for valid square) the time complexity is n^2 * n * n^2 = n^5
*/

// Dynamic Programming
int maxSquareMat(int m, int n, vector<vector<int>> &in)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // Filling first row and first column
    for (int i = 0; i < n; i++)
    {
        if (in[0][i] == 0)
            dp[0][i] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        if (in[i][0] == 0)
            dp[i][0] = 1;
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (in[i][j] == 0)
            {
                int x = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                dp[i][j] = x + 1;
            }
            else
                dp[i][j] = 0;
        }
    }

    int maxSize = 0;
    for (auto v : dp)
    {
        for (auto u : v)
            if (u > maxSize)
                maxSize = u;
    }
    return maxSize;
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int m, n;
        cout << "Enter the size of the square matrix: ";
        cin >> m >> n;
        vector<vector<int>> in(n, vector<int>(n, 0));
        cout << "Enter the matrix: \n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> in[i][j];
        }
        cout << "Maximum square having all zeros has side = " << maxSquareMat(m, n, in) << "\n";
    }
    return 0;
}