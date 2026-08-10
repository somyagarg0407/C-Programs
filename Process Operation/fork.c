#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid = fork();
    if (pid < 0)
        printf("Fork failed\n");
    else if (pid == 0)
        printf("Child Process\n");
    else
        printf("Parent Process\n");
    return 0;
}