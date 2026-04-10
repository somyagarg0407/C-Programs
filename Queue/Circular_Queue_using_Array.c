
#include <stdio.h>

int main()
{

    int n = 0;
    printf("Enter the size of Queue: \n");
    scanf("%d", &n);
    int arr[n + 5];
    printf("Now give the values of all input for queue\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int front = 0;
    int rear = n - 1;
    while (1)
    {
        int choice = 0;
        printf("Choose a number from 1,2,3\n");
        scanf("%d", &choice);
        if (choice == 1)
        { // perform insertion
            int value;
            if (front == rear + 1 || (front == 0 && rear == n - 1))
            {
                printf("Insertion not possible :(\n");
            }
            else if (front == -1)
            {
                printf("Now enter the value you want to insert\n");
                scanf("%d", &value);
                arr[rear] = value;
                front = rear = 0;
                printf("Insertion Successful !\n");
            }
            else
            {
                printf("Now enter the value you want to insert\n");
                scanf("%d", &value);
                arr[n] = value;
                rear++;
                printf("Insertion Successful !\n");
            }
        }

        if (choice == 2)
        { // perfrom deletion
            if (front == rear)
            {
                front = -1;
                rear = -1;
                printf("Deletion Successful !\n");
            }
            else if (front == -1)
            {
                printf("Deletion not possible :( \n");
            }
            else
            {
                front++;
                printf("Deletion Successful !\n");
            }
        }

        if (choice == 3)
        {
            ; // perfrom Display
            for (int i = front; i < rear; i++)
            {
                printf("arr[i] \n");
            }
        }
    }
    return 0;
}