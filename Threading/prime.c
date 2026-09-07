#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BLOCK_SIZE 100 // Define the block size for each thread to process

// Structure to store information for each thread
struct ThreadData
{
    int id;
    int start;
    int end;
    int primes[100];
    int count;
};

// Function to check whether a number is prime
int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

// Function executed by each thread
void *findPrimes(void *arg)
{
    struct ThreadData *data = (struct ThreadData *)arg;

    data->count = 0;

    for (int i = data->start; i <= data->end; i++)
    {
        if (isPrime(i))
        {
            data->primes[data->count] = i; // Store the prime number in the array
            data->count++;// Increment the count of prime numbers found
        }
    }

    return NULL;
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    // Number of threads required
    int numThreads = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;

    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    struct ThreadData *data =
        malloc(numThreads * sizeof(struct ThreadData));

    // ---------------- SEQUENTIAL ----------------

    clock_t startSeq = clock();

    int sequentialPrimes[100000];
    int seqCount = 0;

    for (int i = 1; i <= N; i++)
    {
        if (isPrime(i))
        {
            sequentialPrimes[seqCount++] = i;
        }
    }

    clock_t endSeq = clock();

    double sequentialTime =
        (double)(endSeq - startSeq) / CLOCKS_PER_SEC;

    // ---------------- MULTITHREADED ----------------

    struct timespec startMulti, endMulti;

    clock_gettime(CLOCK_MONOTONIC, &startMulti);

    // Create threads
    for (int i = 0; i < numThreads; i++)
    {
        data[i].id = i + 1;

        data[i].start = i * BLOCK_SIZE + 1;

        data[i].end = (i + 1) * BLOCK_SIZE;

        if (data[i].end > N)
            data[i].end = N;

        pthread_create(
            &threads[i],
            NULL,
            findPrimes,
            &data[i]
        );
    }

    // Wait for all threads
    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &endMulti);

    double multithreadTime =
        (endMulti.tv_sec - startMulti.tv_sec) +
        (endMulti.tv_nsec - startMulti.tv_nsec) / 1e9;

    // ---------------- OUTPUT ----------------

    printf("\nPrime numbers:\n");

    for (int i = 0; i < numThreads; i++)
    {
        for (int j = 0; j < data[i].count; j++)
        {
            printf("%d ", data[i].primes[j]);
        }
    }

    printf("\n\nSequential time     : %f seconds\n",
           sequentialTime);

    printf("Multithreaded time  : %f seconds\n",
           multithreadTime);

    // Free memory
    free(threads);
    free(data);

    return 0;
}