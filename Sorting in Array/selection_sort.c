#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    clock_t start = clock();

    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }

        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    clock_t end = clock();

    printf("\n\nSorted Array:\n");
    printArray(arr, n);

    double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\n\nTime taken by Selection Sort: %f milliseconds\n", time_spent);

    return 0;
}