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

void findPartition(int **matrix, int n) {
	int i, j, max, len, start;

	for(j = 0; j < n; j++) {
		max = len = 1;

		for(i = 1; i < n; i++) {
			if(matrix[i][j] >= matrix[i-1][j]) {
				len++;
			} else {
				len = 1;
			}

			if(max < len) {
				max = len;
				start = i - max + 1;
			}
		}

		printf("(%d,%d)=%d ", start, start+max-1, max);
	}
}

int main() {
	
	int **matrix, i, j, n;
	
    printf("Enter matrix dimensions (n x n): ");
    scanf("%d", &n);
    
    matrix = generateMatrix(n);
    printMatrix(matrix, n);
    findPartition(matrix, n);
	
	return 0;
}


