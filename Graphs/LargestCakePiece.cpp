#include <iostream>
#include <vector>
using namespace std;

// Find largest Piece of 1s
int pieceSize(vector<vector<int>> &edges, int n, vector<vector<bool>> &visited, int sr, int sc)
{
    int count = 1;
    visited[sr][sc] = true;
    // Up
    if (sr > 0 && edges[sr - 1][sc] == 1 && !visited[sr - 1][sc])
        count += pieceSize(edges, n, visited, sr - 1, sc);
    // Left
    if (sc > 0 && edges[sr][sc - 1] == 1 && !visited[sr][sc - 1])
        count += pieceSize(edges, n, visited, sr, sc - 1);
    // Bottom
    if (sr < n - 1 && edges[sr + 1][sc] == 1 && !visited[sr + 1][sc])
        count += pieceSize(edges, n, visited, sr + 1, sc);
    // Right
    if (sc < n - 1 && edges[sr][sc + 1] == 1 && !visited[sr][sc + 1])
        count += pieceSize(edges, n, visited, sr, sc + 1);
    return count;
}
int largestPiece(vector<vector<int>> &edges, int n)
{
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    int maxi = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j] && edges[i][j] == 1)
                maxi = max(maxi, pieceSize(edges, n, visited, i, j));
        }
    }
    return maxi;
}

int main(int argc, char *argv[])
{
    cout << "Enter size of the matrix: ";
    int n;
    cin >> n;
    cout << "Enter the matrix:\n";
    vector<vector<int>> adjMat(n, vector<int>(n, 0));
    for (auto &v : adjMat)
        for (auto &x : v)
            cin >> x;

    cout << "Largest piece size is : " << largestPiece(adjMat, n) << "\n";
    return 0;
}