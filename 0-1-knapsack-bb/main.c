#include <stdio.h>
#include <stdlib.h>

int upper = 0;

int best_profit = 0;
int *best_selected;

void knapsack(int *selected, int idx, int w, int n, int* profits, int* weights) {
    int c = 0, u = 0;
    int total_weight = 0, included_weight = 0;
    for (int i = 0; i < idx; i++) {
        if (selected[i] == 1) {
            included_weight += weights[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (selected[i] == 1) {
            if (total_weight + weights[i] <= w) {
                total_weight += weights[i];
                c -= profits[i];
                u -= profits[i];
            } else {
                c -= (w - total_weight) * profits[i] / weights[i];
                break;
            }
        }
    }

    if (c > upper || included_weight > w) {
        return;
    }
    
    if (u < upper) {
        upper = u;
    }

    if (idx == n) {
        if (-u > best_profit) {
            best_profit = -u;
            for (int i = 0; i < n; i++) {
                best_selected[i] = selected[i];
            }
            return;
        }
    }

    selected[idx] = 0;
    knapsack(selected, idx + 1, w, n, profits, weights);
    selected[idx] = 1;
    knapsack(selected, idx + 1, w, n, profits, weights);

}

int main() {
    int n, w;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &w);

    int *profits = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));
    best_selected = (int *)malloc(n * sizeof(int));

    printf("Enter the profits and weights of the items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &profits[i], &weights[i]);
    }

    int *selected = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        selected[i] = 1;
    }

    knapsack(selected, 0, w, n, profits, weights);

    if (best_profit <= 0) {
        printf("No solution\n");
        goto clear_all;
    }

    printf("Best profit: %d\n", best_profit);
    printf("Selected items: [");
    for (int i = 0; i < n; i++) {
        printf("%d, ", best_selected[i]);
    }
    printf("\b\b]\n");

clear_all:
    free(profits);
    free(weights);
    free(selected);
    free(best_selected);
    return 0;
}