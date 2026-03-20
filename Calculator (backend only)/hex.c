#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

/* Create new node */
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/* Insert at beginning */
void insertBeginning(int data)
{
    struct Node *newNode = createNode(data);
    if (newNode == NULL)
        return;

    newNode->next = head;
    head = newNode;
}

/* Insert at end */
void insertEnd(int data)
{
    struct Node *newNode = createNode(data);
    if (newNode == NULL)
        return;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

/* Insert at specific position */
void insertPosition(int data, int pos)
{
    if (pos == 1)
    {
        insertBeginning(data);
        return;
    }

    struct Node *newNode = createNode(data);
    if (newNode == NULL)
        return;

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Invalid position\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

/* Delete from beginning */
void deleteBeginning()
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;
    free(temp);
}

/* Delete from end */
void deleteEnd()
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}

/* Delete from specific position */
void deletePosition(int pos)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (pos == 1)
    {
        deleteBeginning();
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp->next != NULL; i++)
        temp = temp->next;

    if (temp->next == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    struct Node *delNode = temp->next;
    temp->next = delNode->next;
    free(delNode);
}

/* Display list */
void display()
{
    struct Node *temp = head;
    if (temp == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* Reverse entire list */
void reverseList()
{
    struct Node *prev = NULL, *curr = head, *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

/* Reverse in groups of k */
struct Node *reverseK(struct Node *headRef, int k)
{
    struct Node *curr = headRef, *prev = NULL, *next = NULL;
    int count = 0;

    while (curr != NULL && count < k)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
        _hook_
    }

    if (next != NULL)
        headRef->next = reverseK(next, k);

    return prev;
}

void reverseInGroups(int k)
{
    head = reverseK(head, k);
}

/* Main menu */
int main()
{
    int choice, data, pos, k;

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete from position\n");
        printf("7. Display list\n");
        printf("8. Reverse list\n");
        printf("9. Reverse in groups of k\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            insertBeginning(data);
            break;

        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            insertEnd(data);
            break;

        case 3:
            printf("Enter data and position: ");
            scanf("%d %d", &data, &pos);
            insertPosition(data, pos);
            break;

        case 4:
            deleteBeginning();
            break;

        case 5:
            deleteEnd();
            break;

        case 6:
            printf("Enter position: ");
            scanf("%d", &pos);
            deletePosition(pos);
            break;

        case 7:
            display();
            break;

        case 8:
            reverseList();
            break;

        case 9:
            printf("Enter k: ");
            scanf("%d", &k);
            reverseInGroups(k);
            break;

        case 0:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}
