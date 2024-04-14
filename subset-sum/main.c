#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, sum;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the sum: ");
    scanf("%d", &sum);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int **dp = (int **)malloc((n) * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc((sum + 1) * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= sum; j++) {
            if (j == 0) {
                dp[i][j] = 1;
            } else if (i > 0 && j < arr[i]) {
                dp[i][j] = dp[i - 1][j];
            } else if (i > 0) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i]];
            } else {
                dp[i][j] = arr[i] == j;
            }
        }
    }

    if (!dp[n - 1][sum]) {
        printf("Subset with the given sum does not exist\n");
        return 0;
    } 

    int k = sum;

    printf("The subset with the given sum is: [");
    for (int i = n - 1; i >= 0; i--) {
        if ((i > 0 && dp[i - 1][k] != dp[i][k]) || 
            (i == 0 && k == arr[i])) {
            printf("%d, ", arr[i]);
            k -= arr[i];
        } 
    }
    printf("\b\b]\n");

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    free(arr);
    
    return 0;
}