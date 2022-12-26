#include <iostream>
#include <vector>
using namespace std;

void primeFactors(int n)
{
    if (n < 1)
        return;
    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            n = n / i;
            cout << i << "  ";
        }
    }
    if (n > 1)
        cout << n << "\n";
}

void smallestPrimeFactors(int n)
{
    vector<int> sp(n + 1, 0);

    for (int i = 2; i * i <= n; i++)
    {
        if (sp.at(i) == 0)
            for (int j = i; j <= n; j += i)
                if (sp.at(j) == 0)
                    sp.at(j) = i;
    }

    for (int i = 0; i <= n; i++)
        if (sp.at(i) == 0)
            sp.at(i) = i;

    for (int i = 1; i <= n; i++)
    {
        cout << sp.at(i) << "  ";
    }
}

void primeFactQueries()
{
    int t;
    cin >> t;
    int arr[t];
    int max = INT32_MIN;
    for (auto &x : arr)
    {
        cin >> x;
        if (max < x)
            max = x;
    }

    vector<int> sp(max + 1, 0);
    for (int i = 2; i * i <= max; i++)
    {
        if (sp.at(i) == 0)
            for (int j = i; j <= max; j += i)
                if (sp.at(j) == 0)
                    sp.at(j) = i;
    }
    for (int i = 1; i <= max; i++)
        if (sp.at(i) == 0)
            sp.at(i) = i;

    for (auto x : arr)
    {
        while (x > 1)
        {
            cout << sp.at(x) << " ";
            x = x / sp.at(x);
        }
        cout << "\n";
    }
}

int main(int argc, char *argv[])
{
    // primeFactors(130);
    // smallestPrimeFactors(15);
    primeFactQueries();
    return 0;
}