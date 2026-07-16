#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>

double matrixChainOrder(double p[], int i, int j, int m, double** dp, int** split) {
    if (i == j) return 0.0;
    if (dp[i][j] != -1.0) return dp[i][j];
    dp[i][j] = DBL_MAX;
    for (int k = i; k < j; k++) {
        double cost = matrixChainOrder(p, i, k, m, dp, split) 
                    + matrixChainOrder(p, k + 1, j, m, dp, split) 
                    + p[i] * p[k + 1] * p[j + 1];
        if (cost < dp[i][j]) {
            dp[i][j] = cost;
            split[i][j] = k;
        }
    }
    return dp[i][j];
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening input file!\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    
    double* p = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf", &p[i]);
    }
    fclose(file);

    clock_t start = clock();
    
    int m = n - 1;
    if (m == 0) {
        printf("0\n");
        free(p);
        return 0;
    }

    double** dp = (double**)malloc(m * sizeof(double*));
    int** split = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (double*)malloc(m * sizeof(double));
        split[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dp[i][j] = -1.0;
            split[i][j] = -1;
        }
    }

    double minCost = matrixChainOrder(p, 0, m - 1, m, dp, split);
    
    printf("Minimum cost: %.0f\n", minCost);
    
    for (int i = 0; i < m; i++) {
        free(dp[i]);
        free(split[i]);
    }
    free(dp);
    free(split);
    free(p);
    
    double time_taken = ((double)(clock() - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    
    return 0;
}
