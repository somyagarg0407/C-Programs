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

    int max=a[0][0];
    int min=a[0][0];

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(a[i][j]>max){
                max=a[i][j];
            }
        }
    }

     for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(a[i][j]<min){
                min=a[i][j];
            }
        }
    }

    printf("Maximum of all elements is %d \n",max);
    printf("Minimum of all elements is %d \n",min);



    return 0;
}