#include <stdio.h>

int main()
{
    int n, i, time = 0, done = 0, min;
    int at[20], bt[20], rem[20], ct[20], tat[20], wt[20], rt[20];
    int started[20] = {0};
    char pid[20][5];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        scanf("%s %d %d", pid[i], &at[i], &bt[i]);
        rem[i] = bt[i];
        rt[i] = -1; // -----IMP-----
    }

    while(done < n)
    {
        min = -1;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rem[i] > 0 &&
              (min == -1 || rem[i] < rem[min]))
                min = i;
        }

        if(min == -1)
        {
            time++;
            continue;
        }

        if(rt[min] == -1)
            rt[min] = time - at[min];

        rem[min]--;
        time++;

        if(rem[min] == 0)
        {
            ct[min] = time;
            done++;
        }
    }

    printf("\nSRTF\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    float awt = 0, atat = 0, art = 0;

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        awt += wt[i];
        atat += tat[i];
        art += rt[i];

        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i],
               tat[i], wt[i], rt[i]);
    }

    printf("\nAverage WT = %.2f", awt/n);
    printf("\nAverage TAT = %.2f", atat/n);
    printf("\nAverage RT = %.2f\n", art/n);

    return 0;
}