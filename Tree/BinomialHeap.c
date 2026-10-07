#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct BinomialNode {
    int key;
    int degree;
    struct BinomialNode *parent;
    struct BinomialNode *child;
    struct BinomialNode *sibling;
} BinomialNode;
BinomialNode *createNode(int key) {
    BinomialNode *node = (BinomialNode *)malloc(sizeof(BinomialNode));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}
BinomialNode *binomialLink(BinomialNode *y, BinomialNode *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
    return z;
}
BinomialNode *mergeRootLists(BinomialNode *h1, BinomialNode *h2) {
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    BinomialNode *head = NULL;
    BinomialNode *tail = NULL;
    while (h1 != NULL && h2 != NULL) {
        BinomialNode *temp;
        if (h1->degree <= h2->degree) {
            temp = h1;
            h1 = h1->sibling;
        } else {
            temp = h2;
            h2 = h2->sibling;
        }
        if (head == NULL) {
            head = temp;
            tail = temp;
        } else {
            tail->sibling = temp;
            tail = temp;
        }
    }
    if (h1 != NULL)
        tail->sibling = h1;
    else
        tail->sibling = h2;
    return head;
}
BinomialNode *unionHeap(BinomialNode *h1, BinomialNode *h2) {
    BinomialNode *head = mergeRootLists(h1, h2);
    if (head == NULL)
        return NULL;
    BinomialNode *prev = NULL;
    BinomialNode *curr = head;
    BinomialNode *next = curr->sibling;
    while (next != NULL) {
        if (curr->degree != next->degree ||
            (next->sibling != NULL && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else if (curr->key <= next->key) {
            curr->sibling = next->sibling;
            binomialLink(next, curr);
        } else {
            if (prev == NULL)
                head = next;
            else
                prev->sibling = next;
            binomialLink(curr, next);
            curr = next;
        }
        next = curr->sibling;
    }
    return head;
}
BinomialNode *insert(BinomialNode *heap, int key) {
    BinomialNode *newNode = createNode(key);
    return unionHeap(heap, newNode);
}
BinomialNode *findMin(BinomialNode *heap) {
    if (heap == NULL)
        return NULL;
    BinomialNode *minNode = heap;
    BinomialNode *current = heap->sibling;
    while (current != NULL) {
        if (current->key < minNode->key)
            minNode = current;
        current = current->sibling;
    }
    return minNode;
}
BinomialNode *reverseList(BinomialNode *node) {
    BinomialNode *prev = NULL;
    BinomialNode *current = node;
    while (current != NULL) {
        BinomialNode *next = current->sibling;
        current->sibling = prev;
        current->parent = NULL;
        prev = current;
        current = next;
    }
    return prev;
}
BinomialNode *deleteMin(BinomialNode *heap) {
    if (heap == NULL)
        return NULL;
    BinomialNode *minNode = heap;
    BinomialNode *minPrev = NULL;
    BinomialNode *prev = NULL;
    BinomialNode *current = heap;
    while (current != NULL) {
        if (current->key < minNode->key) {
            minNode = current;
            minPrev = prev;
        }
        prev = current;
        current = current->sibling;
    }
    if (minPrev == NULL)
        heap = minNode->sibling;
    else
        minPrev->sibling = minNode->sibling;
    BinomialNode *children = reverseList(minNode->child);
    minNode->child = NULL;
    free(minNode);
    return unionHeap(heap, children);
}
void printTree(BinomialNode *root, int level) {
    if (root == NULL)
        return;
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%d\n", root->key);
    BinomialNode *child = root->child;
    while (child != NULL) {
        printTree(child, level + 1);
        child = child->sibling;
    }
}
void printHeap(BinomialNode *heap) {
    if (heap == NULL) {
        printf("Heap is empty.\n");
        return;
    }
    BinomialNode *current = heap;
    while (current != NULL) {
        printf("B%d Tree:\n", current->degree);
        printTree(current, 0);
        current = current->sibling;
    }
}
void freeHeap(BinomialNode *heap) {
    if (heap == NULL)
        return;
    BinomialNode *current = heap;
    while (current != NULL) {
        BinomialNode *next = current->sibling;
        freeHeap(current->child);
        free(current);
        current = next;
    }
}
int main() {
    BinomialNode *heap = NULL;
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of elements.\n");
        return 0;
    }
    int *elements = (int *)malloc(n * sizeof(int));
    if (elements == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }
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
        heap = insert(heap, elements[i]);
        printf("\nAfter insertion of %d:\n", elements[i]);
        printHeap(heap);
    }
    end = clock();
    insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
    BinomialNode *minNode = findMin(heap);
    if (minNode != NULL)
        printf("\nMinimum element: %d\n", minNode->key);
    printf("\nStarting deletion of minimum elements:\n");
    start = clock();
    while (heap != NULL) {
        minNode = findMin(heap);
        printf("\nDeleting minimum: %d\n", minNode->key);
        heap = deleteMin(heap);
        printf("Heap after deletion:\n");
        printHeap(heap);
    }
    end = clock();
    deletionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution Time:\n");
    printf("Insertion Time: %.6f seconds\n", insertionTime);
    printf("Deletion Time: %.6f seconds\n", deletionTime);
    freeHeap(heap);
    free(elements);
    return 0;
}