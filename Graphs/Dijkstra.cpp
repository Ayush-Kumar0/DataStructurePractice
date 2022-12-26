#include <iostream>
#include <vector>
using namespace std;

int getMinWeightIndex(int *weights, bool *visited, int v)
{
    int mini = INT32_MAX;
    int ind = -1;
    for (int i = 0; i < v; i++)
        if (!visited[i] && mini > weights[i])
        {
            mini = weights[i];
            ind = i;
        }
    return ind;
}

// Min Weight Path using Dijkstra's algorithm
void printMinWeightPath(vector<vector<int>> &edges, int v, int src)
{
    // Create necessary arrays and variables
    bool visited[v];
    int pathWeight[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
        pathWeight[i] = INT32_MAX;
    }
    pathWeight[src] = 0;

    // Use Dijkstra's Algorithm
    for (int i = 0; i < v; i++)
    {
        int ind = getMinWeightIndex(pathWeight, visited, v);
        visited[ind] = true;
        for (int j = 0; j < v; j++)
        {
            if (visited[j] || edges[ind][j] == -1)
                continue;
            int dist = pathWeight[ind] + edges[ind][j];
            if (dist < pathWeight[j])
                pathWeight[j] = dist;
        }
    }

    // Printing minimum path weights from its source
    for (int i = 0; i < v; i++)
        cout << i << " " << pathWeight[i] << "\n";
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

    int src;
    cout << "Enter the source : ";
    cin >> src;
    printMinWeightPath(adjMat, v, src);

    return 0;
}