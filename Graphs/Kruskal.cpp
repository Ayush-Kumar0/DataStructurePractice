#include <iostream>
#include <algorithm>
using namespace std;

// Class used for creating edge list
class Edge
{
public:
    int v1, v2;
    int wt;
    Edge()
    {
        v1 = v2 = wt = -1;
    }
    Edge(int v1, int v2, int wt)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->wt = wt;
    }
};

// Comparator to sort the edge list according to their weights
bool cmp(Edge prev, Edge next)
{
    return prev.wt < next.wt;
}

// Displays the edge list of the graph
void displayEdgeList(Edge *edges, int e)
{
    for (int i = 0; i < e; i++)
        cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].wt << "\n";
}

// Create Minimum Spanning Tree (MST)
int createMST(Edge *edges, int n, int e, Edge *out)
{
    int parents[n];
    for (int i = 0; i < n; i++)
        parents[i] = i;

    int count = 0;
    int i = 0;
    while (count < n - 1)
    {
        Edge curr = edges[i++];
        int v1 = curr.v1;
        int v2 = curr.v2;
        int wt = curr.wt;

        int p1 = parents[v1];
        while (p1 != parents[p1])
            p1 = parents[p1];
        int p2 = parents[v2];
        while (p2 != parents[p2])
            p2 = parents[p2];

        if (p1 == p2)
            continue;

        out[count++] = Edge(v1, v2, wt);
        parents[p1] = p2;
    }

    return count;
}

int main(int argc, char *argv[])
{
    cout << "Enter number of vertices: ";
    int n;
    cin >> n;
    cout << "Enter number of edges: ";
    int e;
    cin >> e;

    Edge edges[e];
    cout << "Enter the edges and weights:\n";
    for (int i = 0; i < e; i++)
        cin >> edges[i].v1 >> edges[i].v2 >> edges[i].wt;

    sort(edges, edges + e, cmp);

    cout << "\nGraph is:\n";
    displayEdgeList(edges, e);

    Edge mst[n - 1];
    int mstSize = createMST(edges, n, e, mst);
    cout << "\nMinimum Spanning Tree is:\n";
    displayEdgeList(mst, mstSize);

    return 0;
}