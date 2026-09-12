#include <stdio.h>

int main()
{
    int n, i, j, time = 0, min;
    int at[20], bt[20], ct[20], tat[20], wt[20], rt[20], done[20] = {0}; // imp
    char pid[20][5];
    float awt = 0, atat = 0, art = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
        scanf("%s %d %d", pid[i], &at[i], &bt[i]);

    for(i = 0; i < n; i++)
    {
        min = -1;

        for(j = 0; j < n; j++)
        {
            if(!done[j] && at[j] <= time &&
               (min == -1 || bt[j] < bt[min])) // -----------IMP---------
                min = j;
        }

        if(min == -1)
        {
            time++;
            i--;
            continue;
        }

        rt[min] = time - at[min];
        time = time + bt[min];

        ct[min] = time;
        tat[min] = ct[min] - at[min];
        wt[min] = tat[min] - bt[min];

        awt += wt[min];
        atat += tat[min];
        art += rt[min];

        done[min] = 1;
    }

    printf("\nSJF\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    printf("\nAverage WT = %.2f", awt/n);
    printf("\nAverage TAT = %.2f", atat/n);
    printf("\nAverage RT = %.2f\n", art/n);

    return 0;
}