#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int data;
    struct node *next;
};
struct node *head = NULL;
void insert_at_end(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
        return;
    }
    struct node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
}
void delete_at_beg()
{
    if (head == NULL)
    {
        printf("List is empty :( \n");
        return;
    }
    struct node *temp = head;
    head = head->next;
    free(temp);
}
void display()
{
    if (head == NULL)
    {
        printf("Enter the list is empty :( \n");
        return;
    }

    struct node *temp = head;
    while (temp != NULL)
    {
        1

            printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL");
}
int main()
{
    int choice, pos, value;
    while (1)
    {

        printf("\n1.Insertion ");
        printf("\n2.Deletion ");
        printf("\n3.Display the Queue ");
        printf("\n0.Exit\n");
        printf("Enter the choice!\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the value of element to be inserted \n");
            scanf("%d", &value);
            insert_at_end(value);
            break;

        case 2:
            delete_at_beg();
            break;

        case 3:
            display();
            break;

        case 0:
            exit(0); //-----------From #include <stdlib.h>------  and -------------zero in it means to normal termination--------

        default:
            printf("Invalid Choice\n");
        }
    }
    return 0;
}