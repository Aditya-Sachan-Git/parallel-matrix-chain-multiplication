#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <omp.h>

double matrixChainOrder(double p[], int n) {
    int m = n - 1;
    double** dp = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) {
        dp[i] = (double*)malloc(m * sizeof(double));
        dp[i][i] = 0.0;
    }

    for (int len = 2; len <= m; len++) {
        #pragma omp parallel for shared(dp, p) schedule(dynamic)
        for (int i = 0; i < m - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = DBL_MAX;
            
            for (int k = i; k < j; k++) {
                double cost = dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    double result = dp[0][m-1];
    for (int i = 0; i < m; i++) free(dp[i]);
    free(dp);
    return result;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    int n;
    fscanf(file, "%d", &n);
    
    double* p = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf", &p[i]);
    }
    fclose(file);

    double start = omp_get_wtime();
    double minCost = matrixChainOrder(p, n);
    double time_taken = omp_get_wtime() - start;

    printf("Minimum cost: %.0f\n", minCost);
    printf("Execution time: %.2f seconds\n", time_taken);
    printf("Cores used: %d\n", omp_get_max_threads());
    free(p);
    
    return 0;
}
