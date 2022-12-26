#include <iostream>
#include <vector>
using namespace std;

// Recursion
int editDistance1(string s, string t)
{
    int len1 = s.length();
    int len2 = t.length();
    if (len1 == 0)
        return len2;
    else if (len2 == 0)
        return len1;
    else
    {
        if (s[0] == t[0])
            return editDistance1(s.substr(1), t.substr(1));
        else
        {
            // Insertion
            int a = 1 + editDistance1(s, t.substr(1));
            // Deletion
            int b = 1 + editDistance1(s.substr(1), t);
            // Replace
            int c = 1 + editDistance1(s.substr(1), t.substr(1));

            return min(a, min(b, c));
        }
    }
}

// Memoization
int editDistanceMemoization(string s, string t, vector<vector<int>> &mem)
{
    int len1 = s.length();
    int len2 = t.length();
    if (len1 == 0)
    {
        mem[0][len2] = len2;
        return len2;
    }
    else if (len2 == 0)
    {
        mem[len1][0] = len1;
        return len1;
    }
    else
    {
        if (mem[len1][len2] != -1)
        {
            return mem[len1][len2];
        }

        int ans = 0;
        if (s[0] == t[0])
        {
            ans = editDistanceMemoization(s.substr(1), t.substr(1), mem);
        }
        else
        {
            int a, b, c;
            // Insertion
            a = 1 + editDistanceMemoization(s, t.substr(1), mem);
            // Deletion
            b = 1 + editDistanceMemoization(s.substr(1), t, mem);
            // Replacing
            c = 1 + editDistanceMemoization(s.substr(1), t.substr(1), mem);
            ans = min(a, min(b, c));
        }
        mem[len1][len2] = ans;
        return ans;
    }
}
int editDistance2(string s, string t)
{
    vector<vector<int>> mem(s.length() + 1, vector<int>(t.length() + 1, -1));
    return editDistanceMemoization(s, t, mem);
}

// Dynamic Programming
int editDistance3(string s, string t)
{
    int len1 = s.length();
    int len2 = t.length();
    vector<vector<int>> mem(len1 + 1, vector<int>(len2 + 1, 0));
    // Filling first row
    for (int i = 0; i <= len2; i++)
        mem[0][i] = i;
    // Filling first column
    for (int i = 0; i <= len1; i++)
        mem[i][0] = i;
    // Filling other cells
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (s[len1 - i] == t[len2 - j])
                mem[i][j] = mem[i - 1][j - 1];
            else
            {
                int a = mem[i - 1][j];
                int b = mem[i][j - 1];
                int c = mem[i - 1][j - 1];
                mem[i][j] = 1 + min(a, min(b, c));
            }
        }
    }
    return mem[len1][len2];
}
int main(int argc, char *argv[])
{
    while (true)
    {
        string s, t;
        cout << "Enter two strings : ";
        cin >> s >> t;
        cout << "The edit distance of two words is: " << editDistance3(s, t) << "\n";
    }
    return 0;
}