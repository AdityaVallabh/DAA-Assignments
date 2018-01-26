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

int **dp;
int **mask;

int ** generateMatrix(int n) {
    int i, j;
    int **matrix = (int **) malloc(n * sizeof(int*));
    dp = (int **) malloc(n * sizeof(int*));
    mask = (int **) malloc(n * sizeof(int*));
    srand(time(0));
    
    for(i = 0; i < n; i++) {        
        matrix[i] =(int*) malloc(n * sizeof(int));
        dp[i] =(int*) malloc(n * sizeof(int));
        mask[i] =(int*) malloc(n * sizeof(int));
        
        for(j = 0; j < n; j++) {
            matrix[i][j] = rand() % MOD;
            dp[i][j] = mask [i][j] = -1;
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

int recursiveFind(int **matrix, int n, int x, int y) {
    int l, r, u, d, max1, max2;

    if(dp[x][y] != -1) {
        return dp[x][y];
    }

    l = r = u = d = 1;

    if(y-1 >= 0 && matrix[x][y-1] > matrix[x][y]) {
        l += recursiveFind(matrix, n, x, y-1);
    }
    if(y+1 < n && matrix[x][y+1] > matrix[x][y]) {
        r += recursiveFind(matrix, n, x, y+1);
    }
    if(x-1 >= 0 && matrix[x-1][y] > matrix[x][y]) {
        u += recursiveFind(matrix, n, x-1, y);
    }
    if(x+1 < n && matrix[x+1][y] > matrix[x][y]) {
        d += recursiveFind(matrix, n, x+1, y);
    }

    max1 = MAX(l,r), max2 = MAX(u,d);
    return dp[x][y]  = MAX(max1, max2);
}

void findLongestPath(int **matrix, int n) {
    int i, j, len, maxi, maxj, maxLen;

    for(i = maxLen = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            len = recursiveFind(matrix, n, i, j);
            if(len > maxLen) {
                maxLen = len;
                maxi = i;
                maxj = j;
            }   
        }
    }

    printf("[%d]\n",maxLen);
    i = maxi, j = maxj;

    while(1) {
        mask[i][j] = matrix[i][j];
        if(dp[i][j] == 1) break;

        int u = (i-1 >= 0 && matrix[i-1][j] > matrix[i][j])? dp[i-1][j] : 0;
        int d = (i+1 < n && matrix[i+1][j] > matrix[i][j])? dp[i+1][j] : 0;
        int l = (j-1 >= 0 && matrix[i][j-1] > matrix[i][j])? dp[i][j-1] : 0;
        int r = (j+1 < n && matrix[i][j+1] > matrix[i][j])? dp[i][j+1] : 0;
        int max1 = MAX(l,r), max2 = MAX(u,d);
        int max = MAX(max1, max2);

        if(max == r) {
            j += 1;
        } else if(max == d) {
            i += 1;
        } else if(max == l) {
            j -= 1;
        } else if(max == u) {
            i -= 1;
        }
    }

    printMatrix(mask, n, 1);
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
    //printMatrix(dp,n,0);
	
	return 0;
}
