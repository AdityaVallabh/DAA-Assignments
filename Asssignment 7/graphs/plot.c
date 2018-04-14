# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# define MAX(x,y) (x > y)? x : y

int steps;

typedef struct {
  int val;
  int allots[30];
} DP;

DP assign(DP *dp, int n, int **costMatrix) {
  int mask, lim = 1 << n, x, j;

  for(mask = 0; mask < lim; mask++) {
    dp[mask].val = INT_MAX;
  }

  dp[0].val = 0;

  for(mask = 0; mask < lim; mask++) {
    steps += n;
    x = __builtin_popcount(mask);
    for(j = 0; j < n; j++) {
      steps += 1;
      if(!(mask&(1<<j))) {
        int a = dp[mask|(1<<j)].val;
        int b = dp[mask].val + costMatrix[x][j];
        steps += 1;
        if(a <= b) {
          dp[mask|(1<<j)].val = a;
        } else {
          dp[mask|(1<<j)].val = b;
          steps += n;
          for(int i = 0; i < n; i++) dp[mask|(1<<j)].allots[i] = dp[mask].allots[i];
          dp[mask|(1<<j)].allots[x] = j;
        }        
      }
    }
  }

  return dp[lim-1];
}

int ** initializeMatrix(int n) {
  int i, **costMatrix;
  costMatrix = (int **) malloc(n * sizeof(int *));

  for(i = 0; i < n; i++) {
    costMatrix[i] = (int *) malloc(n * sizeof(int));
  }

  return costMatrix;
}

void freeMemory(int **costMatrix, DP *dp, int n) {
    int i;
    for(i = 0; i < n; i++) {
        free(costMatrix[i]);
    }
    free(dp);
}

int convertToMin(int **costMatrix, int n) {
  int i, j, max;

  for(i = 0, max = -1; i < n; i++) {
    for(j = 0; j< n; j++) {
      steps += 1;
      max = MAX(max, costMatrix[i][j]);
    }
  }
  
  for(i = 0; i < n; i++) {
    for(j = 0; j< n; j++) {
      costMatrix[i][j] = max - costMatrix[i][j];
    }
  }

  return max;
}

int main() {
  FILE *allot = fopen("allot.dat", "w");
  int i, j, n, max, **costMatrix;
  DP *dp, solution;
  n = 20;

  while(n-- > 1) {
    steps = 0;
    costMatrix = initializeMatrix(n);
    dp = (DP *) malloc((1<<n) * sizeof(DP));  

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            costMatrix[i][j] = 1;
        }
    }

    max = convertToMin(costMatrix, n);
    solution = assign(dp, n, costMatrix);
    fprintf(allot, "%d\t%d\n", n, steps);
    freeMemory(costMatrix, dp, n);
  }

  fclose(allot);
  system("gnuplot -p plot.gnp");

  return 0;
}