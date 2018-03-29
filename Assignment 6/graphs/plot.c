#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 2

int count;
int steps;

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
    steps += 7;
    if(a >= m || c >= m || b >= n || d >= n) {
        return;
    }

    steps += 3;
    if(a == c && b == d) {
        steps += 3;
        if(matrix[a][b] != 0) {
            steps += 2;
            count += 1;
            //printf("(%d, %d) ", a, b);
        }

        return;
    }

    steps += 2;
    if(!isEmpty(matrix, a, b, c, d)) {
        steps += 20;
        find(matrix, m, n, a,           b,           (a+c)/2,    (b+d)/2);
        find(matrix, m, n, a,           (b+d)/2 + 1, (a+c)/2,     d);
        find(matrix, m, n, (a+c)/2 + 1, b,            c,          (b+d)/2);
        find(matrix, m, n, (a+c)/2 + 1, (b+d)/2 + 1,  c,          d);
    }
}

int main() {
    int m = 1, n = 1, **matrix, i, j;

    FILE *average = fopen("./average.dat", "w");
    FILE *best = fopen("./best.dat", "w");
    FILE *worst = fopen("./worst.dat", "w");
    printf("Enter the size of the matrix: ");
    scanf("%d%d", &i, &j);

    while(i >= m) {
        n = 1;
        while(j >= n) {
            steps = 0;
            matrix = generateMatrix(m, n);
            find(matrix, m, n, 0, 0, m-1, n-1);
            fprintf(average, "%d %d %d\n", m, n, steps);

            int x, y;
            for(x = 0; x < m; x++) for(y = 0; y < n; y++) matrix[x][y] = 0;

            steps = 0;
            find(matrix, m, n, 0, 0, m-1, n-1);
            fprintf(best, "%d %d %d\n", m, n, steps);


            for(x = 0; x < m; x++) for(y = 0; y < n; y++) matrix[x][y] = 1;
            steps = 0;
            find(matrix, m, n, 0, 0, m-1, n-1);
            fprintf(worst, "%d %d %d\n", m, n, steps);

            n += 1;
        }
        m += 1;
    }
    
    fclose(average);
    fclose(best);
    fclose(worst);


    system("gnuplot -p plot.gnp");
    system("gnuplot -p average.gnp");
    system("gnuplot -p best.gnp");
    system("gnuplot -p worst.gnp");

    return 0;
}
