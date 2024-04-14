#include <limits.h>
#include <stdio.h>

int matrix_chain(int p[], int i, int j) {
	if (i == j) { return 0; }
	int k, count;
	int min = INT_MAX;
	for (k = i; k < j; k++) {
		count = matrix_chain(p, i, k) + matrix_chain(p, k + 1, j) + p[i - 1] * p[k] * p[j];
		if (count < min) { min = count; }
	}
	return min;
}

int main() {
	int arr[] = { 1, 2, 3, 4, 3 };
	int N = sizeof(arr) / sizeof(arr[0]);

	printf("The minimum number of multiplication needed is %d\n",
    matrix_chain(arr, 1, N - 1));
	return 0;
}