#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

int swaps, steps, count, maxCount;

typedef struct NODE {
    int it;
    int pos;
    struct NODE* next;
} NODE;

NODE * insertNode(NODE *head, int it, int pos) {
    steps += 7;
    NODE *p = (NODE *) malloc(sizeof(NODE));
    p -> it = it;
    p -> pos = pos;
    p -> next = head;
    return p;
}

void swap(int *arr, NODE **heads, int it, int a, int b) {
    //printf("swapping %d and %d\n", *a, *b);
    swaps += 1;
    steps += 4;
    heads[a] = insertNode(heads[a], it, b);
    heads[b] = insertNode(heads[b], it, a);

    steps += 7;
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;

    steps += 7;
    NODE* head = heads[a];
    heads[a] = heads[b];
    heads[b] = head;
}

int getMinIdx(int *arr, int n, int i) {
    int idx, min, j;
    steps += 6 + 4;
    idx = i;
    min = arr[i];
    
    for(j = i+1; j < n-i; j++) {
        steps += 4 + 9;
        if(arr[j] < min) {
            steps += 3;
            min = arr[j];
            idx = j;
            count++;
        }
    }
    return idx;
}

int getMaxIdx(int *arr, int n, int i) {
    int idx, max, j;
    steps += 6 + 4;
    idx = n-i-1;
    max = arr[n-i-1];
    
    for(j = i; j < n-i-1; j++) {
        steps += 4 + 9;
        if(arr[j] > max) {
            steps += 3;
            max = arr[j];
            idx = j;
            count++;
        }
    }
    return idx;
}

void sort(int *arr, NODE **heads, int n) {
    int i, j, min, mini, max, maxi;

    steps += 3;
    for(i = 0; i < n/2; i++) {
        steps += 4 + 1;
        mini = getMinIdx(arr, n, i);
        if(mini != i) {
            swap(arr, heads, i+1, mini, i);
        }
        
        maxi = getMaxIdx(arr, n, i);
        steps += 1;
        if(maxi != n-i-1) {
            swap(arr, heads, i+1, maxi, n-i-1);
        }
    }
}

int * generateArray(int n) {
    int i;
    int *arr = (int *) malloc(n * sizeof(int));
    srand(time(0));
    
    for(i = 0; i < n; i++) {
        arr[i] = rand() % MOD;
        //scanf("%d", &arr[i]);
    }

    return arr;
}

NODE** initialize(int n) {
    int i;
    NODE** heads = (NODE **) malloc(n * sizeof(NODE *));

    for(i = 0; i < n; i++) {
        heads[i] = (NODE *) malloc(sizeof(NODE));
        heads[i]->it = 0;
        heads[i]->pos = i;
        heads[i]->next = NULL;
    }

    return heads;
}

void freeHeads(NODE **heads, int n) {
    int i;
    for(i = 0; i < n; i++) {
        NODE *p, *head = heads[i];
        while(head != NULL) {
            p = head;
            head = head -> next;
            free(p);
        }
    }
    free(heads);
}

void printArray(int *arr, int n) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void printList(NODE *head) {
    if(head == NULL) {
        return;
    }

    printList(head -> next);
    printf("(%d,%d) ", head -> it, head -> pos);
}

void swap0(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
NODE **heads;
void permute(int *arr,int i,int n) { 
  if (n == i){
    steps = count = 0;
    heads = initialize(n);
    int a[n], ii;
    printArray(arr, n);
    for(ii = 0; ii < n; ii++) a[ii] = arr[ii];
    sort(a, heads, n);
    freeHeads(heads, n);
    printf("\t%d :%d\n", steps, count);
    maxCount = (maxCount < count) ? count : maxCount;
    return;
  }
  int j = i;
  for (j = i; j < n; j++) { 
     swap0(arr+i,arr+j);
     permute(arr,i+1,n);
     swap0(arr+i,arr+j);
  }
  return;
}

int main() {
    int n, i, *arr;
    NODE **heads;
    FILE *average = fopen("./average.dat", "w");
    FILE *best = fopen("./best.dat", "w");
    FILE *worst = fopen("./worst.dat", "w");
    n = 101;

    while(n-- > 1){
        arr = generateArray(n);
        swaps = 0;
        steps = 0;
        count = 0;
        maxCount = count;
        //permute(arr, 0, n);
        //printf("maxCount: %d\n", maxCount);
        
        heads = initialize(n);
        sort(arr, heads, n);
        freeHeads(heads, n);
        fprintf(average, "%d\t%d\n", n, steps);
        swaps = 0;
        steps = 0;
        count = 0;
        heads = initialize(n);
        sort(arr, heads, n);
        freeHeads(heads, n);
        fprintf(best, "%d\t%d\n", n, steps);

        // Not exactly the worst case but it's the best I could find
        swaps = 0;
        steps = 0;
        count = 0;
        if(n % 2 == 0) {
            for(i = n-2; i >= 0; i--) {
                arr[i] = n - i - 2;
            }

            for(i = 0; i < n/2; i++) {
                arr[i] += 1;
            }

            arr[n-1] = n/2 - 1;
        } else {
            for(i = n-2; i >= 0; i--) {
                arr[i] = n - i - 2;
            }

            for(i = 0; i <= n/2; i++) {
                arr[i] += 1;
            }

            arr[n-1] = n/2 - 1;
        }
        heads = initialize(n);
        sort(arr, heads, n);
        freeHeads(heads, n);
        fprintf(worst, "%d\t%d\n", n, steps);
    }

    fclose(average);
    fclose(worst);
    fclose(best);

    system("gnuplot -p sort.gnp");

    return 0;
}
