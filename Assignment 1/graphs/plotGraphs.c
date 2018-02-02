#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MOD 500
#define MAX(x,y) (x > y)? x : y

FILE *fpPartitionAvg;
FILE *fpPartitionBest;
FILE *fpPartitionWorst;
FILE *fpPathAvg;
FILE *fpPathBest;
FILE *fpPathLength;
FILE *fpPathCount;

int **init;
int **mask;
int count;
long long int steps = 0;

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

void findPartition(int **matrix, int n) {
    int i, j, len1, len2, len, max, start;

    steps += 1;
    for(j = 0; j < n; j++) {
        steps += 2;
        steps += 6;
        for(i = max = len = len1  = len2 = 1, start = 0; i < n; i++) {
            steps += 2 + 8 + 4 + 1;
            len1 = (matrix[i][j] >= matrix[i-1][j])? len1 + 1 : 1;
            len2 = (matrix[i][j] <= matrix[i-1][j])? len2 + 1 : 1;
            len = MAX(len1, len2);
            if(max < len) {
                max = len;
                start = i - len + 1;
                steps += 2;
            }
        }

        steps += 1;
        for(i = start; i < start+max; i++) {
            steps += 2 + 1;
            mask[i][j] = matrix[i][j];
        }
    }
}

int recursiveFind(int **matrix, int n, int x, int y, int len, int print) {
    int l, r, u, d, max1, max2;

    steps += 5;
    mask[x][y] = matrix[x][y];
    l = r = u = d = len + 1;

    steps += 1;
    if(len+1 == print) {
        steps += 1;
        count++;
    }

    steps += 5*4;
    
    if(y-1 >= 0 && mask[x][y-1] == -1 && matrix[x][y-1] >= matrix[x][y]) {
        steps += 1;
        l = recursiveFind(matrix, n, x, y-1, len+1, print);
    }
    if(y+1 < n && mask[x][y+1] == -1 && matrix[x][y+1] >= matrix[x][y]) {
        steps += 1;
        r = recursiveFind(matrix, n, x, y+1, len+1, print);
    }
    if(x-1 >= 0 && mask[x-1][y] == -1 && matrix[x-1][y] >= matrix[x][y]) {
        steps += 1;
        u = recursiveFind(matrix, n, x-1, y, len+1, print);
    }
    if(x+1 < n && mask[x+1][y] == -1 && matrix[x+1][y] >= matrix[x][y]) {
        steps += 1;
        d = recursiveFind(matrix, n, x+1, y, len+1, print);
    }

    steps += 6;
    mask[x][y] = -1;
    max1 = MAX(l,r), max2 = MAX(u,d);
    return MAX(max1, max2);
}

void findLongestPath(int **matrix, int n) {
    int i, j, len, maxLen;

    steps += 2;
    for(i = maxLen = 0; i < n; i++) {
        steps += 2 + 1;
        for(j = 0; j < n; j++) {
            steps += 2 + 4;
            len = recursiveFind(matrix, n, i, j, 0, -1);
            init[i][j] = len;
            maxLen = (len > maxLen)? len : maxLen;
        }
    }

    steps += 2;
    for(i = count = 0; i < n; i++) {
        steps += 2 + 1;
        for(j = 0; j < n; j++) {
            steps += 1;
            if(init[i][j] == maxLen) {
                recursiveFind(matrix, n, i, j, 0, maxLen);
            }
        }
    }
    fprintf(fpPathCount, "%d\t%d\n", n, count);
    fprintf(fpPathLength, "%d\t%d\n", n, maxLen);
}

int main() {

    fpPartitionAvg = fopen("./stats/partitionAvg.dat","w");
    fpPartitionBest = fopen("./stats/partitionBest.dat","w");
    fpPartitionWorst = fopen("./stats/partitionWorst.dat","w");
    fpPathAvg = fopen("./stats/pathAvg.dat","w");
    fpPathBest = fopen("./stats/pathBest.dat","w");
    fpPathLength = fopen("./stats/pathLength.dat","w");
    fpPathCount = fopen("./stats/pathCount.dat","w");
    
    int **matrix, i, j, n;
    n = 200;

    while(n--){
        steps = 0;        
        matrix = generateMatrix(n);
        findPartition(matrix, n);
        fprintf(fpPartitionAvg, "%d\t%lld\n", n, steps);

        steps = 0;
        for(i=0; i<n; i++) for(j=0; j<n; j++) mask[i][j] = -1;
        findLongestPath(matrix, n);
        fprintf(fpPathAvg, "%d\t%lld\n", n, steps);


        FILE *tmp1 = fpPathLength;
        FILE *tmp2 = fpPathCount;
        fpPathCount = fpPathLength = fopen("/dev/null", "w");
        steps = 0;
        for(i=0; i<n; i++) for(j=0; j<n; j++) mask[i][j] = -1;
        for(i=0; i<n; i++) for(j=0; j<n; j++) matrix[i][j] = (i+j)%2;
        findPartition(matrix, n);
        fprintf(fpPartitionBest, "%d\t%lld\n", n, steps);

        steps = 0;
        findLongestPath(matrix, n);
        fprintf(fpPathBest, "%d\t%lld\n", n, steps);
        fpPathLength = tmp1;
        fpPathCount = tmp2;


        steps = 0;
        for(i=0; i<n; i++) for(j=0; j<n; j++) mask[i][j] = -1;
        for(i=0; i<n; i++) for(j=0; j<n; j++) matrix[i][j] = 0;
        findPartition(matrix, n);
        fprintf(fpPartitionWorst, "%d\t%lld\n", n, steps);
    }

    fclose(fpPartitionAvg);
    fclose(fpPartitionBest);
    fclose(fpPartitionWorst);
    fclose(fpPathBest);
    fclose(fpPathAvg);
    fclose(fpPathLength);
    fclose(fpPathCount);
    system("gnuplot -p 'pathCount.gnp'");
    system("gnuplot -p 'pathLength.gnp'");
    system("gnuplot -p 'time.gnp'");
    system("gnuplot -p 'partition.gnp'");
    return 0;
}
