#include <stdio.h>
#include <time.h>
#define MAX 100
int main()
{
    int n,w[MAX],v[MAX],dp[MAX][MAX],selected[MAX];
    int capacity,i,j;
    clock_t start,end;
    double time_taken;
    printf("Enter the number of items: ");
    scanf("%d",&n);
    printf("Enter the weights of the items: ");
    for(i=1;i<=n;i++)
        scanf("%d",&w[i]);
    printf("Enter the values of the items: ");
    for(i=1;i<=n;i++)
        scanf("%d",&v[i]);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d",&capacity);
    start=clock();
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=capacity;j++)
        {
            if(i==0||j==0)
                dp[i][j]=0;
            else if(w[i]<=j)
            {
                int include=v[i]+dp[i-1][j-w[i]];
                int exclude=dp[i-1][j];
                dp[i][j]=(include>exclude)?include:exclude;
            }
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    end=clock();
    time_taken=(double)(end-start)/CLOCKS_PER_SEC;
    printf("\nMaximum Profit: %d\n",dp[n][capacity]);
    for(i=1;i<=n;i++)
        selected[i]=0;
    i=n;
    j=capacity;
    while(i>0&&j>0)
    {
        if(dp[i][j]!=dp[i-1][j])
        {
            selected[i]=1;
            j-=w[i];
        }
        i--;
    }
    printf("\nSelected Items:\n");
    printf("Item\tWeight\tValue\n");
    for(i=1;i<=n;i++)
    {
        if(selected[i])
            printf("%d\t%d\t%d\n",i,w[i],v[i]);
    }
    printf("\nDynamic Programming Table:\n");
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=capacity;j++)
            printf("%3d",dp[i][j]);
        printf("\n");
    }
    printf("\nExecution Time (Knapsack Algorithm): %.6f seconds\n",time_taken);
    return 0;
}