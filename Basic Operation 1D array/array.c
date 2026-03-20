#include <stdio.h> 


int main(){ 

int arr[100],n,i,pos,value,choice; 

printf("Enter number of elements: "); 
scanf("%d",&n); 

printf("Enter array elements:\n"); 

for(i=0;i<n;i++){ 
scanf("%d",&arr[i]); 
} 

while(1){ 
printf("\n1.Traversal\n2.Insertion\n3.Deletion\n4.Exit\n"); 
printf("Enter your choice: "); 
scanf("%d",&choice); 
switch(choice){ 
case 1:{ 
printf("Array elements are:\n"); 
for(i=0;i<n;i++){ 
printf("%d ",arr[i]); 
} 
break; 
} 
case 2:{ 
printf("Enter position to insert: "); 
scanf("%d",&pos); 
pos=pos-1;
printf("Enter value to insert: "); 
scanf("%d",&value); 
for(i=n;i>pos;i--){ 
arr[i]=arr[i-1]; 
} 
arr[pos]=value; 
n++; 
printf("Insertion successful\n"); 
break; 
} 
case 3:{ 
printf("Enter position to delete: "); 
scanf("%d",&pos); 
pos=pos-1;
for(i=pos;i<n-1;i++){ 
arr[i]=arr[i+1]; 
} 
n--; 
printf("Deletion successful\n"); 
break; 
} 
case 4: 
return 0; 
default: 
printf("Invalid choice\n");} 
} 
return 0; 
} 