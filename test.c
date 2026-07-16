#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int matrixChainOrder(int p[], int i, int j, int m, int** dp, int** split) {
    if (i == j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = INT_MAX;
    for (int k = i; k < j; k++) {
        int cost = matrixChainOrder(p, i, k, m, dp, split) + matrixChainOrder(p, k + 1, j, m, dp, split) + p[i] * p[k + 1] * p[j + 1];
        if (cost < dp[i][j]) {
            dp[i][j] = cost;
            split[i][j] = k;
        }
    }
    return dp[i][j];
}
/*
    char* constructOptimalParenthesis(int i, int j, int** split) {
    if (i == j) {
        char* str = (char*)malloc(10 * sizeof(char));
        sprintf(str, "A%d", i + 1);
        return str;
    }
    int k = split[i][j];
    char* left = constructOptimalParenthesis(i, k, split);
    char* right = constructOptimalParenthesis(k + 1, j, split);
    char* result = (char*)malloc(strlen(left) + strlen(right) + 4);
    sprintf(result, "(%s*%s)", left, right);
    free(left);
    free(right);
    return result;
}*/

int main() {
    int n;
    scanf("%d", &n);
    int* p = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    clock_t start = clock();
    
    int m = n - 1;
    if (m == 0) {
        printf("0\n");
        free(p);
        return 0;
    }

    int** dp = (int**)malloc(m * sizeof(int*));
    int** split = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (int*)malloc(m * sizeof(int));
        split[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dp[i][j] = -1;
            split[i][j] = -1;
        }
    }
    int minCost = matrixChainOrder(p, 0, m - 1, m, dp, split);
    /*
    char* optimal = constructOptimalParenthesis(0, m - 1, split);
    printf("%d\n%s\n", minCost, optimal);
    free(optimal);*/
    printf("\n%d\n",minCost);
    for (int i = 0; i < m; i++) {
        free(dp[i]);
        free(split[i]);
    }
    free(dp);
    free(split);
    free(p);
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %.2f seconds\n", time_taken);
    return 0;
}
