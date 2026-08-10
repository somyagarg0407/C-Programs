#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Child Process\n");
        exit(10);
    }
    else
    {
        int status;
        wait(&status);
        if (WIFEXITED(status))
            printf("Child returned %d\n", WEXITSTATUS(status));
    }
    return 0;
}