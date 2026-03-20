#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct Node *insertAtBeginning(struct Node *head, int data)
{
    struct Node *newNode = createNode(data);
    if (!head)
        return newNode;
    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

struct Node *insertAtEnd(struct Node *head, int data)
{
    struct Node *newNode = createNode(data);
    if (!head)
        return newNode;
    struct Node *temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

struct Node *insertAtPosition(struct Node *head, int data, int pos)
{
    if (pos < 1)
    {
        printf("Invalid position!\n");
        return head;
    }
    if (pos == 1)
        return insertAtBeginning(head, data);
    struct Node *newNode = createNode(data);
    struct Node *temp = head;
    for (int i = 1; i < pos - 1; i++)
    {
        if (!temp)
        {
            printf("Position out of range!\n");
            free(newNode);
            return head;
        }
        temp = temp->next;
    }
    if (!temp)
    {
        printf("Position out of range!\n");
        free(newNode);
        return head;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
        temp->next->prev = newNode;
    temp->next = newNode;
    return head;
}

struct Node *deleteFromBeginning(struct Node *head)
{
    if (!head)
    {
        printf("List is empty!\n");
        return NULL;
    }
    struct Node *temp = head;
    head = head->next;
    if (head)
        head->prev = NULL;
    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

struct Node *deleteFromEnd(struct Node *head)
{
    if (!head)
    {
        printf("List is empty!\n");
        return NULL;
    }
    struct Node *temp = head;
    while (temp->next)
        temp = temp->next;
    if (temp->prev)
        temp->prev->next = NULL;
    else
        head = NULL;
    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

struct Node *deleteFromPosition(struct Node *head, int pos)
{
    if (!head)
    {
        printf("List is empty!\n");
        return NULL;
    }
    if (pos < 1)
    {
        printf("Invalid position!\n");
        return head;
    }
    if (pos == 1)
        return deleteFromBeginning(head);
    struct Node *temp = head;
    for (int i = 1; i < pos; i++)
    {
        if (!temp)
        {
            printf("Position out of range!\n");
            return head;
        }
        temp = temp->next;
    }
    if (!temp)
    {
        printf("Position out of range!\n");
        return head;
    }
    if (temp->prev)
        temp->prev->next = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;
    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

void displayForward(struct Node *head)
{
    if (!head)
    {
        printf("List is empty!\n");
        return;
    }
    printf("Forward: ");
    while (head)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void displayBackward(struct Node *head)
{
    if (!head)
    {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    while (temp->next)
        temp = temp->next;
    printf("Backward: ");
    while (temp)
    {
        printf("%d -> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

struct Node *reverseList(struct Node *head)
{
    if (!head)
    {
        printf("List is empty!\n");
        return NULL;
    }
    struct Node *temp = NULL;
    struct Node *curr = head;
    while (curr)
    {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp)
        head = temp->prev;
    printf("List reversed successfully!\n");
    return head;
}

int main()
{
    struct Node *head = NULL;
    int choice, data, pos;
    printf("=== Doubly Linked List ===\n");
    do
    {
        printf("\n1.Insert Begin  2.Insert End  3.Insert Pos\n");
        printf("4.Del Begin  5.Del End  6.Del Pos\n");
        printf("7.Display Forward  8.Display Backward  9.Reverse  0.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            head = insertAtBeginning(head, data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            head = insertAtEnd(head, data);
            break;
        case 3:
            printf("Enter data and position: ");
            scanf("%d %d", &data, &pos);
            head = insertAtPosition(head, data, pos);
            break;
        case 4:
            head = deleteFromBeginning(head);
            break;
        case 5:
            head = deleteFromEnd(head);
            break;
        case 6:
            printf("Enter position: ");
            scanf("%d", &pos);
            head = deleteFromPosition(head, pos);
            break;
        case 7:
            displayForward(head);
            break;
        case 8:
            displayBackward(head);
            break;
        case 9:
            head = reverseList(head);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
    return 0;
}