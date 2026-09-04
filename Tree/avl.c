// AVL Tree
// Operations: Insertion, Searching, Deletion
// Traversals: Inorder, Preorder, Postorder
// Also measures execution time

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure of an AVL node
struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

// Function to find maximum of two numbers
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

// Function to find height of a node
int height(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return root->height;
}

// Function to create a new node
struct Node* createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    // New node initially has height 1
    newNode->height = 1;

    return newNode;
}

// Right rotation
struct Node* rightRotate(struct Node *y)
{
    struct Node *x;
    struct Node *temp;

    x = y->left;
    temp = x->right;

    // Perform rotation
    x->right = y;
    y->left = temp;

    // Update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotation
struct Node* leftRotate(struct Node *x)
{
    struct Node *y;
    struct Node *temp;

    y = x->right;
    temp = y->left;

    // Perform rotation
    y->left = x;
    x->right = temp;

    // Update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Function to calculate balance factor
int getBalance(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return height(root->left) - height(root->right);
}

// Function to insert a value into AVL tree
struct Node* insert(struct Node *root, int value)
{
    int balance;

    // Normal BST insertion
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        return root;
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Find balance factor
    balance = getBalance(root);

    // Case 1: Left Left
    if (balance > 1 && value < root->left->data)
    {
        return rightRotate(root);
    }

    // Case 2: Right Right
    if (balance < -1 && value > root->right->data)
    {
        return leftRotate(root);
    }

    // Case 3: Left Right
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 4: Right Left
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a value
struct Node* search(struct Node *root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->data == value)
    {
        return root;
    }

    if (value < root->data)
    {
        return search(root->left, value);
    }

    return search(root->right, value);
}

// Function to find the smallest node
struct Node* findMin(struct Node *root)
{
    struct Node *current = root;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Function to delete a node from AVL tree
struct Node* deleteNode(struct Node *root, int value)
{
    struct Node *temp;
    int balance;

    // If tree is empty
    if (root == NULL)
    {
        return NULL;
    }

    // Normal BST deletion
    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        // Node with no child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        // Node with only right child
        else if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        // Node with only left child
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        else
        {
            temp = findMin(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, temp->data);
        }
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Check balance
    balance = getBalance(root);

    // Left Left case
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }

    // Left Right case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right case
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return leftRotate(root);
    }

    // Right Left case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Main function
int main()
{
    struct Node *root = NULL;

    int n, i;
    int value;
    int searchValue;
    int deleteValue;

    clock_t start, end;
    double timeTaken;

    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    // Seed random number generator
    srand(time(NULL));

    // ---------------- INSERTION ----------------

    start = clock();

    for (i = 0; i < n; i++)
    {
        value = rand() % (n * 10 + 1);

        root = insert(root, value);
    }

    end = clock();

    timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nAVL Tree after insertion:\n");

    printf("Inorder   : ");
    inorder(root);

    printf("\nPreorder  : ");
    preorder(root);

    printf("\nPostorder : ");
    postorder(root);

    printf("\n\nInsertion time: %f seconds\n", timeTaken);

    // ---------------- SEARCHING ----------------

    printf("\nEnter value to search: ");
    scanf("%d", &searchValue);

    start = clock();

    if (search(root, searchValue) != NULL)
    {
        printf("Value %d found in AVL Tree.\n", searchValue);
    }
    else
    {
        printf("Value %d not found in AVL Tree.\n", searchValue);
    }

    end = clock();

    timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Searching time: %f seconds\n", timeTaken);

    // ---------------- DELETION ----------------

    printf("\nEnter value to delete: ");
    scanf("%d", &deleteValue);

    start = clock();

    root = deleteNode(root, deleteValue);

    end = clock();

    timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nAVL Tree after deletion:\n");

    printf("Inorder   : ");
    inorder(root);

    printf("\nPreorder  : ");
    preorder(root);

    printf("\nPostorder : ");
    postorder(root);

    printf("\n\nDeletion time: %f seconds\n", timeTaken);

    return 0;
}