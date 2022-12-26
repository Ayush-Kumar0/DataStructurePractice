#include <iostream>
using namespace std;
using ll = long long int;

// Using Recursion
int fib1(int n)
{
    if (n <= 1)
        return n;
    return fib1(n - 1) + fib1(n - 2);
}

// Memoization
int fibo(int n, int *arr)
{
    if (n == 0 || n == 1)
    {
        *arr = n;
        return n;
    }

    if (*(arr + n) == -1)
    {
        *(arr + n) = fibo(n - 1, arr) + fibo(n - 2, arr);
    }
    return *(arr + n);
}
int fib2(int n)
{
    int arr[n + 1];
    for (int &x : arr)
        x = -1;
    return fibo(n, arr);
}

// Dynamic Programming
int fib3(int n)
{
    if (n <= 1)
        return n;

    int arr[n + 1];
    *(arr + 0) = 0;
    *(arr + 1) = 1;

    for (int i = 2; i <= n; i++)
    {
        *(arr + i) = *(arr + i - 1) + *(arr + i - 2);
    }
    return *(arr + n);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
        cout << fib2(i) << "\n";

    return 0;
}