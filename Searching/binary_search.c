#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n;
    int nums[100];
    int key;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    srand(time(NULL));

    printf("\nGenerated Array:\n");
    for (int i = 0; i < n; i++)
    {
        nums[i] = rand() % 100;   // Random numbers between 0 and 99
        printf("%d ", nums[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    printf("\n\nSorted Array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }

    printf("\n\nEnter the key element to search: ");
    scanf("%d", &key);

    int low = 0;
    int high = n - 1;

    clock_t start = clock();

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (nums[mid] == key)
        {
            printf("\nKey element found at index %d\n", mid);
            break;
        }
        else if (nums[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (low > high)
    {
        printf("\nKey element not found.\n");
    }

    clock_t end = clock();

    double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("Time taken: %f milliseconds\n", time_spent);

    return 0;
}