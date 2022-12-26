#include <iostream>
#include <vector>
using namespace std;

// Count number of cycles which are Triangles
int countThreeCycles(vector<vector<int>> &edges, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (edges[i][j] == 0)
                continue;
            for (int k = 0; k < n; k++)
            {
                if (edges[j][k] == 0 || k == i)
                    continue;
                count++;
            }
        }
    }
    return count / 6;
}

int main(int argc, char *argv[])
{
    cout << "Enter number of vertices: ";
    int n;
    cin >> n;
    vector<vector<int>> adjMat(n, vector<int>(n, 0));

    int e;
    cout << "Enter number of edges: ";
    cin >> e;
    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        adjMat[a][b] = 1;
        adjMat[b][a] = 1;
    }

    cout << "The number of 3 Cycles are: " << countThreeCycles(adjMat, n) << "\n";

    return 0;
}