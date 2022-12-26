#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long int;

// Recursion
int lcs1(string s1, string s2)
{
    int len1 = s1.length();
    int len2 = s2.length();

    if (len1 == 0 || len2 == 0)
        return 0;

    int lcs = 0;
    if (s1[0] == s2[0])
    {
        lcs = 1 + lcs1(s1.substr(1), s2.substr(1));
    }
    else
    {
        int a = lcs1(s1.substr(1), s2);
        int b = lcs1(s1, s2.substr(1));
        // int c = lcs1(s1.substr(1), s2.substr(1));  This is the redundant call
        // lcs = max(a, max(b, c));
        lcs = max(a, b);
    }
    return lcs;
}

// Memoization
int lcsMemoization(string s1, string s2, int **output)
{
    int len1 = s1.length();
    int len2 = s2.length();
    if (output[len1][len2] != -1)
    {
        return output[len1][len2];
    }

    if (len1 == 0 || len2 == 0)
        return (output[len1][len2] = 0);

    int lcs = 0;
    if (s1[0] == s2[0])
    {
        lcs = 1 + lcsMemoization(s1.substr(1), s2.substr(1), output);
    }
    else
    {
        int a, b;
        a = lcsMemoization(s1.substr(1), s2, output);
        b = lcsMemoization(s1, s2.substr(1), output);
        lcs = max(a, b);
    }
    output[len1][len2] = lcs;
    return lcs;
}
int lcs2(string s1, string s2)
{
    int **output = new int *[s1.size() + 1];
    for (int i = 0; i <= s1.size(); i++)
    {
        *(output + i) = new int[s2.size() + 1];
        for (int j = 0; j <= s2.size(); j++)
            *(*(output + i) + j) = -1;
    }
    return lcsMemoization(s1, s2, output);
}

// Dynamic Programming
int lcs3(string s1, string s2)
{
    int len1 = s1.length();
    int len2 = s2.length();
    vector<vector<int>> output(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 1; i <= len1; i++)
    {
        string x = s1.substr(len1 - i);
        for (int j = 1; j <= len2; j++)
        {
            string y = s2.substr(len2 - j);
            int a, b;
            a = output[i - 1][j];
            b = output[i][j - 1];
            if (x[0] == y[0])
                output[i][j] = 1 + max(a, b);
            else
                output[i][j] = max(a, b);
        }
    }
    return output[len1][len2];
}

int main(int argc, char *argv[])
{
    while (true)
    {
        string s, t;
        cin >> s >> t;
        cout << "Maximum length of subsequence : " << lcs2(s, t) << "\n";
    }
    return 0;
}