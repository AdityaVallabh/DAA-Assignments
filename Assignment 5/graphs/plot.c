#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

int steps;
int k = 0;
void buildTree(int *arr, int *tree, int n, int i) {
    steps += 1;
    if(i < n) {
        steps += 2;
        buildTree(arr, tree, n, 2*i + 1);
        steps += 5;
        tree[i] = arr[k];
        k += 1;
        steps += 2;
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

    FILE *average = fopen("./average.dat", "w");
    int n, *arr, *tree, i;

    scanf("%d", &n);
    
    while(n-- > 1) {
        steps = 0;
        k = 0;
        arr = (int *) malloc(n * sizeof(int));
        generateArray(arr, n);

        tree = (int *) malloc(n * sizeof(int));
        buildTree(arr, tree, n, 0);
        fprintf(average, "%d %d\n", n, steps);
    }
    fclose(average);

    system("gnuplot -p plot.gnp");

    return 0;
}
