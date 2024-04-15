#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rabinkarp(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    int d = 256;
    int q = 101;

    // h = pow(d, m - 1) % q
    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                printf("Pattern found at index %d\n", i);
            }
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            // t might become negative, so we need to make it positive
            if (t < 0) {
                t = t + q;
            }
        }
    }


}

int main() {
    char text[256];
    char pattern[256];

    printf("Enter the text: ");
    fgets(text, 256, stdin);
    printf("Enter the pattern: ");
    fgets(pattern, 256, stdin);

    text[strlen(text) - 1] = '\0';
    pattern[strlen(pattern) - 1] = '\0';

    rabinkarp(text, pattern);

    return 0;
}