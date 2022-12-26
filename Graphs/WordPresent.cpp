#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool checkWord(vector<vector<char>> &mat, int r, int c, string s)
{
    int ind = 0;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (mat[i][j] == s[ind])
            {
                queue<pair<int, int>> q;
                q.push({i, j});

                ind++;
                while (!q.empty())
                {
                    if (ind == s.length())
                        return true;
                    char ch = s[ind];

                    pair<int, int> p = q.front();
                    q.pop();
                    int a = p.first;
                    int b = p.second;

                    if (a > 0 && mat[a - 1][b] == ch)
                        q.push({a - 1, b});
                    if (b > 0 && mat[a][b - 1] == ch)
                        q.push({a, b - 1});
                    if (a > 0 && b > 0 && mat[a - 1][b - 1] == ch)
                        q.push({a - 1, b - 1});
                    if (a < r - 1 && mat[a + 1][b] == ch)
                        q.push({a + 1, b});
                    if (b < c - 1 && mat[a][b + 1] == ch)
                        q.push({a, b + 1});
                    if (a < r - 1 && b < c - 1 && mat[a + 1][b + 1] == ch)
                        q.push({a + 1, b + 1});
                    if (a > 0 && b < c - 1 && mat[a - 1][b + 1] == ch)
                        q.push({a - 1, b + 1});
                    if (b > 0 && a < r - 1 && mat[a + 1][b - 1] == ch)
                        q.push({a + 1, b - 1});

                    ind++;
                }
            }
        }
    }
    if (ind == s.length())
        return true;
    return false;
}

int main(int argc, char *argv[])
{
    int r, c;
    cout << "Enter number of rows and columns: ";
    cin >> r >> c;
    vector<vector<char>> mat(r, vector<char>(c, 0));
    cout << "Enter the matrix:\n";
    for (auto &v : mat)
        for (auto &x : v)
            cin >> x;

    cout << "Enter word to check : ";
    string s;
    cin >> s;
    cout << checkWord(mat, r, c, s) << "\n";

    return 0;
}