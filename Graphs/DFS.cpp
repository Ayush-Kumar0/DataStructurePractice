#include <iostream>
#include <vector>
using namespace std;

// Print Connected graph
void printDFSConnected(vector<vector<int>> &edges, int n, int startV, vector<bool> &visited)
{
    cout << startV << " ";
    visited[startV] = true;

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue;
        if (edges[startV][i] == 1)
            printDFSConnected(edges, n, i, visited);
    }
}

// Print Disconnected Graph
void printDFSDisconnected(vector<vector<int>> &edges, int n)
{
    cout << "Graph DFS:\n";
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            printDFSConnected(edges, n, i, visited);
            cout << "\n";
        }
}

// Find if there exists a path from one vertex to another
bool hasPathHelper(vector<vector<int>> &edges, int n, int a, int b, vector<bool> &visited)
{
    if (edges[a][b] == 1)
        return true;
    visited[a] = true;

    bool has = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && edges[a][i] == 1)
            has = has || hasPathHelper(edges, n, i, b, visited);
        if (has)
            break;
    }
    return has;
}
bool hasPath(vector<vector<int>> &edges, int n, int a, int b)
{
    vector<bool> visited(n, false);
    return hasPathHelper(edges, n, a, b, visited);
}

// Print the path from one vertex to another
bool printPathHelper(vector<vector<int>> &edges, int n, int a, int b, vector<bool> &visited)
{
    visited[a] = true;
    if (a == b)
    {
        cout << a << " ";
        return true;
    }
    bool has = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && edges[a][i] == 1)
        {
            has = has || printPathHelper(edges, n, i, b, visited);
        }
    }
    if (has)
        cout << a << " ";
    return has;
}
bool printPath(vector<vector<int>> &edges, int n, int a, int b)
{
    vector<bool> visited(n, 0);
    return printPathHelper(edges, n, a, b, visited);
}

// Find if the graph is connected graph
void traverseAllVertices(vector<vector<int>> &edges, int n, int startV, vector<bool> &visited)
{
    visited[startV] = true;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && edges[startV][i] == 1)
            traverseAllVertices(edges, n, i, visited);
    }
}
bool isConnected(vector<vector<int>> &edges, int n)
{
    vector<bool> visited(n, false);
    traverseAllVertices(edges, n, 0, visited);
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false)
            return false;
    }
    return true;
}

// Return all components of graph
void getOneComponent(vector<vector<int>> &edges, int n, int startV, vector<bool> &visited, vector<int> &component)
{
    component.push_back(startV);
    visited[startV] = true;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && edges[startV][i] == 1)
        {
            getOneComponent(edges, n, i, visited, component);
        }
    }
}
vector<vector<int>> getComponents(vector<vector<int>> &edges, int n)
{
    vector<vector<int>> components;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            vector<int> component;
            getOneComponent(edges, n, i, visited, component);
            if (component.size() > 0)
                components.push_back(component);
        }
    }
    return components;
}

// Count the number of components in a graph
int countIslands(vector<vector<int>> &edges, int n)
{
    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            traverseAllVertices(edges, n, i, visited);
            count++;
        }
    }
    return count;
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

    printDFSDisconnected(adjMat, n);

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

    vector<vector<int>> components = getComponents(adjMat, n);
    cout << "All components are :\n";
    for (auto com : components)
    {
        for (auto x : com)
            cout << x << " ";
        cout << "\n";
    }

    cout << "\nNumer of islands are: " << countIslands(adjMat, n) << "\n";

    return 0;
}