#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Include the pthread library for threading functions

void *printHello(void *arg)
{
    int thread_id = *(int *)arg; // left star="Go to that address and give me the integer stored there."

    printf("Hello from Thread %d\n", thread_id); 

    return NULL;
}

int main()
{
    int N;

    printf("Enter number of threads: ");
    scanf("%d", &N);

    pthread_t threads[N];// Array to hold thread identifiers
    int thread_id[N]; // Array to hold thread IDs

    // Create N threads
    for (int i = 0; i < N; i++)
    {
        thread_id[i] = i + 1;

        pthread_create( // Create a new thread
            &threads[i],
            NULL,
            printHello,
            &thread_id[i]
        );
    }

    // Wait for all threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL); // Wait for the thread to finish
    }

    printf("All threads have finished.\n");

    return 0;
}