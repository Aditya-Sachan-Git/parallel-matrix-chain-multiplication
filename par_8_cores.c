#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <omp.h>

double matrixChainOrder(double p[], int n) {
    int m = n - 1;
    double** dp = (double**)malloc(m * sizeof(double*));
    
    for (int i = 0; i < m; i++) {
        dp[i] = (double*)malloc(m * sizeof(double));
        dp[i][i] = 0.0;
    }

    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            for (int len = 2; len <= m; len++) {
                #pragma omp taskgroup
                {
                    #pragma omp taskloop shared(dp, p) grainsize(15) nogroup
                    for (int i = 0; i < m - len + 1; i++) {
                        int j = i + len - 1;
                        double min_cost = DBL_MAX;
                        
                        for (int k = i; k < j; k++) {
                            double cost = dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1];
                            if (cost < min_cost) min_cost = cost;
                        }
                        
                        #pragma omp atomic write
                        dp[i][j] = min_cost;
                    }
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
    if (!file) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1) {
        fprintf(stderr, "Invalid input format\n");
        fclose(file);
        return 1;
    }

    double* p = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &p[i]) != 1) {
            fprintf(stderr, "Invalid matrix dimension\n");
            fclose(file);
            free(p);
            return 1;
        }
    }
    fclose(file);

    omp_set_num_threads(8);
    omp_set_schedule(omp_sched_guided, 0);
    
    double start = omp_get_wtime();
    double minCost = matrixChainOrder(p, n);
    double time_taken = omp_get_wtime() - start;

    printf("Optimal Cost: %.0f\n", minCost);
    printf("Execution time: %f seconds\n", time_taken);
    printf("Cores used: %d\n", omp_get_max_threads());

    free(p);
    return 0;
}
