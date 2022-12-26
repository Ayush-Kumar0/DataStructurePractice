#include <iostream>
#include <vector>
using namespace std;

bool dfs(vector<vector<char>> &edges, vector<vector<bool>> &visited, int &m, int &n, int sr, int sc, int pr, int pc)
{
    bool c = false;

    visited[sr][sc] = true;
    if (sr > 0 && !(sr - 1 == pr && sc == pc))
    {
        if (edges[sr - 1][sc] == edges[sr][sc])
        {
            if (visited[sr - 1][sc])
                return true;
            else
                c = c || dfs(edges, visited, m, n, sr - 1, sc, sr, sc);
        }
    }
    if (sr < m - 1 && !(sr + 1 == pr && sc == pc))
    {
        if (edges[sr + 1][sc] == edges[sr][sc])
        {
            if (visited[sr + 1][sc])
                return true;
            else
                c = c || dfs(edges, visited, m, n, sr + 1, sc, sr, sc);
        }
    }
    if (sc > 0 && !(sr == pr && sc - 1 == pc))
    {
        if (edges[sr][sc - 1] == edges[sr][sc])
        {
            if (visited[sr][sc - 1])
                return true;
            else
                c = c || dfs(edges, visited, m, n, sr, sc - 1, sr, sc);
        }
    }
    if (sc < n - 1 && !(sr == pr && sc + 1 == pc))
    {
        if (edges[sr][sc + 1] == edges[sr][sc])
        {
            if (visited[sr][sc + 1])
                return true;
            else
                c = c || dfs(edges, visited, m, n, sr, sc + 1, sr, sc);
        }
    }

    return c;
}
bool isCyclePresent(vector<vector<char>> &edges)
{
    int m = edges.size();
    int n = edges[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    bool c = false;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j])
            {
                c = c || dfs(edges, visited, m, n, i, j, -1, -1);
            }
        }
    }
    return c;
}

int main(int argc, char *argv[])
{
    cout << "Enter number of rows and columns: ";
    int m, n;
    cin >> m >> n;
    vector<vector<char>> adjMat(m, vector<char>(n, 0));
    cout << "Enter matrix elements:\n";
    for (auto &v : adjMat)
    {
        for (auto &x : v)
            cin >> x;
    }

    cout << boolalpha << isCyclePresent(adjMat) << "\n";

    return 0;
}