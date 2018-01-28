#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MOD 100
#define MAX(x,y) (x > y)? x : y
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int **init;
int **mask;
int count;

int ** generateMatrix(int n) {
    int i, j;
    int **matrix = (int **) malloc(n * sizeof(int*));
    mask = (int **) malloc(n * sizeof(int*));
    init = (int **) malloc(n * sizeof(int*));
    srand(time(0));
    
    for(i = 0; i < n; i++) {        
        matrix[i] =(int*) malloc(n * sizeof(int));
        init[i] =(int*) malloc(n * sizeof(int));
        mask[i] =(int*) malloc(n * sizeof(int));
        
        for(j = 0; j < n; j++) {
            matrix[i][j] = rand() % MOD;
            init[i][j] = mask[i][j] = -1;
        }
    }
    
    return matrix;
}

void printMatrix(int ** matrix, int n, int color) {
    int i, j;
    char COLOR[10];
    (color != 0)? strcpy(COLOR, YEL) : strcpy(COLOR, RESET);

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(matrix[i][j] != -1) {
                printf("%s%02d ", COLOR, matrix[i][j]);
            } else {
                printf(" %s* ", RESET);
            }
        }        
        printf("%s\n", RESET);
    }
}

void printPartitions(int ** matrix, int n) {
    int i, j;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(matrix[i][j] != -1) {
                printf("%s%02d ", (j%2)?GRN:CYN, matrix[i][j]);
            } else {
                printf(" %s* ", RESET);
            }
        }        
        printf("%s\n", RESET);
    }
}

void findPartition(int **matrix, int n) {
    int i, j, len1, len2, len, max, start;

    for(j = 0; j < n; j++) {
        for(i = max = len = len1  = len2 = 1, start = 0; i < n; i++) {
            len1 = (matrix[i][j] >= matrix[i-1][j])? len1 + 1 : 1;
            len2 = (matrix[i][j] <= matrix[i-1][j])? len2 + 1 : 1;
            len = MAX(len1, len2);
            if(max < len) {
                max = len;
                start = i - len + 1;
            }
        }

        for(i = start; i < start+max; i++) {
            mask[i][j] = matrix[i][j];
        }
    }

    printPartitions(mask, n);
}

int recursiveFind(int **matrix, int n, int x, int y, int len, int print) {
    int l, r, u, d, max1, max2;

    mask[x][y] = matrix[x][y];
    l = r = u = d = len + 1;

    if(len+1 == print) {
        printMatrix(mask, n, 1);
        printf("\n");
        count++;
    }

    if(y-1 >= 0 && mask[x][y-1] == -1 && matrix[x][y-1] >= matrix[x][y]) {
        l = recursiveFind(matrix, n, x, y-1, len+1, print);
    }
    if(y+1 < n && mask[x][y+1] == -1 && matrix[x][y+1] >= matrix[x][y]) {
        r = recursiveFind(matrix, n, x, y+1, len+1, print);
    }
    if(x-1 >= 0 && mask[x-1][y] == -1 && matrix[x-1][y] >= matrix[x][y]) {
        u = recursiveFind(matrix, n, x-1, y, len+1, print);
    }
    if(x+1 < n && mask[x+1][y] == -1 && matrix[x+1][y] >= matrix[x][y]) {
        d = recursiveFind(matrix, n, x+1, y, len+1, print);
    }

    mask[x][y] = -1;
    max1 = MAX(l,r), max2 = MAX(u,d);
    return MAX(max1, max2);
}

void findLongestPath(int **matrix, int n) {
    int i, j, len, maxLen;

    for(i = maxLen = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            len = recursiveFind(matrix, n, i, j, 0, -1);
            init[i][j] = len;
            maxLen = (len > maxLen)? len : maxLen;
        }
    }

    for(i = count = 0; i < n; i++) {
        for(j = 0;j < n; j++) {
            if(init[i][j] == maxLen) {
                printf("Initial Point: (%d,%d)\n", i, j);
                recursiveFind(matrix, n, i, j, 0, maxLen);
            }
        }
    }
    
    printf("Total number of paths found: %d\n", count);
}

int main() {
    
    int **matrix, i, j, n;
    printf("Enter matrix dimensions (n x n): ");
    scanf("%d", &n);
    
    matrix = generateMatrix(n);
    printf("\nThe Random Matrix:\n");
    printMatrix(matrix, n, 0);

    printf("\nThe Partition Matrix\n");
    findPartition(matrix, n);

    for(i=0; i<n; i++) for(j=0; j<n; j++) mask[i][j] = -1;
    printf("\nThe Longest Path Matrix\n");
    findLongestPath(matrix, n);
    
    return 0;
}
