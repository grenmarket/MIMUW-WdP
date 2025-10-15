#include <stdio.h>

int maks(int N, int a[]) {
    if (N == 0) {
        return 0;
    }
    int b[N+1];
    b[0] = 0;
    for (int i = 0; i < N; i++) {
        b[i+1] = b[i] + a[i];
    }
    int mins[N+1];
    mins[0] = 0;
    int min = 0;
    for (int i = 1; i<=N; i++) {
        if (b[i] < min) {
            min = b[i];
        }
        mins[i] = min;
    }
    int max = 0;
    for (int i = 0; i<=N; i++) {
        int curr = b[i] - mins[i];
        if (curr > max) {
            max = curr;
        }
    }
    return max;
}

static void run_test(const char *name, int a[], int n, int expected, int *passed, int *total) {
    int got = maks(n, a);
    (*total)++;
    if (got == expected) {
        printf("%-30s: expected %d, got %d — PASS\n", name, expected, got);
        (*passed)++;
    } else {
        printf("%-30s: expected %d, got %d — FAIL\n", name, expected, got);
    }
}

int main(void) {
    int passed = 0, total = 0;

    // Test 1: empty array -> expected 0
    int *empty = NULL;
    run_test("Empty array", empty, 0, 0, &passed, &total);

    // Test 2: single positive element
    int t2[] = {5};
    run_test("Single positive", t2, 1, 5, &passed, &total);

    // Test 3: single negative element -> expected 0 (empty segment)
    int t3[] = {-7};
    run_test("Single negative", t3, 1, 0, &passed, &total);

    // Test 4: all positive -> sum of all
    int t4[] = {1, 2, 3, 4};
    run_test("All positive", t4, 4, 10, &passed, &total);

    // Test 5: all negative -> expected 0
    int t5[] = {-1, -2, -3, -4};
    run_test("All negative", t5, 4, 0, &passed, &total);

    // Test 6: mixed numbers -> max in middle
    int t6[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    run_test("Mixed numbers", t6, 9, 6, &passed, &total); // 4 + (-1)+2+1=6

    // Test 7: max at start
    int t7[] = {3, 2, -1, -2};
    run_test("Max at start", t7, 4, 5, &passed, &total); // 3+2

    // Test 8: max at end
    int t8[] = {-2, -1, 2, 3};
    run_test("Max at end", t8, 4, 5, &passed, &total); // 2+3

    // Test 9: single large negative in middle
    int t9[] = {1, 2, -100, 3, 4};
    run_test("Large negative middle", t9, 5, 7, &passed, &total); // 3+4

    // Test 10: all zeros
    int t10[] = {0, 0, 0, 0};
    run_test("All zeros", t10, 4, 0, &passed, &total);

    // Test 11: alternating positive and negative
    int t11[] = {1, -1, 2, -2, 3, -3, 4};
    run_test("Alternating", t11, 7, 4, &passed, &total); // max is last 4 alone

    printf("\nSummary: passed %d/%d tests.\n", passed, total);

    return 0;
}
