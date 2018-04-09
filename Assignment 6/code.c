#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 2

int count;                                              // to keep track of the number of elements

// function to generate a random bit matrix
int ** generateMatrix(int m, int n) {
    int i, j;
    int **matrix = (int **) malloc(m * sizeof(int*));   // allocate m rows
    srand(time(0));
    
    for(i = 0; i < m; i++) {        
        matrix[i] =(int*) malloc(n * sizeof(int));      // allocate n integers in each row
        
        for(j = 0; j < n; j++) {
            matrix[i][j] = rand() % MOD;                // 0 represents a clean cell, 1 represents a dirty cell
        }
    }
    
    return matrix;
}

// function to print the given matrix
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

// checks if the given sub-matrix is completely empty
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

// function to find the dirty elements in a given matrix
void find(int **matrix, int m, int n, int a, int b, int c, int d) {
    // a check to ensure we're still inside the matrix
    if(a >= m || c >= m || b >= n || d >= n) {
        return;
    }

    // base case when we reach a sinle cell
    if(a == c && b == d) {
        if(matrix[a][b] != 0) {             // if cell is dirty, print
            printf("(%d, %d) ", a, b);
            count += 1;                     // increment count
        }

        return;
    }

    // if sub-matrix is not empty, call find() on quadrants
    if(!isEmpty(matrix, a, b, c, d)) {
        find(matrix, m, n, a,           b,           (a+c)/2,    (b+d)/2);          // find() in 1st quadrant
        find(matrix, m, n, a,           (b+d)/2 + 1, (a+c)/2,     d);               // find() in 2nd quadrant
        find(matrix, m, n, (a+c)/2 + 1, b,            c,          (b+d)/2);         // find() in 3rd quadrant
        find(matrix, m, n, (a+c)/2 + 1, (b+d)/2 + 1,  c,          d);               // find() in 4th quadrant
    }
}

// the main method
int main() {
    int m, n, **matrix;

    printf("Enter the size of the matrix: ");
    scanf("%d%d", &m, &n);                          // input the matrix dimensions

    count = 0;
    matrix = generateMatrix(m, n);                  // generate the random bit matrix
    printf("The Random Matrix:\n");
    printMatrix(matrix, m, n);                      // print the generated random matrix

    printf("The elements are at:\n");
    find(matrix, m, n, 0, 0, m-1, n-1);             // call the find() function on complete matrix
    printf("\n");
    printf("Total elements found: %d\n", count);    // print the total number of elements found

    return 0;
}
