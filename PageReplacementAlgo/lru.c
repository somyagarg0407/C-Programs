#include <stdio.h>
int main()
{
    int pages[50], frames[10], lastUsed[10];
    int n, f, i, j;
    int pageFaults = 0, found, lru;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &f);
    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }
    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < n; i++)
    {
        found = 0;
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }
        if (found == 0)
        {
            lru = 0;
            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    lru = j;
                    break;
                }
                if (lastUsed[j] < lastUsed[lru])
                {
                    lru = j;
                }
            }
            frames[lru] = pages[i];
            lastUsed[lru] = i;
            pageFaults++;
        }
        printf("%d\t", pages[i]);
        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        if (found == 0)
            printf("\tPage Fault");
        else
            printf("\tHit");
        printf("\n");
    }
    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", n - pageFaults);
    return 0;
}
