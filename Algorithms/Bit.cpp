#include <iostream>
#include <vector>
using namespace std;

int countSetBits(int n)
{
    int count = 0;
    while (n > 0)
    {
        n = n & (n - 1);
        count++;
    }
    return count;
}

void kthBitSetBit(int n, int k)
{
    if ((n & (1 << (k - 1))) != 0) // OR    ((n>>(k-1))&1)!=0
        cout << "YES\n";
    else
        cout << "NO\n";
}

inline bool powerOfTwo(int n)
{
    return ((n > 0) && ((n & (n - 1)) == 0));
}

void oddTimesNum(int *arr, int len)
{
    int num;
    for (int i = 0; i < len; i++)
        num = num ^ (*(arr + i));
    cout << num;
}

void oddTimesTwoNum(int *arr, int len)
{
    int a, b;
    a = b = 0;
    vector<int> x, y;

    int p = 0;
    for (int i = 0; i < len; i++)
        p ^= *(arr + i);

    int q = p & ~(p - 1); // Gives last set bit

    // Grouping according to last set bit
    for (int i = 0; i < len; i++)
    {
        int t = *(arr + i);
        if ((t & q) == 0)
            x.push_back(t);
        else
            y.push_back(t);
    }

    for (auto t : x)
        a ^= t;
    for (auto t : y)
        b ^= t;

    cout << a << "  " << b << "\n";
}

int binToGray(int n)
{
    return (n ^ (n >> 1));
}
int grayToBin(int n)
{
    int res = 0;
    while (n > 0)
    {
        res = res ^ n;
        n >> 1;
    }
    return res;
}

int main(int argc, char *argv[])
{
    int arr[] = {1, 1, 17, 5, 5, 90};
    oddTimesTwoNum(arr, sizeof(arr) / sizeof(int));
    return 0;
}