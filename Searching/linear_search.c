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
        nums[i] = rand() % 100;   // Random numbers from 0 to 99
        printf("%d ", nums[i]);
    }

    printf("\n\nEnter the key element to search: ");
    scanf("%d", &key);

    clock_t start = clock();

    int found = 0;

    for (int i = 0; i < n; i++)
    {
        if (nums[i] == key)
        {
            printf("\nKey Element found at index %d :)\n", i);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nKey element not found :(\n");
    }

    clock_t end = clock();

    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Time taken by the program: %f milliseconds\n", time_spent);

    return 0;
}