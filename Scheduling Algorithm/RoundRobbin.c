#include <stdio.h>

int main()
{
    int n, tq, i, time = 0, done = 0;
    int at[20], bt[20], rem[20], ct[20], tat[20], wt[20], rt[20];
    int q[100], front = 0, rear = 0, added[20] = {0};
    char pid[20][5];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for(i = 0; i < n; i++)
    {
        scanf("%s %d %d", pid[i], &at[i], &bt[i]);
        rem[i] = bt[i];
        rt[i] = -1;
    }

    q[rear++] = 0;
    added[0] = 1;

    while(done < n)
    {
        if(front == rear)
        {
            time++;
            for(i = 0; i < n; i++)
                if(!added[i] && at[i] <= time)
                {
                    q[rear++] = i;
                    added[i] = 1;
                }
            continue;
        }

        i = q[front++];

        if(rt[i] == -1)
            rt[i] = time - at[i];

        int run = (rem[i] < tq) ? rem[i] : tq;

        time += run;
        rem[i] -= run;

        for(int j = 0; j < n; j++)
            if(!added[j] && at[j] <= time)
            {
                q[rear++] = j;
                added[j] = 1;
            }

        if(rem[i] > 0)
            q[rear++] = i;
        else
        {
            ct[i] = time;
            done++;
        }
    }

    printf("\nRR\n");
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