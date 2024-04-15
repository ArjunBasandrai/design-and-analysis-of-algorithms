#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* compute_lps(char* pattern, int m) {
    int* lps = (int*)malloc(sizeof(int) * m);
    lps[0] = 0;
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            lps[i] = ++len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

void kmp(char* text, char* pattern) {
    int n = strlen(text) - 1;
    int m = strlen(pattern) - 1;
    int* lps = compute_lps(pattern, m);

    int i = 0;
    int j = 0;

    int found = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            found = 1;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    if (!found) printf("Pattern not found\n");
    free(lps);
}

int main() {
    char text[255];
    char pattern[50];

    printf("Enter the text: ");
    fgets(text, 255, stdin);
    printf("Enter the pattern: ");
    fgets(pattern, 50, stdin);

    kmp(text, pattern);

    return 0;
}