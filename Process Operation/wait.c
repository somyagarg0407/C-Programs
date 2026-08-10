#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
int main()
{
    pid_t pid = fork();
    if (pid == 0)
        printf("Child Process\n");
    else
    {
        wait(NULL);
        printf("Parent Process\n");
    }
    return 0;
}