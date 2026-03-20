#include <stdio.h>

int main() {
    int r,c,i,j;
    printf("Enter the number of rows and columns respectively: ");
    scanf("%d %d",&r,&c);
    int a[r][c];
    int t[c][r];
    int m[r][r];

    printf("Enter the elements of matrices:\n");

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    for(i=0;i<r;i++)
    {
        for(j=0;j<r;j++)
        {
            m[i][j]=0;
        }
    }

    for(j=0;j<c;j++)
    {
        for(i=0;i<r;i++)
        {
            t[j][i]=a[i][j];
        }
    }
    
     for(i=0;i<r;i++)
    {
        for(j=0;j<r;j++)
        {
           for(int k=0;k<c;k++)
           {
            m[i][j]+=a[i][k]*t[k][j];
           }
        }
    }
    
    printf(" Multiplied matrix is :\n");
    for(i=0;i<r;i++)
    {
        for(j=0;j<r;j++)
        {
            printf("  %d",m[i][j]);
        }
        printf("\n");
    }

    return 0;
}