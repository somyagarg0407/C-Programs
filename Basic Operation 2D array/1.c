#include <stdio.h>


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

        printf("Matrix is: \n");

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("  %d",a[i][j]);
        }
        printf("\n");
    }


    return 0;
}