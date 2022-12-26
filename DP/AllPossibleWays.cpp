#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Recursion
int allPossibleWays1Helper(int n, int b, int prevNum)
{
    if (n == 0)
        return 1;

    int count = 0;
    for (int i = prevNum + 1; (int)pow(i, b) <= n; i++)
    {
        int res = allPossibleWays1Helper(n - (int)pow(i, b), b, i);
        count += res;
    }
    return count;
}
int allPossibleWays1(int n, int b)
{
    return allPossibleWays1Helper(n, b, 0);
}

// Memoization
int allPossibleWays2Helper(int n, int b, int prevNum, vector<vector<int>> &output)
{
    if (n == 0)
    {
        return output[prevNum][n] = 1;
    }

    // Return saved data
    if (output[prevNum][n] != -1)
    {
        return output[prevNum][n];
    }

    int count = 0;
    for (int i = prevNum + 1; (int)pow(i, b) <= n; i++)
    {
        int res = allPossibleWays2Helper(n - (int)pow(i, b), b, i, output);
        count += res;
    }
    return output[prevNum][n] = count;
}
int allPossibleWays2(int n, int b)
{
    vector<vector<int>> output(ceil(pow(n, 1.0 / b)) + 1, vector<int>(n + 1, -1));
    return allPossibleWays2Helper(n, b, 0, output);
}

// Dynamic Programming
int allPossibleWays3(int n, int b)
{
}

int main(int argc, char *argv[])
{
    while (true)
    {
        int n;
        cout << "Enter a number and a power: ";
        cin >> n;
        int b;
        cin >> b;
        cout << "All Possible ways are: " << allPossibleWays1(n, b) << "\n";
    }
    return 0;
}