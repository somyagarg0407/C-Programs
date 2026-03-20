#include<stdio.h>

int main(){

    int Bin=0;
    int pow=1;
    int Dec;
    
    printf("enter decimal number:");
    scanf("%d",&Dec);
    int rem;

    while(Dec>0){
        rem=Dec%2;
        Dec=Dec/2;
        Bin+=(rem*pow);
        pow*=10; 

    }

    printf("binary number is : %d",Bin);

    return 0;


}