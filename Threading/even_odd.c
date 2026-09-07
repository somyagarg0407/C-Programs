#include <stdio.h>
#include <pthread.h>

void *printEven(void *arg)
{
    int N = *(int *)arg;

    printf("Even numbers: ");

    for (int i = 2; i <= N; i += 2)
    {
        printf("%d ", i);
    }

    printf("\n");

    return NULL; // Return NULL to indicate successful completion
}

void *printOdd(void *arg)
{
    int N = *(int *)arg;

    printf("Odd numbers: ");

    for (int i = 1; i <= N; i += 2)
    {
        printf("%d ", i);
    }

    printf("\n");

    return NULL;
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_t evenThread; // Thread identifier for even numbers
    pthread_t oddThread; // Thread identifier for odd numbers

    // Create even thread
    pthread_create(&evenThread, NULL, printEven, &N);

    // Create odd thread
    pthread_create(&oddThread, NULL, printOdd, &N);

    // Wait for both threads
    pthread_join(evenThread, NULL);
    pthread_join(oddThread, NULL);

    printf("Both threads finished.\n");

    return 0;
}