#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

typedef struct NODE {
    int it;
    int pos;
    struct NODE* next;
} NODE;

NODE * insertNode(NODE *head, int it, int pos) {
    NODE *p = (NODE *) malloc(sizeof(NODE));
    p -> it = it;
    p -> pos = pos;
    p -> next = head;
    return p;
}

void swap(int *arr, NODE **heads, int it, int a, int b) {
    //printf("swapping %d and %d\n", *a, *b);

    heads[a] = insertNode(heads[a], it, b);
    heads[b] = insertNode(heads[b], it, a);

    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;

    NODE* head = heads[a];
    heads[a] = heads[b];
    heads[b] = head;
}

int getMinIdx(int *arr, int n, int i) {
    int mini = i, min = arr[i];
    mini = i;
    min = arr[i];
    for(int j = i+1; j < n-i; j++) {
        if(arr[j] < min) {
            min = arr[j];
            mini = j;
        }
    }
    return mini;
}
int getMaxIdx(int *arr, int n, int i) {
    int maxi = i, max = arr[i];
    maxi = i+1;
    max = arr[i+1];
    for(int j = i+2; j < n-i; j++) {
        if(arr[j] > max) {
            max = arr[j];
            maxi = j;
        }
    }
    return maxi;
}

void sort(int *arr, NODE **heads, int n) {
    int i, j, min, mini, max, maxi;

    for(i = 0; i < n/2; i++) {
        mini = getMinIdx(arr, n, i);
        if(mini != i) {
            swap(arr, heads, i+1, mini, i);
        }
        
        maxi = getMaxIdx(arr, n, i);
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

void printArray(int *arr, int n) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%02d ", arr[i]);
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

int main() {
    int n, i, *arr;
    NODE **heads;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    arr = generateArray(n);
    printArray(arr, n);

    heads = initialize(n);
    sort(arr, heads, n);
    printArray(arr, n);
    
    for(i = 0; i < n; i++) {
        printf("%d: ", arr[i]);
        printList(heads[i]);
        printf("\n");
    }

    return 0;
}