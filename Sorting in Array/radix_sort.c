#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMax(int arr[], int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

void countSort(int arr[], int n, int exp)
{
    int output[100];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int main()
{
    int n;
    int arr[100];

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    srand(time(NULL));

    printf("\nGenerated Array:\n");
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        printf("%d ", arr[i]);
    }

    clock_t start = clock();

    radixSort(arr, n);

    clock_t end = clock();

    printf("\n\nSorted Array:\n");
    printArray(arr, n);

    double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\n\nTime taken by Radix Sort: %f milliseconds\n", time_spent);

    return 0;
}