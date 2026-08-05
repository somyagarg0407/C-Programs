#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void countingSort(int arr[], int n) {
    int mx = arr[0];
    for(int i = 1; i < n; i++) if(arr[i] > mx) mx = arr[i];

    int count[mx + 1] = {0};

    for(int i = 0; i < n; i++) count[arr[i]]++;
    int k = 0;

    for(int i = 0; i <= mx; i++)
        while(count[i]--) arr[k++] = i;
}

int main() {
    int n;
    cin >> n;
    int arr[n];

    srand(time(0));
    for(int i = 0; i < n; i++) arr[i] = rand() % 1000;

    clock_t start = clock();
    countingSort(arr, n);
    clock_t end = clock();

    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nTime Taken: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds";

    return 0;
}