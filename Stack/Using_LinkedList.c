#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *top = NULL;

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(int data)
{
    struct Node *newNode = createNode(data);
    newNode->next = top;
    top = newNode;
    printf("Pushed: %d\n", data);
}

void pop()
{
    if (!top)
    {
        printf("Stack Underflow!\n");
        return;
    }
    struct Node *temp = top;
    top = top->next;
    printf("Popped: %d\n", temp->data);
    free(temp);
}

void peek()
{
    if (!top)
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}

void display()
{
    if (!top)
    {
        printf("Stack is empty!\n");
        return;
    }
    struct Node *temp = top;
    printf("Stack (top to bottom): ");
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    int choice, data;
    do
    {
        printf("\n1.Push  2.Pop  3.Peek  4.Display  0.Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            push(data);
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
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