#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

int main() {
    int n, w;
    scanf("%d", &n);
    scanf("%d", &w);
    int *weights, *values;
    weights = (int*)malloc(n * sizeof(int));
    values = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    int** dp;
    dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((w + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (j - weights[i - 1] < 0) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    int sum = dp[n][w];
    int *selected;
    selected = (int*)malloc(n * sizeof(int));
    int k = n - 1;
    int flag = 1;

    for (int i = 0; i < n; i++) {
        selected[i] = 0;
    }

    while (sum > 0) {
        int i = 0;
        while (i != w) {
            if (dp[k][i] == sum) {
                i = 0;
                k--;
                flag = 0;
            } else {
                i++;
            }
        }
        if (flag) {
            selected[k] = 1;
            sum -= values[k];

        }
        flag = 1;
    }
    
    printf("Items selected: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", selected[i]);
    }
    printf("\n");

    free(weights);
    free(values);
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    free(selected);
    return 0;
}