#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int a[10][10];
    int r,c,i,j;

    printf("Enter the number of rows and columns respectively: ");
    scanf("%d %d",&r,&c);

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
        int rowsum=0;
        for(j=0;j<c;j++)
        {
            rowsum+=a[i][j];
        }
        printf("sum of elements of %d row is %d\n",i+1,rowsum);
    }

    for(j=0;j<c;j++)
    {
        int colsum=0;
        for(i=0;i<r;i++)
        {
            colsum+=a[i][j];
        }
        printf("sum of elements of %d column is %d\n",j+1,colsum);
    }



    return 0;
}