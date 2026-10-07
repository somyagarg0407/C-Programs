#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_KEYS 100
typedef struct BTreeNode
{
    int keys[MAX_KEYS];
    struct BTreeNode *child[MAX_KEYS + 1];
    int n;
    int leaf;
} BTreeNode;
int T;
BTreeNode *createNode(int leaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i <= MAX_KEYS; i++)
        node->child[i] = NULL;
    return node;
}
void traverseInorder(BTreeNode *root)
{
    if (root == NULL)
        return;
    int i;
    for (i = 0; i < root->n; i++)
    {
        if (!root->leaf)
            traverseInorder(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverseInorder(root->child[i]);
}
void traversePreorder(BTreeNode *root)
{
    if (root == NULL)
        return;
    for (int i = 0; i < root->n; i++)
        printf("%d ", root->keys[i]);
    for (int i = 0; i <= root->n; i++)
        if (!root->leaf)
            traversePreorder(root->child[i]);
}
void traversePostorder(BTreeNode *root)
{
    if (root == NULL)
        return;
    for (int i = 0; i <= root->n; i++)
        if (!root->leaf)
            traversePostorder(root->child[i]);
    for (int i = 0; i < root->n; i++)
        printf("%d ", root->keys[i]);
}
BTreeNode *search(BTreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;
    if (i < root->n && key == root->keys[i])
        return root;
    if (root->leaf)
        return NULL;
    return search(root->child[i], key);
}
void splitChild(BTreeNode *parent, int index, BTreeNode *fullChild)
{
    BTreeNode *newChild = createNode(fullChild->leaf);
    newChild->n = T - 1;
    for (int j = 0; j < T - 1; j++)
        newChild->keys[j] = fullChild->keys[j + T];
    if (!fullChild->leaf)
    {
        for (int j = 0; j < T; j++)
            newChild->child[j] = fullChild->child[j + T];
    }
    fullChild->n = T - 1;
    for (int j = parent->n; j >= index + 1; j--)
        parent->child[j + 1] = parent->child[j];
    parent->child[index + 1] = newChild;
    for (int j = parent->n - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[index] = fullChild->keys[T - 1];
    parent->n++;
}
void insertNonFull(BTreeNode *node, int key)
{
    int i = node->n - 1;
    if (node->leaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->child[i]->n == 2 * T - 1)
        {
            splitChild(node, i, node->child[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->child[i], key);
    }
}
BTreeNode *insert(BTreeNode *root, int key)
{
    if (root == NULL)
    {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return root;
    }
    if (root->n == 2 * T - 1)
    {
        BTreeNode *newRoot = createNode(0);
        newRoot->child[0] = root;
        splitChild(newRoot, 0, root);
        int i = 0;
        if (key > newRoot->keys[0])
            i++;
        insertNonFull(newRoot->child[i], key);
        return newRoot;
    }
    insertNonFull(root, key);
    return root;
}
int getPredecessor(BTreeNode *node)
{
    while (!node->leaf)
        node = node->child[node->n];
    return node->keys[node->n - 1];
}
int getSuccessor(BTreeNode *node)
{
    while (!node->leaf)
        node = node->child[0];
    return node->keys[0];
}
void removeKey(BTreeNode *node, int key);
void borrowFromPrevious(BTreeNode *node, int index)
{
    BTreeNode *child = node->child[index];
    BTreeNode *sibling = node->child[index - 1];
    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];
        child->child[0] = sibling->child[sibling->n];
    }
    child->keys[0] = node->keys[index - 1];
    node->keys[index - 1] = sibling->keys[sibling->n - 1];
    child->n++;
    sibling->n--;
}
void borrowFromNext(BTreeNode *node, int index)
{
    BTreeNode *child = node->child[index];
    BTreeNode *sibling = node->child[index + 1];
    child->keys[child->n] = node->keys[index];
    if (!child->leaf)
        child->child[child->n + 1] = sibling->child[0];
    node->keys[index] = sibling->keys[0];
    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] = sibling->child[i];
    }
    child->n++;
    sibling->n--;
}
void merge(BTreeNode *node, int index)
{
    BTreeNode *child = node->child[index];
    BTreeNode *sibling = node->child[index + 1];
    child->keys[T - 1] = node->keys[index];
    for (int i = 0; i < sibling->n; i++)
        child->keys[i + T] = sibling->keys[i];
    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; i++)
            child->child[i + T] = sibling->child[i];
    }
    for (int i = index + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];
    for (int i = index + 2; i <= node->n; i++)
        node->child[i - 1] = node->child[i];
    child->n += sibling->n + 1;
    node->n--;
    free(sibling);
}
void fill(BTreeNode *node, int index)
{
    if (index != 0 && node->child[index - 1]->n >= T)
        borrowFromPrevious(node, index);
    else if (index != node->n && node->child[index + 1]->n >= T)
        borrowFromNext(node, index);
    else
    {
        if (index != node->n)
            merge(node, index);
        else
            merge(node, index - 1);
    }
}
void removeFromLeaf(BTreeNode *node, int index)
{
    for (int i = index + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];
    node->n--;
}
void removeFromNonLeaf(BTreeNode *node, int index)
{
    int key = node->keys[index];
    if (node->child[index]->n >= T)
    {
        int pred = getPredecessor(node->child[index]);
        node->keys[index] = pred;
        removeKey(node->child[index], pred);
    }
    else if (node->child[index + 1]->n >= T)
    {
        int succ = getSuccessor(node->child[index + 1]);
        node->keys[index] = succ;
        removeKey(node->child[index + 1], succ);
    }
    else
    {
        merge(node, index);
        removeKey(node->child[index], key);
    }
}
void removeKey(BTreeNode *node, int key)
{
    int index = 0;
    while (index < node->n && node->keys[index] < key)
        index++;
    if (index < node->n && node->keys[index] == key)
    {
        if (node->leaf)
            removeFromLeaf(node, index);
        else
            removeFromNonLeaf(node, index);
    }
    else
    {
        if (node->leaf)
            return;
        int flag = (index == node->n);
        if (node->child[index]->n < T)
            fill(node, index);
        if (flag && index > node->n)
            removeKey(node->child[index - 1], key);
        else
            removeKey(node->child[index], key);
    }
}
BTreeNode *deleteKey(BTreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    removeKey(root, key);
    if (root->n == 0)
    {
        BTreeNode *temp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];
        free(temp);
    }
    return root;
}
void printLevel(BTreeNode *root, int level)
{
    if (root == NULL)
        return;
    BTreeNode *queue[10000];
    int levels[10000];
    int front = 0, rear = 0;
    queue[rear] = root;
    levels[rear++] = 0;
    int currentLevel = 0;
    printf("Level 0: ");
    while (front < rear)
    {
        BTreeNode *node = queue[front];
        int nodeLevel = levels[front++];
        if (nodeLevel != currentLevel)
        {
            currentLevel = nodeLevel;
            printf("\nLevel %d: ", currentLevel);
        }
        printf("[");
        for (int i = 0; i < node->n; i++)
        {
            printf("%d", node->keys[i]);
            if (i < node->n - 1)
                printf(" ");
        }
        printf("] ");
        if (!node->leaf)
        {
            for (int i = 0; i <= node->n; i++)
            {
                queue[rear] = node->child[i];
                levels[rear++] = nodeLevel + 1;
            }
        }
    }
    printf("\n");
}
void freeTree(BTreeNode *root)
{
    if (root == NULL)
        return;
    if (!root->leaf)
    {
        for (int i = 0; i <= root->n; i++)
            freeTree(root->child[i]);
    }
    free(root);
}
int main()
{
    BTreeNode *root = NULL;
    int n, key;
    printf("Enter the minimum degree of B-Tree: ");
    scanf("%d", &T);
    if (T < 2 || 2 * T - 1 > MAX_KEYS)
    {
        printf("Invalid minimum degree.\n");
        return 0;
    }
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n <= 0 || n > 10000)
    {
        printf("Invalid number of elements.\n");
        return 0;
    }
    int *elements = (int *)malloc(n * sizeof(int));
    srand((unsigned int)time(NULL));
    printf("Elements inserted: ");
    for (int i = 0; i < n; i++)
    {
        elements[i] = rand() % (n * 10 + 1) + 1;
        printf("%d ", elements[i]);
    }
    printf("\n");
    clock_t start, end;
    double insertionTime, searchTime, deletionTime;
    start = clock();
    for (int i = 0; i < n; i++)
        root = insert(root, elements[i]);
    end = clock();
    insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nB-Tree after insertion:\n");
    printLevel(root, 0);
    printf("\nInorder:\n");
    traverseInorder(root);
    printf("\n");
    printf("\nPreorder:\n");
    traversePreorder(root);
    printf("\n");
    printf("\nPostorder:\n");
    traversePostorder(root);
    printf("\n");
    printf("\nSearch Operations:\n");
    start = clock();
    for (int i = 0; i < n; i++)
    {
        if (search(root, elements[i]) != NULL)
            printf("%d -> Found\n", elements[i]);
        else
            printf("%d -> Not Found\n", elements[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        key = n * 20 + i;
        if (search(root, key) != NULL)
            printf("%d -> Found\n", key);
        else
            printf("%d -> Not Found\n", key);
    }
    end = clock();
    searchTime = (double)(end - start) / CLOCKS_PER_SEC;
    start = clock();
    for (int i = 0; i < n; i++)
        root = deleteKey(root, elements[i]);
    end = clock();
    deletionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution Time:\n");
    printf("Insertion Time: %.6f seconds\n", insertionTime);
    printf("Searching Time: %.6f seconds\n", searchTime);
    printf("Deletion Time: %.6f seconds\n", deletionTime);
    freeTree(root);
    free(elements);
    return 0;
}