#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void merge(int **arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1][2], R[n2][2];

    for(i = 0; i < n1; i++) {
        L[i][0] = arr[l+i][0];
        L[i][1] = arr[l+i][1];
    }

    for(j = 0; j < n2; j++) {
        R[j][0] = arr[m+1+j][0];
        R[j][1] = arr[m+1+j][1];
    }

    i = j = 0;
    k = l;

    while(i < n1 && j < n2) {
        if(L[i][1] <= R[j][1]) {
            arr[k][0] = L[i][0];
            arr[k][1] = L[i][1];
            i++;
        } else {
            arr[k][0] = R[j][0];
            arr[k][1] = R[j][1];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k][0] = L[i][0];
        arr[k][1] = L[i][1];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k][0] = R[j][0];
        arr[k][1] = R[j][1];
        j++;
        k++;
    }
}

void mergeSort(int **arr, int l, int r) {

    if(l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int binarySearch(int **arr, int n, int key) {
    int l = 0, r = n-1, m;

    while(l <= r) {
        m = (l + r) / 2;
        if(arr[m][1] == key) {
            return m;
        } else if(arr[m][1] < key) {
            l = m + 1;
        } else if(arr[m][1] > key) {
            r = m - 1;
        }
    }

    return -1;
}

int getStartingIdx(int **arr, int n, int k) {
    int i;
    for(i = k; i >= 0 && arr[i][1] == arr[k][1]; i--);
    return i + 1;
}

void printArray(int **arr, int n, int k) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%02d ", arr[i][k]);
    }
    printf("\n");
    
}

int ** generateArray(int n) {
    int i;
    int **arr = (int **) malloc(n * sizeof(int *));
    srand(time(0));
    
    for(i = 0; i < n; i++) {
        arr[i] = (int *) malloc(2 * sizeof(int));
        arr[i][0] = i;
        arr[i][1] = rand() % MOD;
    }
    
    return arr;
}

int main() {
    int **arr, n, key, idx;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    arr = generateArray(n);
    printf("%sIndex: ", BLU);
    printArray(arr, n, 0);
    printf("%sArray: ", YEL);
    printArray(arr, n, 1);

    printf("\n%sSorted Array\n", RESET);
    mergeSort(arr, 0, n-1);
    printf("%sIndex: ", CYN);
    printArray(arr, n, 0);
    printf("%sArray: ", YEL);
    printArray(arr, n, 1);


    printf("\n%sEnter a key to find: ", RESET);
    scanf("%d", &key);

    idx = binarySearch(arr, n, key);
    if(idx >= 0) {
        idx = getStartingIdx(arr, n, idx);

        printf("%sFound %02d at: ", GRN, key);
        for(int i = idx; i < n && arr[i][1] == key; i++) {
            printf("%02d ", i);
        }

        printf("\n%sInitially at : ", CYN);
        for(int i = idx; i < n && arr[i][1] == key; i++) {
            printf("%02d ", arr[i][0]);
        }
        printf("\n");
    } else {
        printf("%s%02d not found in the array!\n", RED, key);
    }

    return 0;
}
