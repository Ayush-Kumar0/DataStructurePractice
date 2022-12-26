#include <iostream>
using namespace std;

// Recursion
int shortestSubsequence(string s, string t)
{
    if (s.size() == 0)
        return INT16_MAX;
    else if (t.size() == 0)
        return 1;

    // Excluding first character in shortest subsequence
    int a = shortestSubsequence(s.substr(1), t);

    // Including first character in shortest subsequence
    int pos = -1;
    for (int i = 0; i < t.size(); i++)
        if (t[i] == s[0])
        {
            pos = i;
            break;
        }
    int b = 1 + shortestSubsequence(s.substr(1), t.substr(pos + 1));

    return min(a, b);
}

int main(int argc, char *argv[])
{
    while (true)
    {
        string s, t;
        cout << "Enter two strings: ";
        cin >> s >> t;
        cout << "Length of shortest subsequence in 's' not present in 't' is: " << shortestSubsequence(s, t) << "\n";
    }
    return 0;
}