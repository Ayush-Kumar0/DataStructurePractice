#include <iostream>
using namespace std;

// Using Recursion
int minSteps1(int n)
{
    if (n == 1)
        return 0;

    int a, b, c;
    a = b = c = n;
    if (n % 3 == 0)
        a = minSteps1(n / 3);
    if ((n & 1) == 0)
        b = minSteps1(n / 2);
    c = minSteps1(n - 1);

    return 1 + min(a, min(b, c));
}

// Using Memoization
int minStepsMemoization(int n, int *arr)
{
    if (n == 1)
        return 0;

    int a, b, c;
    a = b = c = n;

    // Condition 1
    if (n % 3 == 0)
    {
        if (*(arr + n / 3) == -1)
            a = minStepsMemoization(n / 3, arr);
        else
            a = *(arr + n / 3);
    }
    // Condition 2
    if (n % 2 == 0)
    {
        if (*(arr + n / 2) == -1)
            b = minStepsMemoization(n / 2, arr);
        else
            b = *(arr + n / 2);
    }
    // Condition 3
    if (*(arr + n - 1) == -1)
        c = minStepsMemoization(n - 1, arr);
    else
        c = *(arr + n - 1);

    *(arr + n) = 1 + min(a, min(b, c));
    return *(arr + n);
}
int minSteps2(int n)
{
    int arr[n + 1];
    for (int &x : arr)
        x = -1;
    return minStepsMemoization(n, arr);
}

// Dynamic Programming
int minSteps3(int n)
{
    int arr[n + 1];
    *(arr + 0) = -1;
    *(arr + 1) = 0;

    for (int i = 2; i <= n; i++)
    {
        int a, b, c;
        a = b = c = i;
        if (i % 3 == 0)
            a = *(arr + i / 3);
        if (i % 2 == 0)
            b = *(arr + i / 2);
        c = *(arr + i - 1);

        *(arr + i) = 1 + min(a, min(b, c));
    }
    return *(arr + n);
}

int main(int argc, char *argv[])
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Minimum Steps to reduce to 1 are : " << minSteps3(n) << endl;
    return 0;
}