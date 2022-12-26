#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Print Connected graph
void printBFSConnected(vector<vector<int>> &edges, int n, int startV, vector<bool> &visited)
{
    queue<int> q;
    q.push(startV);
    cout << startV << " ";
    visited[startV] = true;
    while (!q.empty())
    {
        int vert = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            if (edges[vert][i] == 1 && visited[i] == false)
            {
                cout << i << " ";
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

// Print Disconnected Graph
void printBFSDisconnected(vector<vector<int>> &edges, int n)
{
    cout << "Graph BFS:\n";
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            printBFSConnected(edges, n, i, visited);
            cout << "\n";
        }
}

// Find if there exists a path from one vertex to another
bool hasPath(vector<vector<int>> &edges, int n, int a, int b)
{
    vector<bool> visited(n, false);
    visited[a] = true;
    queue<int> q;
    q.push(a);

    bool has = false;
    while (!q.empty())
    {
        int vert = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && edges[vert][i] == 1)
            {
                q.push(i);
                visited[i] = true;
                if (i == b)
                {
                    has = true;
                    break;
                }
            }
        }
    }
    return has;
}

// Print the path from one vertex to another
bool printPath(vector<vector<int>> &edges, int n, int a, int b)
{
    vector<bool> visited(n, false);
    queue<int> q;
    unordered_map<int, int> m;
    q.push(a);
    visited[a] = true;

    bool has = false;
    while (!q.empty())
    {
        int vert = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && edges[vert][i] == 1)
            {
                visited[i] = true;
                q.push(i);
                m.insert({i, vert});
                if (i == b)
                    break;
            }
        }
    }

    if (m.count(b))
    {
        while (b != a)
        {
            cout << b << " ";
            b = m[b];
        }
        cout << b << "\n";
    }
}

// Find if the graph is connected graph
bool isConnected(vector<vector<int>> &edges, int n)
{
    vector<bool> visited(n, false);
    queue<int> q;
    visited[0] = true;
    q.push(0);

    while (!q.empty())
    {
        int vert = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && edges[vert][i] == 1)
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (visited[i] == false)
            return false;
    return true;
}

// Return all components of graph
vector<vector<int>> getAllComponents(vector<vector<int>> &edges, int n)
{
    vector<vector<int>> components;
    queue<int> q;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            q.push(i);
            vector<int> component;
            while (!q.empty())
            {
                int vert = q.front();
                component.push_back(vert);
                q.pop();
                for (int i = 0; i < n; i++)
                {
                    if (!visited[i] && edges[vert][i] == 1)
                    {
                        q.push(i);
                        visited[i] = true;
                    }
                }
            }
            components.push_back(component);
        }
    }
    return components;
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

    printBFSDisconnected(adjMat, n);

    cout << "Your graph is of type: " << (isConnected(adjMat, n) ? "Connected" : "Disconnected") << "\n";

    // cout << "Enter two vertices to check the path between them: ";
    // int a, b;
    // cin >> a >> b;
    // if (hasPath(adjMat, n, a, b))
    //     cout << "Yes\n";
    // else
    //     cout << "No\n";

    // cout << "The path of two vertices is: \n";
    // printPath(adjMat, n, a, b);

    vector<vector<int>> components = getAllComponents(adjMat, n);
    cout << "All components are :\n";
    for (auto com : components)
    {
        for (auto x : com)
            cout << x << " ";
        cout << " \n";
    }

    return 0;
}