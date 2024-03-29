#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
#define V 6  //  указать кол во вершин в графе

bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);

    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();

        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;
    int rGraph[V][V];  // Остаточная сеть
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)


            rGraph[u][v] = graph[u][v];

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;

            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;

        // Вывод состояния графа
        cout << "The state of the graph after increasing the flow by " << path_flow << ":" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                cout << rGraph[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return max_flow;
}

int main()
{

    int graph[V][V];
    cout << "Enter the bandwidth matrix for the graph (" << V << "x" << V << "):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {

            cin >> graph[i][j];

        }
    }
    int source, sink;
    cout << "Enter the source and drain: ";
    cin >> source >> sink;

    // Вызов алгоритма Ф-Ф
    cout << "The maximum flow in the graph: " << fordFulkerson(graph, source, sink) << endl;
    return 0;
}
