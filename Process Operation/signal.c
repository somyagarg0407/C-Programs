#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig)
{
    printf("Signal received\n");
}
int main()
{
    signal(SIGINT, handler);
    printf("Press Ctrl+C\n");
    while (1)
        sleep(1);
    return 0;
}