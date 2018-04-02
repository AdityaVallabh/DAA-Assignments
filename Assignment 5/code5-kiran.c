#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

int k = 0, *a, *tree;
void buildTree(int n, int i) {
    if(i < n) {
        buildTree(n, 2*i + 1);
        tree[i] = a[k];
        k += 1;
        buildTree(n, 2*i + 2);
    }
}

void inorder(int *array, int n, int i) {
    if(i < n) {
        inorder(array, n, 2*i + 1);
        printf("%02d ", array[i]);
        inorder(array, n, 2*i + 2);
    }
}

void generateArray(int n) {
    int i;
    for(i = 0; i < n; i++) {
        a[i] = rand()%MOD;
    }
}

void printArray(int *a, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%02d ", a[i]);
    }
    printf("\n");
}

int main(){

    int n, i;

    printf("Enter the size of inorder traversal array: ");
    scanf("%d", &n);
    a = (int *) malloc(n * sizeof(int));
	tree = (int *) malloc(n * sizeof(int));

    generateArray(n);
    printf("Inorder traversal array:\n");
    printArray(a, n);

    buildTree(n, 0);
    
    printf("\nLevel order traversal:\n");
    printArray(tree, n);

    printf("\nInorder traversal:(Verification)\n");
    inorder(tree, n, 0);
    printf("\n");

    return 0;
}
