#include <stdio.h>
#define MAX 100

int stack[MAX], top = -1;

void push(int data)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top] = data;
    printf("Pushed: %d\n", data);
}

void pop()
{
    if (top == -1)
    {
        printf("Stack Underflow!\n");
        return;
    }
    printf("Popped: %d\n", stack[top--]);
}

void peek()
{
    if (top == -1)
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", stack[top]);
}

void display()
{
    if (top == -1)
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack (top to bottom): ");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
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