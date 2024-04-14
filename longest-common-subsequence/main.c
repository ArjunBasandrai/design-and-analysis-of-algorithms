#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

int main() {
    char str1[64], str2[64];

    printf("Enter the first string: ");
    fgets(str1, 64, stdin);
    printf("Enter the second string: ");
    fgets(str2, 64, stdin);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int** dp = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int i = len1, j = len2, l = 0;
    char *string = (char *)malloc(len1 * sizeof(char));
    while (i != 0 && j != 0) {
        if (dp[i][j] == dp[i][j - 1]) {
            j--;
        } else {
            string[l] = str2[j - 1];
            l++;
            i--;
            j--;
        }
    }
    
    printf("The longest common sub sequence is: ");
    for (i = l - 1; i >= 0; i--) {
        printf("%c", string[i]);
    }

    free(string);
    for (int i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}