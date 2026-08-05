#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

void bucketSort(int arr[], int n) {
    vector<int> bucket[10];

    for(int i = 0; i < n; i++)
        bucket[arr[i] / 100].push_back(arr[i]);

    int k = 0;

    for(int i = 0; i < 10; i++) {
        sort(bucket[i].begin(), bucket[i].end());
        for(int x : bucket[i]) arr[k++] = x;
    }
}

int main() {
    int n;
    cin >> n;
    int arr[n];

    srand(time(0));
    for(int i = 0; i < n; i++) arr[i] = rand() % 1000;

    clock_t start = clock();
    bucketSort(arr, n);
    clock_t end = clock();

    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nTime Taken: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds";

    return 0;
}