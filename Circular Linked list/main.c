#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
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
    newNode->next = newNode;
    return newNode;
}

struct Node *createList(int data)
{
    return createNode(data);
}

struct Node *insertAtBeginning(struct Node *last, int data)
{
    struct Node *newNode = createNode(data);
    if (!last)
    {
        return newNode;
    }
    newNode->next = last->next;
    last->next = newNode;
    return last;
}

struct Node *insertAtEnd(struct Node *last, int data)
{
    struct Node *newNode = createNode(data);
    if (!last)
    {
        return newNode;
    }
    newNode->next = last->next;
    last->next = newNode;
    return newNode;
}

struct Node *insertAtPosition(struct Node *last, int data, int pos)
{
    if (pos < 1)
    {
        printf("Invalid position!\n");
        return last;
    }
    if (pos == 1)
        return insertAtBeginning(last, pos), insertAtBeginning(last, data);
    struct Node *newNode = createNode(data);
    struct Node *temp = last->next;
    for (int i = 1; i < pos - 1; i++)
    {
        temp = temp->next;
        if (temp == last->next)
        {
            printf("Position out of range!\n");
            free(newNode);
            return last;
        }
    }
    newNode->next = temp->next;
    temp->next = newNode;
    if (temp == last)
        return newNode;
    return last;
}

struct Node *deleteFromBeginning(struct Node *last)
{
    if (!last)
    {
        printf("List is empty!\n");
        return NULL;
    }
    struct Node *head = last->next;
    if (head == last)
    {
        free(last);
        return NULL;
    }
    last->next = head->next;
    printf("Deleted: %d\n", head->data);
    free(head);
    return last;
}

struct Node *deleteFromEnd(struct Node *last)
{
    if (!last)
    {
        printf("List is empty!\n");
        return NULL;
    }
    struct Node *head = last->next;
    if (head == last)
    {
        printf("Deleted: %d\n", last->data);
        free(last);
        return NULL;
    }
    struct Node *temp = head;
    while (temp->next != last)
        temp = temp->next;
    temp->next = last->next;
    printf("Deleted: %d\n", last->data);
    free(last);
    return temp;
}

struct Node *deleteFromPosition(struct Node *last, int pos)
{
    if (!last)
    {
        printf("List is empty!\n");
        return NULL;
    }
    if (pos < 1)
    {
        printf("Invalid position!\n");
        return last;
    }
    if (pos == 1)
        return deleteFromBeginning(last);
    struct Node *temp = last->next;
    for (int i = 1; i < pos - 1; i++)
    {
        temp = temp->next;
        if (temp == last->next)
        {
            printf("Position out of range!\n");
            return last;
        }
    }
    struct Node *delNode = temp->next;
    if (delNode == last->next)
    {
        printf("Position out of range!\n");
        return last;
    }
    temp->next = delNode->next;
    struct Node *newLast = (delNode == last) ? temp : last;
    printf("Deleted: %d\n", delNode->data);
    free(delNode);
    return newLast;
}

void display(struct Node *last)
{
    if (!last)
    {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = last->next;
    printf("Circular Linked List: ");
    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != last->next);
    printf("(back to %d)\n", last->next->data);
}

int countNodes(struct Node *last)
{
    if (!last)
        return 0;
    int count = 1;
    struct Node *temp = last->next;
    while (temp != last)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void search(struct Node *last, int key)
{
    if (!last)
    {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = last->next;
    int pos = 1, found = 0;
    do
    {
        if (temp->data == key)
        {
            printf("Element %d found at position %d\n", key, pos);
            found = 1;
        }
        temp = temp->next;
        pos++;
    } while (temp != last->next);
    if (!found)
        printf("Element %d not found in the list\n", key);
}

int main()
{
    struct Node *last = NULL;
    int choice, data, pos;
    printf("=== Circular Singly Linked List ===\n");
    do
    {
        printf("\n1.Create  2.Insert Begin  3.Insert End  4.Insert Pos\n");
        printf("5.Del Begin  6.Del End  7.Del Pos  8.Display\n");
        printf("9.Count  10.Search  0.Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            last = createList(data);
            printf("List created with element %d\n", data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            last = insertAtBeginning(last, data);
            break;
        case 3:
            printf("Enter data: ");
            scanf("%d", &data);
            last = insertAtEnd(last, data);
            break;
        case 4:
            printf("Enter data and position: ");
            scanf("%d %d", &data, &pos);
            last = insertAtPosition(last, data, pos);
            break;
        case 5:
            last = deleteFromBeginning(last);
            break;
        case 6:
            last = deleteFromEnd(last);
            break;
        case 7:
            printf("Enter position: ");
            scanf("%d", &pos);
            last = deleteFromPosition(last, pos);
            break;
        case 8:
            display(last);
            break;
        case 9:
            printf("Total nodes: %d\n", countNodes(last));
            break;
        case 10:
            printf("Enter element to search: ");
            scanf("%d", &data);
            search(last, data);
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