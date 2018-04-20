# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>
# define MAX(x,y) (x > y)? x : y

typedef struct {
  int val;
  int allots[30];
} DP;

DP assign(DP *dp, int n, int **costMatrix) {
  int mask, lim = 1 << n, x, j;

  for(mask = 0; mask < lim; mask++) {
    dp[mask].val = INT_MIN;
  }

  dp[0].val = 0;

  for(mask = 0; mask < lim; mask++) {
    x = __builtin_popcount(mask);
    for(j = 0; j < n; j++) {
      if(!(mask&(1<<j))) {
        int a = dp[mask|(1<<j)].val;
        int b = dp[mask].val + costMatrix[x][j];
        
        if(a > b) {
          dp[mask|(1<<j)].val = a;
        } else {
          dp[mask|(1<<j)].val = b;
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

int main() {
  int i, j, n, max, **costMatrix;
  DP *dp, solution;
  printf("Enter the number of engineers/jobs: ");
  scanf("%d", &n);

  costMatrix = initializeMatrix(n);
  dp = (DP *) malloc((1<<n) * sizeof(DP));  
  srand(time(NULL));
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      //scanf("%d", &costMatrix[i][j]);
      costMatrix[i][j] = rand()%100;
      printf("%02d ", costMatrix[i][j]);
    }
    printf("\n");
  }

  solution = assign(dp, n, costMatrix);
  printf("Optimized Value: %d\n", solution.val);

   for(i = 0 ; i < n; i++) {
    printf("Engineer %d gets Job %d\n", i, solution.allots[i]);
  }

  return 0;
}