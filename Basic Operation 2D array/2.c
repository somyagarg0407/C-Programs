#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int a[10][10];
    int r,c,i,j;
    int sum=0;

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
        for(j=0;j<c;j++)
        {
            sum+=a[i][j];
        }
    }


    printf("Sum of all elements of matrices are: %d",sum);



    return 0;
}