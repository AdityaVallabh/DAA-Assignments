#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

double steps = 0;

int join(int arr[], int left[], int right[],
          int l, int m, int r)
{
    int i, j; // Used in second loop
    for (i = 0; i <= m - l; i++)
        arr[i] = left[i];
 
    for (j = 0; j < r - m; j++)
        arr[i + j] = right[j];
}
 
// Function to store alternate elemets in left
// and right subarray
int split(int arr[], int left[], int right[],
          int l, int m, int r)
{
    int i;
    for (i = 0; i <= m - l; i++)
        left[i] = arr[i * 2];
 
    for (i = 0; i < r - m; i++)
        right[i] = arr[i * 2 + 1];
}
 
// Function to generate Worst Case of Merge Sort
int generateWorstCase(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
 
        // create two auxillary arrays
        int left[m - l + 1];
        int right[r - m];
 
        // Store alternate array elements in left
        // and right subarray
        split(arr, left, right, l, m, r);
 
        // Recurse first and second halves
        generateWorstCase(left, l, m);
        generateWorstCase(right, m + 1, r);
 
        // join left and right subarray
        join(arr, left, right, l, m, r);
    }
}

void merge(int **arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1][2], R[n2][2];

    steps += 2;
    for(i = 0; i < n1; i++) {
        steps += 3 + 6;
        L[i][0] = arr[l+i][0];
        L[i][1] = arr[l+i][1];
    }

    steps += 2;
    for(j = 0; j < n2; j++) {
        steps += 3 + 6;
        R[j][0] = arr[m+1+j][0];
        R[j][1] = arr[m+1+j][1];
    }

    steps += 3;
    i = j = 0;
    k = l;

    while(i < n1 && j < n2) {
        steps += 3 + 3 + 2;
        if(L[i][1] <= R[j][1]) {
            steps += 8;
            arr[k][0] = L[i][0];
            arr[k][1] = L[i][1];
            i++;
        } else {
            steps += 8;
            arr[k][0] = R[j][0];
            arr[k][1] = R[j][1];
            j++;
        }
        k++;
    }

    while(i < n1) {
        steps += 11;
        arr[k][0] = L[i][0];
        arr[k][1] = L[i][1];
        i++;
        k++;
    }

    while(j < n2) {
        steps += 11;
        arr[k][0] = R[j][0];
        arr[k][1] = R[j][1];
        j++;
        k++;
    }
}

void mergeSort(int **arr, int l, int r) {
    steps += 1;
    if(l < r) {
        steps += 3 + 4;
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int binarySearch(int **arr, int n, int key) {
    int l = 0, r = n-1, m;
    steps += 2;

    while(l <= r) {
        steps += 1 + 3;

        m = (l + r) / 2;
        if(arr[m][1] == key) {
            steps += 2;
            return m;
        } else if(arr[m][1] < key) {
            steps += 4 + 2;
            l = m + 1;
        } else if(arr[m][1] > key) {
            steps += 6 + 2;
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
    int **arr;
    int n, key, idx, i;
    n = 50;
    FILE *sortAverage = fopen("sortAverage.dat", "w");
    FILE *sortWorst = fopen("sortWorst.dat", "w");
    FILE *sortBest = fopen("sortBest.dat", "w");
    FILE *searchAverage = fopen("searchAverage.dat", "w");
    FILE *searchBest = fopen("searchBest.dat", "w");
    FILE *searchWorst = fopen("searchWorst.dat", "w");

    while(n-- > 1){
        //printf("%d ",n);
        steps = 0;
        arr = generateArray(n);
        
        mergeSort(arr, 0, n-1);
        fprintf(sortAverage, "%d\t%lf\n", n+1, steps);



        steps = 0;
        for(i=0; i <n; i++){
            key = arr[i][1];
            idx = binarySearch(arr, n, key);
        }
        steps /= n;
        fprintf(searchAverage, "%d\t%lf\n", n+1, steps);

        steps = 0;
        key = -1;
        idx = binarySearch(arr, n, key);
        fprintf(searchWorst, "%d\t%lf\n", n+1, steps);



        steps = 0;
        mergeSort(arr, 0, n-1);
        fprintf(sortBest, "%d\t%lf\n", n+1, steps);



        steps = 0;
        key = arr[(n-1)/2][1];
        idx = binarySearch(arr, n, key);
        fprintf(searchBest, "%d\t%lf\n", n+1, steps);



        steps = 0;
        int a[n];
        for(i = 0; i < n; i++) a[i] = i;
        generateWorstCase(a, 0, n-1);
        for(i = 0; i < n; arr[i][0] = i++) arr[i][1] = a[i];
        mergeSort(arr, 0, n-1);
        fprintf(sortWorst, "%d\t%lf\n", n+1, steps);
        
        //fprintf(searchAverage, "%d\t%lf\n", n+1, (steps+8)/2);


  //  printf("\nEnter a key to find: ");
//    scanf("%d", &key);

    //key = arr[(n-1)/2][1];
    /*
    if(idx >= 0) {
        idx = getStartingIdx(arr, n, idx);

        printf("Found %02d at: ", key);
        for(int i = idx; i < n && arr[i][1] == key; i++) {
            printf("%02d ", i);
        }

        printf("\nInitially at : ");
        for(int i = idx; i < n && arr[i][1] == key; i++) {
            printf("%02d ", arr[i][0]);
        }
        printf("\n");
    } else {
        printf("%02d not found in the array!\n", key);
    }    */

    for(i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}
    fclose(sortAverage);
    fclose(sortWorst);
    fclose(sortBest);
    fclose(searchWorst);
    fclose(searchBest);
    fclose(searchAverage);

    system("gnuplot -p 'sort.gnp'");
    system("gnuplot -p 'search.gnp'");

    return 0;
}