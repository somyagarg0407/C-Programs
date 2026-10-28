#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// ---------- Adjacency Matrix ----------
int adjMatrix[MAX][MAX];
int vertices;

// ---------- Adjacency List ------------
struct Node {
    int data;
    struct Node* next;
};

struct Node* adjList[MAX];

// Create new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

// ---------- GRAPH CREATION ----------
void initGraph(int v) {
    vertices = v;
    for(int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
        for(int j = 0; j < vertices; j++)
            adjMatrix[i][j] = 0;
    }
}

// ---------- ADD EDGE ----------
void addEdge(int src, int dest) {
    // Matrix
    adjMatrix[src][dest] = 1;
    adjMatrix[dest][src] = 1;

    // List
    struct Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

// ---------- DELETE EDGE ----------
void deleteEdge(int src, int dest) {
    adjMatrix[src][dest] = 0;
    adjMatrix[dest][src] = 0;
}

// ---------- BFS ----------
void BFS(int start) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS: ");

    while(front < rear) {
        int v = queue[front++];
        printf("%d ", v);

        for(int i = 0; i < vertices; i++) {
            if(adjMatrix[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

// ---------- DFS ----------
void DFSUtil(int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);

    struct Node* temp = adjList[v];
    while(temp) {
        if(!visited[temp->data])
            DFSUtil(temp->data, visited);
        temp = temp->next;
    }
}

void DFS(int start) {
    int visited[MAX] = {0};
    printf("DFS: ");
    DFSUtil(start, visited);
    printf("\n");
}

// ---------- DISPLAY ----------
void printMatrix() {
    printf("\nAdjacency Matrix:\n");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void printList() {
    printf("\nAdjacency List:\n");
    for(int i = 0; i < vertices; i++) {
        struct Node* temp = adjList[i];
        printf("%d -> ", i);
        while(temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// ---------- MAIN ----------
int main() {
    initGraph(5);

    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,3);
    addEdge(2,4);

    printMatrix();
    printList();

    BFS(0);
    DFS(0);

    deleteEdge(0,1);

    printf("\nAfter deleting edge (0-1):\n");
    printMatrix();

    return 0;
}