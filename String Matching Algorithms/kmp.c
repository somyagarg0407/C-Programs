#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_LENGTH 1000000
static char text[MAX_LENGTH + 2];
static char pattern[MAX_LENGTH + 2];
static int lps[MAX_LENGTH + 2];
static volatile unsigned long long benchmarkSink;
void trimNewline(char s[]) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}
void buildLPS(const char pattern[], int m, int lps[]) {
    int len = 0;
    int i = 1;
    lps[0] = 0;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
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
}
int kmpSearch(const char text[], const char pattern[], int n, int m, const int lps[], int printMatches) {
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            count++;
            if (printMatches) {
                printf("Pattern found at index: %d\n", i - j);
            }
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}
double measureKMP(const char text[], const char pattern[], int n, int m, int lps[], int *runs) {
    clock_t start, end;
    double elapsed;
    int count;
    start = clock();
    buildLPS(pattern, m, lps);
    count = kmpSearch(text, pattern, n, m, lps, 0);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    benchmarkSink = (unsigned long long)count;
    *runs = 1;
    if (elapsed < 0.01) {
        int repetitions;
        unsigned long long checksum = 0;
        if (elapsed > 0.0) {
            repetitions = (int)(0.01 / elapsed) + 1;
        } else {
            repetitions = 100000;
        }
        if (repetitions > 1000000) {
            repetitions = 1000000;
        }
        start = clock();
        for (int r = 0; r < repetitions; r++) {
            buildLPS(pattern, m, lps);
            checksum += (unsigned int)kmpSearch(text, pattern, n, m, lps, 0);
        }
        end = clock();
        benchmarkSink = checksum;
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        *runs = repetitions;
    }
    return elapsed / (*runs);
}
int main() {
    int n, m, total, runs;
    double avgTime;
    printf("Enter the text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 0;
    }
    trimNewline(text);
    printf("Enter the pattern: ");
    if (fgets(pattern, sizeof(pattern), stdin) == NULL) {
        return 0;
    }
    trimNewline(pattern);
    n = (int)strlen(text);
    m = (int)strlen(pattern);
    if (m == 0) {
        printf("Error: Pattern cannot be empty.\n");
        return 0;
    }
    avgTime = measureKMP(text, pattern, n, m, lps, &runs);
    buildLPS(pattern, m, lps);
    printf("\nLPS Array: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", lps[i]);
    }
    printf("\n");
    total = kmpSearch(text, pattern, n, m, lps, 1);
    if (total == 0) {
        printf("Pattern not found in the text.\n");
    }
    printf("Total occurrences: %d\n", total);
    if (avgTime < 0.001) {
        printf("Average Execution Time (KMP Algorithm): %.3f microseconds (%d runs)\n", avgTime * 1000000.0, runs);
    } else {
        printf("Average Execution Time (KMP Algorithm): %.6f milliseconds (%d runs)\n", avgTime * 1000.0, runs);
    }
    return 0;
}