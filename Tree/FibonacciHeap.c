#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct FibNode {
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;
typedef struct {
    FibNode *min;
    int n;
} FibHeap;
FibNode *createNode(int key) {
    FibNode *node = (FibNode *)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}
FibHeap *createHeap() {
    FibHeap *heap = (FibHeap *)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}
void insert(FibHeap *heap, int key) {
    FibNode *node = createNode(key);
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;
        if (node->key < heap->min->key)
            heap->min = node;
    }
    heap->n++;
}
void printChildren(FibNode *node, int level) {
    if (node == NULL)
        return;
    FibNode *start = node;
    FibNode *curr = start;
    do {
        for (int i = 0; i < level; i++)
            printf("  ");
        printf("%d\n", curr->key);
        if (curr->child != NULL)
            printChildren(curr->child, level + 1);
        curr = curr->right;
    } while (curr != start);
}
void printHeap(FibHeap *heap) {
    if (heap->min == NULL) {
        printf("Heap is empty.\n");
        return;
    }
    printf("Root List:\n");
    FibNode *start = heap->min;
    FibNode *curr = start;
    do {
        printf("%d", curr->key);
        if (curr == heap->min)
            printf(" <- MIN");
        printf("\n");
        if (curr->child != NULL) {
            printf("  Children:\n");
            printChildren(curr->child, 2);
        }
        curr = curr->right;
    } while (curr != start);
}
void link(FibHeap *heap, FibNode *y, FibNode *x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}
void consolidate(FibHeap *heap) {
    int maxDegree = 100;
    FibNode *A[100];
    for (int i = 0; i < maxDegree; i++)
        A[i] = NULL;
    int rootCount = 0;
    FibNode *start = heap->min;
    FibNode *curr = start;
    if (curr != NULL) {
        do {
            rootCount++;
            curr = curr->right;
        } while (curr != start);
    }
    FibNode **roots = (FibNode **)malloc(rootCount * sizeof(FibNode *));
    curr = start;
    for (int i = 0; i < rootCount; i++) {
        roots[i] = curr;
        curr = curr->right;
    }
    for (int i = 0; i < rootCount; i++) {
        FibNode *x = roots[i];
        int d = x->degree;
        while (A[d] != NULL) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }
            link(heap, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }
    heap->min = NULL;
    for (int i = 0; i < maxDegree; i++) {
        if (A[i] != NULL) {
            A[i]->left = A[i];
            A[i]->right = A[i];
            if (heap->min == NULL) {
                heap->min = A[i];
            } else {
                A[i]->right = heap->min->right;
                A[i]->left = heap->min;
                heap->min->right->left = A[i];
                heap->min->right = A[i];
                if (A[i]->key < heap->min->key)
                    heap->min = A[i];
            }
        }
    }
    free(roots);
}
int deleteMin(FibHeap *heap) {
    if (heap->min == NULL)
        return -1;
    FibNode *z = heap->min;
    if (z->child != NULL) {
        FibNode *start = z->child;
        FibNode *curr = start;
        int count = 0;
        do {
            count++;
            curr = curr->right;
        } while (curr != start);
        FibNode **children = (FibNode **)malloc(count * sizeof(FibNode *));
        curr = start;
        for (int i = 0; i < count; i++) {
            children[i] = curr;
            curr = curr->right;
        }
        for (int i = 0; i < count; i++) {
            FibNode *child = children[i];
            child->parent = NULL;
            child->left = heap->min;
            child->right = heap->min->right;
            heap->min->right->left = child;
            heap->min->right = child;
        }
        free(children);
        z->child = NULL;
    }
    if (z->right == z) {
        heap->min = NULL;
    } else {
        z->left->right = z->right;
        z->right->left = z->left;
        heap->min = z->right;
        consolidate(heap);
    }
    int minValue = z->key;
    free(z);
    heap->n--;
    return minValue;
}
int findMin(FibHeap *heap) {
    if (heap->min == NULL)
        return -1;
    return heap->min->key;
}
void freeNodes(FibNode *node) {
    if (node == NULL)
        return;
    FibNode *start = node;
    FibNode *curr = start;
    do {
        FibNode *next = curr->right;
        if (curr->child != NULL)
            freeNodes(curr->child);
        free(curr);
        curr = next;
    } while (curr != start);
}
int main() {
    FibHeap *heap = createHeap();
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid value of n.\n");
        return 0;
    }
    int *elements = (int *)malloc(n * sizeof(int));
    srand((unsigned int)time(NULL));
    printf("\nGenerated elements: ");
    for (int i = 0; i < n; i++) {
        elements[i] = rand() % (n * 10 + 1) + 1;
        printf("%d ", elements[i]);
    }
    printf("\n");
    clock_t start, end;
    double insertionTime, deletionTime;
    start = clock();
    for (int i = 0; i < n; i++) {
        insert(heap, elements[i]);
        printf("\nAfter insertion of %d:\n", elements[i]);
        printHeap(heap);
    }
    end = clock();
    insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nMinimum element: %d\n", findMin(heap));
    start = clock();
    while (heap->min != NULL) {
        int minValue = findMin(heap);
        printf("\nDeleting minimum: %d\n", minValue);
        deleteMin(heap);
        printf("Heap after deletion:\n");
        printHeap(heap);
    }
    end = clock();
    deletionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution Time:\n");
    printf("Insertion Time: %.6f seconds\n", insertionTime);
    printf("Deletion Time: %.6f seconds\n", deletionTime);
    free(elements);
    free(heap);
    return 0;
}