#include <stdio.h>

int main()
{
    int n, i, time = 0;
    int at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    char pid[20][5]; // IMP
    float awt = 0, atat = 0, art = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter PID, AT and BT: ");
        scanf("%s %d %d", pid[i], &at[i], &bt[i]);
    }

    for(i = 0; i < n; i++)
    {
        if(time < at[i]) // for idle space
            time = at[i];

        rt[i] = time - at[i];
        time = time + bt[i];

        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        awt += wt[i];
        atat += tat[i];
        art += rt[i];
    }

    printf("\nFCFS\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    printf("\nAverage WT = %.2f", awt/n);
    printf("\nAverage TAT = %.2f", atat/n);
    printf("\nAverage RT = %.2f\n", art/n);

    return 0;
}