#include<stdio.h>

int main(){
    int Bin;

    printf("Enter binary number:");
    scanf("%d",&Bin);
    int rem;
    int Dec=0;
    int pow=1;

    while(Bin>0){
        rem=Bin%10;
        Bin=Bin/10;
        Dec+=(rem*pow);
        pow*=2;

    }    
    
    printf("Your decimal number : %d \n",Dec);
    return 0;

}