#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 2

int count;

int ** generateMatrix(int m, int n) {
    int i, j;
    int **matrix = (int **) malloc(m * sizeof(int*));
    srand(time(0));
    
    for(i = 0; i < m; i++) {        
        matrix[i] =(int*) malloc(n * sizeof(int));
        
        for(j = 0; j < n; j++) {
            matrix[i][j] = rand() % MOD;
        }
    }
    
    return matrix;
}

void printMatrix(int ** matrix, int m, int n) {
    int i, j;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(matrix[i][j] != 0) {
                printf(" %d ", matrix[i][j]);
            } else {
                printf(" * ");
            }
        }        
        printf("\n");
    }
}

int isEmpty(int **matrix, int a, int b, int c, int d) {
    int i, j;

    for(i = a; i <= c; i++) {
        for(j = b; j <= d; j++) {
            if(matrix[i][j] != 0) {
                return 0;
            }
        }
    }

    return 1;
}

void find(int **matrix, int m, int n, int a, int b, int c, int d) {
    if(a >= m || c >= m || b >= n || d >= n) {
        return;
    }

    if(a == c && b == d) {
        if(matrix[a][b] != 0) {
            count += 1;
            printf("(%d, %d) ", a, b);
        }

        return;
    }

    if(!isEmpty(matrix, a, b, c, d)) {
        find(matrix, m, n, a,           b,           (a+c)/2,    (b+d)/2);
        find(matrix, m, n, a,           (b+d)/2 + 1, (a+c)/2,     d);
        find(matrix, m, n, (a+c)/2 + 1, b,            c,          (b+d)/2);
        find(matrix, m, n, (a+c)/2 + 1, (b+d)/2 + 1,  c,          d);
    }
}

int main() {
    int m, n, **matrix;

    printf("Enter the size of the matrix: ");
    scanf("%d%d", &m, &n);

    count = 0;
    matrix = generateMatrix(m, n);
    printf("The Random Matrix:\n");
    printMatrix(matrix, m, n);

    printf("The elements are at:\n");
    find(matrix, m, n, 0, 0, m-1, n-1);
    printf("\n");
    printf("Total elements found: %d\n", count);

    return 0;
}
