#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }

char pop() { return stack[top--]; }

char peek() { return stack[top]; }

int isEmpty() { return top == -1; }

int precedence(char c)
{
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

void infixToPostfix(char *infix, char *postfix)
{
    int j = 0;
    for (int i = 0; i < strlen(infix); i++)
    {
        char c = infix[i];
        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (!isEmpty() && peek() != '(')
                postfix[j++] = pop();
            if (!isEmpty())
                pop();
        }
        else if (isOperator(c))
        {
            while (!isEmpty() && precedence(peek()) >= precedence(c) && c != '^')
                postfix[j++] = pop();
            push(c);
        }
    }
    while (!isEmpty())
        postfix[j++] = pop();
    postfix[j] = '\0';
}

int main()
{
    char infix[MAX], postfix[MAX];
    printf("=== Infix to Postfix Converter ===\n");
    do
    {
        printf("\nEnter infix expression (0 to exit): ");
        scanf("%s", infix);
        if (infix[0] == '0' && strlen(infix) == 1)
            break;
        top = -1;
        infixToPostfix(infix, postfix);
        printf("Infix:   %s\n", infix);
        printf("Postfix: %s\n", postfix);
    } while (1);
    printf("Exiting...\n");
    return 0;
}