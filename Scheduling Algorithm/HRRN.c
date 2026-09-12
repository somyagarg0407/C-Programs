#include <stdio.h>

int main()
{
    int n, i, j, time = 0, done = 0, max;
    int at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int finished[20] = {0};
    char pid[20][5];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
        scanf("%s %d %d", pid[i], &at[i], &bt[i]);

    while(done < n)
    {
        max = -1;
        float ratio, maxRatio = -1;

        for(j = 0; j < n; j++)
        {
            if(!finished[j] && at[j] <= time)
            {
                wt[j] = time - at[j]; // ----- yahan ye alag hai -------
                ratio = (float)(wt[j] + bt[j]) / bt[j];

                if(ratio > maxRatio)
                {
                    maxRatio = ratio;
                    max = j;
                }
            }
        }

        if(max == -1)
        {
            time++;
            continue;
        }

        rt[max] = time - at[max];
        time += bt[max];

        ct[max] = time;
        tat[max] = ct[max] - at[max];
        wt[max] = tat[max] - bt[max];

        finished[max] = 1;
        done++;
    }

    printf("\nHRRN\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    float awt = 0, atat = 0, art = 0;

    for(i = 0; i < n; i++)
    {
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