#include <stdio.h>
void merge(int a[],int l,int m,int r){
    int i=l,j=m+1,k=0,temp[100];
    while(i<=m&&j<=r){
        if(a[i]<a[j]) temp[k++]=a[i++];
        else temp[k++]=a[j++];
    }
    while(i<=m) temp[k++]=a[i++];
    while(j<=r) temp[k++]=a[j++];
    for(i=l,k=0;i<=r;i++,k++) a[i]=temp[k];
}
void mergeSort(int a[],int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(a,l,m);
        mergeSort(a,m+1,r);
        merge(a,l,m,r);
    }
}
int main(){
    int n,i,a[100];
    printf("Enter number of elements: ");
    scanf("%d",&n);
    printf("Enter elements: ");
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    mergeSort(a,0,n-1);
    printf("Sorted array: ");
    for(i=0;i<n;i++) printf("%d ",a[i]);
    return 0;
}