# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# define MAX(x,y) (x > y)? x : y

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
    x = __builtin_popcount(mask);
    for(j = 0; j < n; j++) {
      if(!(mask&(1<<j))) {
        int a = dp[mask|(1<<j)].val;
        int b = dp[mask].val + costMatrix[x][j];
        
        if(a <= b) {
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

int convertToMin(int **costMatrix, int n) {
  int i, j, max;

  for(i = 0, max = -1; i < n; i++) {
    for(j = 0; j< n; j++) {
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

void print(int **matrix, int n)
{
  int i,j;
  for(i = 0; i < n; i++) 
  {
    for(j = 0; j< n; j++) 
    {
      if(matrix[i][j]==0)
        printf(" * ");
      else
        printf(" 1 ");
    }
    printf("\n");
  }
}

int main() {
  int i, j, n, max, **costMatrix, **printMatrix, temp;
  DP *dp, solution;
  printf("Enter number of engineers: ");
  scanf("%d", &n);

  costMatrix = initializeMatrix(n);
  printMatrix = initializeMatrix(n);
  dp = (DP *) malloc((1<<n) * sizeof(DP));  

  printf("\nEnter the liking values for jobs(n x n matrix):\n");
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      scanf("%d", &costMatrix[i][j]);
    }
  }

  max = convertToMin(costMatrix, n);
  
  solution = assign(dp, n, costMatrix);
  //printf("%d\n", n*max - solution.val);

  printf("\nJob allocation matrix:\n");
  for(i = 0 ; i < n; i++) {
    for(j = 0; j < n; j++)
    {
      printMatrix[i][j] = 0;
    }
    temp = solution.allots[i];
    printMatrix[i][temp] = 1;
  }

  print(printMatrix, n);

  return 0;
}
