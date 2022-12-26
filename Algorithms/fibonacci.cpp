#include <iostream>
using namespace std;

int fibonacci(int n)
{
    int a = 0, b = 1, c;
    for (int i = 1; i <= n; i++)
    {
        c = a + b;
        a = b + c - (b = c);
    }
    return a;
}

int fibonacciRec(int n, int &next)
{
    if (n == 0)
    {
        next = 1;
        return 0;
    }

    int nextt;
    int curr = fibonacciRec(n / 2, nextt);
    int a = curr * (2 * nextt - curr);
    int b = nextt * nextt + curr * curr;
    if (n % 2 == 0) // even
    {
        next = b;
        return a;
    }
    else // odd
    {
        next = a + b;
        return b;
    }
}
int fib(int n)
{
    int next;
    return fibonacciRec(n, next);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 11; i++)
    {
        cout << fib(i) << "  ";
    }
    cout << endl;
    return 0;
}