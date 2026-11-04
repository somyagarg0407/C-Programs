#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 100
int main()
{
    char X[MAX],Y[MAX],LCS[MAX];
    int dp[MAX][MAX],m,n,i,j,index;
    clock_t start,end;
    double time_taken;
    printf("Enter the first sequence: ");
    scanf("%99s",X);
    printf("Enter the second sequence: ");
    scanf("%99s",Y);
    m=strlen(X);
    n=strlen(Y);
    start=clock();
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            if(i==0||j==0)
                dp[i][j]=0;
            else if(X[i-1]==Y[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=(dp[i-1][j]>dp[i][j-1])?dp[i-1][j]:dp[i][j-1];
        }
    }
    index=dp[m][n];
    LCS[index]='\0';
    i=m;
    j=n;
    while(i>0&&j>0)
    {
        if(X[i-1]==Y[j-1])
        {
            LCS[index-1]=X[i-1];
            i--;
            j--;
            index--;
        }
        else if(dp[i-1][j]>=dp[i][j-1])
            i--;
        else
            j--;
    }
    end=clock();
    time_taken=(double)(end-start)/CLOCKS_PER_SEC;
    printf("\nLongest Common Subsequence (LCS):\n");
    printf("Length of LCS: %d\n",dp[m][n]);
    printf("LCS: %s\n",LCS);
    printf("\nDynamic Programming Table:\n");
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
            printf("%3d",dp[i][j]);
        printf("\n");
    }
    printf("\nExecution Time (LCS Algorithm): %.6f seconds\n",time_taken);
    return 0;
}