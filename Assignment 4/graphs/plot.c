#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define MOD 100

int swaps, steps, count, maxCount, minCount, minSteps, maxSteps;

typedef struct NODE {
    int it;
    int pos;
    struct NODE* next;
} NODE;

NODE * insertNode(NODE *head, int pos) {
    steps += 5;
    NODE *p = (NODE *) malloc(sizeof(NODE));
    p -> pos = pos;
    p -> next = head;
    return p;
}

void swap(int *arr, NODE **heads, int a, int b) {
    //printf("swapping %d and %d\n", *a, *b);
    count += 1;
    swaps += 1;
    steps += 4;
    heads[a] = insertNode(heads[a], b);
    heads[b] = insertNode(heads[b], a);

    steps += 7;
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;

    steps += 7;
    NODE* head = heads[a];
    heads[a] = heads[b];
    heads[b] = head;
}

void heapify(int *arr, NODE **heads, int n, int idx) {
    steps += 7;
    int largest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    steps += 3;
    if(left < n && arr[left] > arr[largest]) {
        steps += 1;
        largest = left;
    }

    steps += 3;
    if(right < n && arr[right] > arr[largest]) {
        steps += 1;
        largest = right;
    }

    steps += 1;
    if(largest != idx) {
        swap(arr, heads, idx, largest);
        heapify(arr, heads, n, largest);
    }
}

void heapSort(int *arr, NODE **heads, int n) {
    int i;
    steps += 4;
    for(i = n/2 - 1; i >= 0 ; i--) {
        steps += 3;
        heapify(arr, heads, n, i);
    }

    steps += 3;
    for(i = n-1; i > 0; i--) {
        steps += 3;
        swap(arr, heads, 0, i);
        heapify(arr, heads, i, 0);
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
    //printArray(arr, n);
    for(ii = 0; ii < n; ii++) a[ii] = arr[ii];
    heapSort(a, heads, n);
    freeHeads(heads, n);
    //printf("\t%d :%d\n", steps, count);
    maxCount = (maxCount < count) ? count : maxCount;
    minCount = (minCount > count) ? count : minCount;


    maxSteps = (maxSteps < steps) ? steps : maxSteps;
    minSteps = (minSteps > steps) ? steps : minSteps;
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
    n = 5;
    scanf("%d",&n);
    while(n-- > 1){
        arr = generateArray(n);
        swaps = 0;
        steps = 0;
        count = 0;
        maxCount = maxSteps = 0;
        minCount = minSteps = INT_MAX;
        heads = initialize(n);
        heapSort(arr, heads, n);
        fprintf(average, "%d %d\n", n, count);
        freeHeads(heads, n);
        for(i = 0; i < n; i++) arr[i] = i;
        permute(arr, 0, n);
        fprintf(best, "%d %d\n", n, minCount);
        fprintf(worst, "%d %d\n", n, maxCount);
        //printf("%d: %d, %d\n", n, maxCount, minCount);
        /*
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
        fprintf(worst, "%d\t%d\n", n, steps);*/
    }

    fclose(average);
    fclose(worst);
    fclose(best);

    system("gnuplot -p sort.gnp");

    return 0;
}
