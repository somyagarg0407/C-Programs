#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 999999999

int main()
{
    int V, E;
    int i, j;
    int src, dest, weight;
    int source;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int graph[V][V];

    // Initialize graph with INF
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    printf("Enter the edges (source destination weight):\n");

    for (i = 0; i < E; i++)
    {
        scanf("%d %d %d", &src, &dest, &weight);

        if (src < 0 || src >= V || dest < 0 || dest >= V || weight < 0)
        {
            printf("Invalid edge input!\n");
            return 1;
        }

        graph[src][dest] = weight;
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    if (source < 0 || source >= V)
    {
        printf("Invalid source vertex!\n");
        return 1;
    }

    int dist[V];
    int visited[V];

    // Initialize distances and visited array
    for (i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[source] = 0;

    clock_t start = clock();

    // Dijkstra's Algorithm
    for (i = 0; i < V - 1; i++)
    {
        int minDist = INF;
        int u = -1;

        // Find the unvisited vertex with minimum distance
        for (j = 0; j < V; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }

        // No more reachable vertices
        if (u == -1)
            break;

        visited[u] = 1;

        // Relax all outgoing edges from u
        for (j = 0; j < V; j++)
        {
            if (!visited[j] &&
                graph[u][j] != INF &&
                dist[u] != INF &&
                dist[u] + graph[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }

    clock_t end = clock();

    printf("\nShortest Paths using Dijkstra's Algorithm:\n");
    printf("Vertex\tDistance\n");

    for (i = 0; i < V; i++)
    {
        if (dist[i] == INF)
            printf("%d\tINF (Unreachable)\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }

    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nExecution Time (Dijkstra's Algorithm): %.6f seconds\n",
           executionTime);

    return 0;
}