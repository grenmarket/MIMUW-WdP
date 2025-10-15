#include <stdio.h>

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int find(int N, int a[]) {
    if (N == 0) {
        return 0;
    }
    int longest = 1;
    int len = 1;
    int curr = a[0];
    int i = 1;
    while (i < N) {
        if (a[i] == curr) {
            len += 1;
        } else {
            longest = max(len, longest);
            len = 1;
            curr = a[i];
        }
        i++;
    }
    longest = max(len, longest);
    return longest;
}

static void run_test(const char *name, int a[], int n, int expected, int *passed, int *total) {
    int got = find(n, a);
    (*total)++;
    if (got == expected) {
        printf("%-28s: expected %d, got %d — PASS\n", name, expected, got);
        (*passed)++;
    } else {
        printf("%-28s: expected %d, got %d — FAIL\n", name, expected, got);
    }
}

int main(void) {
    int passed = 0, total = 0;

        /* Test 1: empty array -> expected 0
           We represent empty array by passing NULL with length 0. */
        int *empty = NULL;
        run_test("Empty array", empty, 0, 0, &passed, &total);

        /* Test 2: single element -> expected 1 */
        int t2[] = {5};
        run_test("Single element", t2, sizeof(t2)/sizeof(t2[0]), 1, &passed, &total);

        /* Test 3: all unique -> expected 1 */
        int t3[] = {1, 2, 3, 4};
        run_test("All unique", t3, sizeof(t3)/sizeof(t3[0]), 1, &passed, &total);

        /* Test 4: all identical -> expected length */
        int t4[] = {7, 7, 7, 7};
        run_test("All identical", t4, sizeof(t4)/sizeof(t4[0]), 4, &passed, &total);

        /* Test 5: longest run in the middle -> expected 3 */
        int t5[] = {1, 1, 2, 2, 2, 3};
        run_test("Longest in middle", t5, sizeof(t5)/sizeof(t5[0]), 3, &passed, &total);

        /* Test 6: longest run at the end -> expected 4 */
        int t6[] = {4, 4, 4, 2, 2, 1, 1, 1, 1};
        run_test("Longest at end", t6, sizeof(t6)/sizeof(t6[0]), 4, &passed, &total);

        /* Test 7: alternating pattern -> expected 1 */
        int t7[] = {1, 2, 1, 2, 1, 2};
        run_test("Alternating", t7, sizeof(t7)/sizeof(t7[0]), 1, &passed, &total);

        /* Test 8: multiple runs of same length -> expected 3 */
        int t8[] = {3, 3, 3, 2, 2, 3, 3};
        run_test("Multiple same-length runs", t8, sizeof(t8)/sizeof(t8[0]), 3, &passed, &total);

        /* Test 9: long run of zeros -> expected 7 */
        int t9[] = {0, 0, 0, 0, 0, 0, 0};
        run_test("All zeros long run", t9, sizeof(t9)/sizeof(t9[0]), 7, &passed, &total);

        /* Test 10: longest run at start -> expected 3 */
        int t10[] = {9, 9, 9, 1, 2, 3, 4};
        run_test("Longest at start", t10, sizeof(t10)/sizeof(t10[0]), 3, &passed, &total);

        /* Test 11: single long run in the middle -> expected 5 */
        int t11[] = {8, 8, 7, 7, 7, 7, 7, 2};
        run_test("Long odd-length middle", t11, sizeof(t11)/sizeof(t11[0]), 5, &passed, &total);

        /* Test 12: negative and positive values -> expected 2 */
        int t12[] = {-1, -1, 0, 1, 1, 2};
        run_test("Neg & pos values", t12, sizeof(t12)/sizeof(t12[0]), 2, &passed, &total);

        /* Test 13: single long element repeated many times (stress-ish moderate) */
        int t13[20];
        for (int i = 0; i < 20; ++i) t13[i] = 42;
        run_test("20 identical elements", t13, 20, 20, &passed, &total);

        /* Summary */
        printf("\nSummary: passed %d/%d tests.\n", passed, total);

        return 0;
}
