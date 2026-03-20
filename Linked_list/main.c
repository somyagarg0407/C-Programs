#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

void insert_at_beg(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = head;
    head = newnode;
}

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

void insert_at_position(int value, int pos)
{
    if (pos == 1)
    {
        insert_at_beg(value);
        return;
    }

    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = value;
    struct node *temp = head;

    for (int i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Insertion not possible :( \n");
        return; // ------------------------TO GET OUT OF FUNCTION AFTER THIS-------------------
    }

    newnode->next = temp->next;
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

void delete_at_end()
{
    if (head == NULL)
    {
        printf("List is empty :( \n");
        return;
    }

    if (head->next == NULL)
    { // there is only one element in list
        free(head);
        head = NULL; //-------This is very importnat step to avoid dangling pointer !!!!!!!!--------
        return;
    }

    struct node *temp = head;

    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL; //-------for the last node very important !!!------------
}

void delete_at_position(int pos)
{
    if (head == NULL)
    {
        printf("List is empty :( \n");
        return;
    }

    if (pos == 1)
    {
        delete_at_beg();
        return;
    }

    struct node *temp = head;

    for (int i = 1; i < pos - 1 && temp->next != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        printf("Invalid position :( \n");
        return;
    }

    struct node *del = temp->next; //-----------------VERY IMPORTANT---------------
    temp->next = del->next;
    free(del);
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
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL !");
}

void reverse()
{ //------------------GOATED!!!------------------
    struct node *prev = NULL;
    struct node *current = head;
    struct node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

int main()
{
    int choice, pos, value;

    while (1)
    {
        printf("\n1.Insert at Beginning ");
        printf("\n2.Insert at End ");
        printf("\n3.Insert at Specific postion ");
        printf("\n4.Delete at Beginning ");
        printf("\n5.Delete at End ");
        printf("\n6.Delete at specific position ");
        printf("\n7.Display the Linked list ");
        printf("\n8.Reverse the Linked list ");
        printf("\n0.Exit\n");

        printf("Enter the choice!\n");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            printf("Enter the value of element to be inserted \n");
            scanf("%d", &value);
            insert_at_beg(value);
            break;

        case 2:
            printf("Enter the value of element to be inserted \n");
            scanf("%d", &value);
            insert_at_end(value);
            break;

        case 3:
            printf("Enter the value of element to be inserted and the position on which it will inserted \n");
            scanf("%d %d", &value, &pos);
            insert_at_position(value, pos);
            break;

        case 4:
            delete_at_beg();
            break;

        case 5:
            delete_at_end();
            break;

        case 6:
            printf("Enter position at which the element will be deleted \n: ");
            scanf("%d", &pos);
            delete_at_position(pos);
            break;

        case 7:
            display();
            break;

        case 8:
            reverse();
            break;

        case 0:
            exit(0); //-----------From #include <stdlib.h>------  and -------------zero in it means to normal termination--------

        default:
            printf("Invalid Choice\n");
        }
    }

    return 0;
}
