#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
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
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    clock_t start = clock();

    heapSort(arr, n);

    clock_t end = clock();

    printf("\n\nSorted Array:\n");
    printArray(arr, n);

    double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\n\nTime taken by Heap Sort: %f milliseconds\n", time_spent);

    return 0;
}