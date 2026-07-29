#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n;
    int nums[100];

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    srand(time(NULL));

    printf("\nGenerated Array:\n");
    for (int i = 0; i < n; i++)
    {
        nums[i] = rand() % 100;  
        printf("%d ", nums[i]);
    }

    clock_t start = clock();

    for (int i = 1; i < n; i++)
    {
        int key = nums[i];
        int j = i - 1;

        while (j >= 0 && nums[j] > key)
        {
            nums[j + 1] = nums[j];
            j--;
        }

        nums[j + 1] = key;
    }

    clock_t end = clock();

    printf("\n\nSorted Array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }

    double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\n\nTime taken by Insertion Sort: %f milliseconds\n", time_spent);

    return 0;
}