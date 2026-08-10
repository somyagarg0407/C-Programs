#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("Before execlp\n");
    execlp("ls", "ls", "-l", NULL);
    printf("execlp failed\n");
    return 0;
}