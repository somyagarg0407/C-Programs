
#include <stdio.h>

int main() {
    int n, m, i, j, choice;
    int block[50], process[50], alloc[50], temp[50];

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    printf("Enter sizes of memory blocks:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &m);

    printf("Enter sizes of processes:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &process[i]);

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    for(i = 0; i < n; i++)
        temp[i] = block[i];

    for(i = 0; i < m; i++)
        alloc[i] = -1;

    if(choice < 1 || choice > 3) {
        printf("Invalid choice!\n");
        return 0;
    }

    for(i = 0; i < m; i++) {
        int idx = -1;

        for(j = 0; j < n; j++) {
            if(temp[j] >= process[i]) {
                if(choice == 1) {
                    idx = j;
                    break;
                }

                if(choice == 2 && (idx == -1 || temp[j] < temp[idx]))
                    idx = j;

                if(choice == 3 && (idx == -1 || temp[j] > temp[idx]))
                    idx = j;
            }
        }

        if(idx != -1) {
            alloc[i] = idx;
            temp[idx] -= process[i];
        }
    }

    printf("\nProcess\tSize\tBlock\n");

    for(i = 0; i < m; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);

        if(alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }

    printf("\nRemaining Memory Blocks:\n");

    for(i = 0; i < n; i++)
        printf("Block %d: %d KB\n", i + 1, temp[i]);

    return 0;
}
