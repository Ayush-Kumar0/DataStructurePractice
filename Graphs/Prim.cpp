#include <iostream>
#include <vector>
using namespace std;

int getMinWeightIndex(int *weights, bool *visited, int v)
{
    int mini = INT32_MAX;
    int ind = -1;
    for (int i = 0; i < v; i++)
        if (mini > weights[i] && !visited[i])
        {
            mini = weights[i];
            ind = i;
        }
    return ind;
}

// Using Prims algorithm, create a MST
int creatMST(vector<vector<int>> &edges, int v, vector<pair<pair<int, int>, int>> &out)
{

    // Create necessary array and variables
    bool visited[v];
    int weights[v];
    int parents[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
        weights[i] = INT32_MAX;
        parents[i] = -1;
    }
    weights[0] = 0;

    // Use Prims algorithm
    for (int i = 0; i < v; i++)
    {
        int ind = getMinWeightIndex(weights, visited, v);
        visited[ind] = true;
        for (int j = 0; j < v; j++)
        {
            if (visited[j] || edges[ind][j] == -1)
                continue;
            int wt = edges[ind][j];
            if (wt < weights[j])
            {
                weights[j] = wt;
                parents[j] = ind;
            }
        }
    }

    for (int i = 1; i < v; i++)
    {
        pair<pair<int, int>, int> p = {{i, parents[i]}, weights[i]};
        out.push_back(p);
    }
    return v - 1;
}

int main(int argc, char *argv[])
{
    cout << "Enter number of vertices: ";
    int v;
    cin >> v;
    cout << "Enter number of edges: ";
    int e;
    cin >> e;
    vector<vector<int>> adjMat(v, vector<int>(v, -1));
    cout << "Enter the edges with their weights:\n";
    for (int i = 0; i < e; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adjMat[x][y] = w;
        adjMat[y][x] = w;
    }

    vector<pair<pair<int, int>, int>> mst(0);
    int mstSize = creatMST(adjMat, v, mst);
    cout << "\nThe edges of MST are:\n";
    for (int i = 0; i < mstSize; i++)
    {
        pair<pair<int, int>, int> p = mst[i];
        cout << p.first.first << " " << p.first.second << " " << p.second << "\n";
    }

    return 0;
}