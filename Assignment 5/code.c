#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

int k = 0;
void buildTree(int *arr, int *tree, int n, int i) {
    if(i < n) {
        buildTree(arr, tree, n, 2*i + 1);
        tree[i] = arr[k];
        k += 1;
        buildTree(arr, tree, n, 2*i + 2);
    }
}

void inorder(int *arr, int n, int i) {
    if(i < n) {
        inorder(arr, n, 2*i + 1);
        printf("%02d ", arr[i]);
        inorder(arr, n, 2*i + 2);
    }
}

void generateArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        arr[i] = rand()%MOD;
    }
}

void printArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%02d ", arr[i]);
    }
    printf("\n");
}

int main(){

    int n, *arr, *tree, i;

    printf("Enter the size of the array: ");
    scanf("%d", &n);
    arr = (int *) malloc(n * sizeof(int));
    generateArray(arr, n);
    printf("Inorder Traversal Array: ");
    printArray(arr, n);

    tree = (int *) malloc(n * sizeof(int));
    buildTree(arr, tree, n, 0);
    
    printf("\nCompletely Filled Tree\n");
    printf("Level Order Traversal: ");
    printArray(tree, n);

    printf("Inorder Traversal:     ");
    inorder(tree, n, 0);
    printf("\n");

    return 0;
}
