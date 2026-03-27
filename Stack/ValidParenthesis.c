#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char nums[30];
    char stack[30];
    int top = -1;

    printf("Now enter Expression ! \n ");

    for (int i = 0; i < 30; i++)
    {
        scanf(" %c", &nums[i]);
        if (nums[i] == '=')
        {
            break;
        }
    }

    for (int i = 0; i < 30; i++)
    {
        if (nums[i] == '(' || nums[i] == '{' || nums[i] == '[')
        {
            if (top == 29)
            {
                printf("Stack Overflow!\n");
                break;
            }
            stack[++top] = nums[i];
        }

        else if (nums[i] == ')' || nums[i] == '}' || nums[i] == ']')
        {
            if (top == -1)
            {
                printf("expression is not balanced :(");
                return 1;
            }

            if ((stack[top] == '(' && nums[i] == ')') || (stack[top] == '{' && nums[i] == '}') || (stack[top] == '[' && nums[i] == ']'))
            {
                if (top == -1)
                {
                    printf("Stack Underflow!\n");
                    break;
                }

                else
                {
                    top--;
                }
            }

            else if ((stack[top] != '(' && nums[i] == ')') || (stack[top] != '{' && nums[i] == '}') || (stack[top] != '[' && nums[i] == ']'))
            {
                printf("expression is not balanced :(");
                return 1;
            }
        }
    }

    if (top == -1)
    {
        printf("Expression is balanced :)");
    }

    else
    {
        printf("Expression is not Balanced :(");
    }

    return 0;
}