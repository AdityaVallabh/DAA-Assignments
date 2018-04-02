#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

int k = 0;

// The buildtree function
void buildTree(int *arr, int *tree, int n, int i) {
    if(i < n) {
        buildTree(arr, tree, n, 2*i + 1);           // build left sub-tree
        tree[i] = arr[k];                           // assign value to root
        k += 1;
        buildTree(arr, tree, n, 2*i + 2);           // build right sub-tree
    }
}

// Perform inorder traversal
void inorder(int *arr, int n, int i) {
    if(i < n) {
        inorder(arr, n, 2*i + 1);                   // traverse left sub-tree
        printf("%02d ", arr[i]);                    // print root
        inorder(arr, n, 2*i + 2);                   // traverse right sub-tree
    }
}

// Generate random array
void generateArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        arr[i] = rand()%MOD;
    }
}

// Print array
void printArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%02d ", arr[i]);
    }
    printf("\n");
}

// Main method
int main(){

    int n, *arr, *tree, i;

    printf("Enter the size of the array: ");
    scanf("%d", &n);                                // input array size
    arr = (int *) malloc(n * sizeof(int));
    generateArray(arr, n);                          // generate array
    printf("Inorder Traversal Array: ");
    printArray(arr, n);                             // print array

    tree = (int *) malloc(n * sizeof(int));         // initialize tree array
    buildTree(arr, tree, n, 0);                     // build tree
    
    printf("\nCompletely Filled Tree\n");
    printf("Level Order Traversal: ");
    printArray(tree, n);                            // print level-order traversal

    printf("Inorder Traversal:     ");
    inorder(tree, n, 0);                            // print inorder traversal
    printf("\n");

    return 0;
}
