
#include <stdio.h>
#include <time.h>
#define INF 999999999
struct Edge
{
    int src, dest, weight;
};
int main()
{
    int V, E, i, j, source;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);
    if (V <= 0 || E < 0)
    {
        printf("Invalid number of vertices or edges!\n");
        return 1;
    }
    struct Edge edges[E > 0 ? E : 1];
    printf("Enter the edges (source destination weight):\n");
    for (i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        if (edges[i].src < 0 || edges[i].src >= V || edges[i].dest < 0 || edges[i].dest >= V)
        {
            printf("Invalid edge input!\n");
            return 1;
        }
    }
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    if (source < 0 || source >= V)
    {
        printf("Invalid source vertex!\n");
        return 1;
    }
    int dist[V];
    for (i = 0; i < V; i++)
        dist[i] = INF;
    dist[source] = 0;
    clock_t start = clock();
    for (i = 0; i < V - 1; i++)
    {
        int updated = 0;
        for (j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        if (!updated)
            break;
    }
    clock_t end = clock();
    int negativeCycle = 0;
    for (i = 0; i < E; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;
        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            negativeCycle = 1;
            break;
        }
    }
    if (negativeCycle)
    {
        printf("\nNegative-weight cycle detected!\n");
        printf("Shortest paths are not well-defined.\n");
    }
    else
    {
        printf("\nShortest Paths using Bellman-Ford Algorithm:\n");
        printf("Vertex\tDistance\n");
        int allReachable = 1;
        for (i = 0; i < V; i++)
        {
            if (dist[i] == INF)
            {
                printf("%d\tINF (Unreachable)\n", i);
                allReachable = 0;
            }
            else
                printf("%d\t%d\n", i, dist[i]);
        }
        if (allReachable)
            printf("A shortest-path tree exists for all vertices.\n");
        else
            printf("A shortest-path tree spanning all vertices does not exist because some vertices are unreachable.\n");
    }
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution Time (Bellman-Ford Algorithm): %.6f seconds\n", executionTime);
    return 0;
}

