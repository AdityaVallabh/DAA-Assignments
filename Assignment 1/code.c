#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

int ** generateMatrix(int n) {
    int i, j;
    int **matrix = (int **) malloc(n * sizeof(int*));
    srand(time(0));
    
    for(i = 0; i < n; i++) {
        
        matrix[i] =(int*) malloc(n * sizeof(int));
        
        for(j = 0; j < n; j++) {
            matrix[i][j] = rand() % MOD;
        }
    }
    
    return matrix;
}

void printMatrix(int ** matrix, int n) {
    int i, j;
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%02d ", matrix[i][j]);
        }        
        printf("\n");
    }
}

int main() {
	
	int **matrix, i, j, n;
	
    printf("Enter matrix dimensions (n x n): ");
    scanf("%d", &n);
    
    matrix = generateMatrix(n);
    printMatrix(matrix, n);
	
	return 0;
}


