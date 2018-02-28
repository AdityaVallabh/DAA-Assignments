#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100


typedef struct NODE {
    int pos;
    struct NODE* next;
} NODE;

NODE * insertNode(NODE *head, int pos) {
    NODE *p = (NODE *) malloc(sizeof(NODE));
    p -> pos = pos;
    p -> next = head;
    return p;
}

void swap(int *arr, NODE **heads, int a, int b) {
    //printf("swapping %d and %d\n", *a, *b);
    heads[a] = insertNode(heads[a], b);
    heads[b] = insertNode(heads[b], a);

    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;

    NODE* head = heads[a];
    heads[a] = heads[b];
    heads[b] = head;
}

void heapify(int *arr, NODE **heads, int n, int idx) {
    int largest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if(largest != idx) {
        swap(arr, heads, idx, largest);
        heapify(arr, heads, n, largest);
    }
}

void heapSort(int *arr, NODE **heads, int n) {
    int i;
    for(i = n/2 - 1; i >= 0 ; i--) {
        heapify(arr, heads, n, i);
    }

    for(i = n-1; i > 0; i--) {
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
        printf("%02d ", arr[i]);
    }

    printf("\n");
}

void printList(NODE *head) {
    if(head == NULL) {
        return;
    }

    printList(head -> next);
    printf("(%d) ",head -> pos);
}

int main() {
    int n, i, *arr;
    NODE **heads;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    arr = generateArray(n);
    printf("Initial Array: ");
    printArray(arr, n);
    
    heads = initialize(n);
    heapSort(arr, heads, n);
    
    printf("\n");
    for(i = 0; i < n; i++) {
        printf("%02d: ", arr[i]);
        printList(heads[i]);
        printf("\n");
    }

    printf("\nSorted Array: ");
    printArray(arr, n);
    free(arr);
    freeHeads(heads, n);

    return 0;
}
