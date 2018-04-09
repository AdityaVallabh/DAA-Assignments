#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 2

int** generateMatrix(int m, int n)
{
    srand(time(NULL));

    int** matrix = (int**) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {        
        matrix[i] =(int*) malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % MOD;
        }
    }
    
    return matrix;
}

void printMatrix(int** matrix, int m, int n)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                printf(" %d ", matrix[i][j]);
            } else {
                printf(" * ");
            }
        }        
        printf("\n");
    }
}

int isEmpty(int** matrix, int a, int b, int c, int d)
{
    for (int i = a; i <= c; i++) {
        for (int j = b; j <= d; j++) {
            if (matrix[i][j] != 0) {
                return 0;
            }
        }
    }

    return 1;
}

void find(int** matrix, int m, int n, int a, int b, int c, int d)
{
    if (isEmpty(matrix, a, b, c, d)) {
        return;
    }
    if (a == c && b == d) {
        printf("(%d, %d) = %d\n", a, b, matrix[a][b]);
        return;
    }
    find(matrix, m, n, a,           b,           (a+c)/2, (b+d)/2);
    find(matrix, m, n, a,           (b+d)/2 + 1, (a+c)/2, d);
    find(matrix, m, n, (a+c)/2 + 1, b,           c,       (b+d)/2);
    find(matrix, m, n, (a+c)/2 + 1, (b+d)/2 + 1, c,       d);
}

int main()
{
    int m, n;
    printf("Enter the dimensions of the matrix: ");
    scanf("%d %d", &m, &n);
    int** matrix = generateMatrix(m, n);
    printMatrix(matrix, m, n);
    find(matrix, m, n, 0, 0, m - 1, n - 1);
    return 0;
}
