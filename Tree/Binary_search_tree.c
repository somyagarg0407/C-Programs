// Binary Search Tree (BST)
// Operations: Insertion, Searching, Deletion
// Traversals: Inorder, Preorder, Postorder
// Also measures execution time

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure of a BST node
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to insert a value into BST
struct Node* insert(struct Node *root, int value)
{
    // If tree is empty, create a new node
    if (root == NULL)
    {
        return createNode(value);
    }

    // Smaller values go to the left
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }

    // Greater values go to the right
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }

    // If value is equal, do not insert duplicate
    return root;
}

// Function to search for a value
struct Node* search(struct Node *root, int value)
{
    // Value not found
    if (root == NULL)
    {
        return NULL;
    }

    // Value found
    if (root->data == value)
    {
        return root;
    }

    // Search in left subtree
    if (value < root->data)
    {
        return search(root->left, value);
    }

    // Search in right subtree
    return search(root->right, value);
}

// Function to find the smallest node
struct Node* findMin(struct Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

// Function to delete a node
struct Node* deleteNode(struct Node *root, int value)
{
    struct Node *temp;

    // Value not found
    if (root == NULL)
    {
        return NULL;
    }

    // Search in left subtree
    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }

    // Search in right subtree
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }

    // Node found
    else
    {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        // Case 2: Only right child
        else if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        // Case 3: Only left child
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        // Case 4: Two children
        else
        {
            // Find smallest value in right subtree
            temp = findMin(root->right);

            // Replace current value
            root->data = temp->data;

            // Delete duplicate node
            root->right = deleteNode(root->right, temp->data);
        }
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

    // Seed for random number generation
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

    printf("\nBST after insertion:\n");

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
        printf("Value %d found in BST.\n", searchValue);
    }
    else
    {
        printf("Value %d not found in BST.\n", searchValue);
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

    printf("\nBST after deletion:\n");

    printf("Inorder   : ");
    inorder(root);

    printf("\nPreorder  : ");
    preorder(root);

    printf("\nPostorder : ");
    postorder(root);

    printf("\n\nDeletion time: %f seconds\n", timeTaken);

    return 0;
}
