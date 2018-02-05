#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(int *arr, int *pos, int low, int high) {
    int pivot = arr[high];
    int i = low - 1, j;

    for(j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            swap(&arr[i+1], &arr[j]);
            swap(&pos[i+1], &pos[j]);
            i += 1;
        }
    }

    swap(&arr[i+1], &arr[high]);
    swap(&pos[i+1], &pos[high]);
    return i + 1;
}

void quickSort(int *arr, int *pos, int low, int high) {
    if(low < high) {
        int pivot = partition(arr, pos, low, high);
        quickSort(arr, pos, low, pivot-1);
        quickSort(arr, pos, pivot+1, high);
    }
}

void printArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%02d ", arr[i]);
    }
    printf("\n");
}

void generateArray(int **arr, int **pos, int n) {
    int i;
    *arr = (int *) malloc(n * sizeof(int));
    *pos = (int *) malloc(n * sizeof(int));
    srand(time(0));
    
    for(i = 0; i < n; i++) {
        (*arr)[i] = rand() % MOD;
        (*pos)[i] = i;
    }
}

int binarySearch(int *arr, int n, int key) {
    int low = 0, high = n-1, mid;

    while(low < high) {
        mid = (low + high) / 2;
        if(arr[mid] == key) {
            return mid;
        } else if(arr[mid] < key) {
            low = mid + 1;
        } else if(arr[mid] > key) {
            high = mid - 1;
        }
    }

    if(key == arr[low] || key == arr[high]) {
        return (key == arr[low])? low : high;
    }

    return -1;
}

int main() {
    int *arr, *pos, n, key, idx1, idx2;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    generateArray(&arr, &pos, n);
    printf("Array: ");
    printArray(arr, n);
    printf("Index: ");
    printArray(pos, n);

    printf("\nSorted Array\n");
    quickSort(arr, pos, 0, n-1);
    printf("Array: ");
    printArray(arr, n);
    printf("Index: ");
    printArray(pos, n);

    printf("\nEnter a key to find: ");
    scanf("%d", &key);

    idx2 = binarySearch(arr, n, key);
    idx1 = (idx2 >= 0)? pos[idx2] : -1;
    printf("\nOriginal Index: %d\n", idx1);
    printf("New Index: %d\n", idx2);

    return 0;
}