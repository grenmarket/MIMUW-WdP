#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int najdluzszy_segment_schodkowy(int a[], int n) {
    if (n == 0) return 0;
    int p = 0, i = 1;
    int max = 0;
    if (a[0] == 1) {
        max = 1;
    }
    while (i < n) {
        if (a[i] == a[i-1]-1) {
            if (a[i] <= i-p+1 && a[i] >= 1) {
                if (a[i] > max) {
                    max = a[i];
                }
            }
        } else {
            p = i;
            if (max == 0 && a[i] == 1) {
                max = 1;
            }
        }
        i++;
    }
    return max;
}

int brute_force(int a[], int n) {
    int best = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int ok = 1;
            /* Condition: step -1 for every consecutive pair inside [i..j] */
            for (int k = i + 1; k <= j; ++k) {
                if (a[k] != a[k-1] - 1) { ok = 0; break; }
            }
            if (!ok) continue;
            /* Condition: a[j] must equal length (j-i+1) */
            int len = j - i + 1;
            if (a[j] != len) continue;
            if (len > best) best = len;
        }
    }
    return best;
}

void run_test(int a[], int n, const char *name) {
    int expected = brute_force(a, n);
    int got = najdluzszy_segment_schodkowy(a, n);

    if (expected == got) {
        printf("[PASS] %-28s n=%2d result=%d\n", name, n, got);
    } else {
        printf("[FAIL] %-28s n=%2d got=%d expected=%d\n", name, n, got, expected);
        /* Print array for debugging */
        printf("  array: {");
        for (int i = 0; i < n; ++i) {
            printf("%d", a[i]);
            if (i+1 < n) printf(", ");
        }
        printf("}\n");
    }
}

int main() {
    /* Seed random */
    srand((unsigned)time(NULL));

    /* === Example from the prompt ===
       int a[] = {6,5,4,3,7,6,5,4,3,2}
       Expected longest staircase segment = 4 (the segment 7,6,5,4 at indices 4..7,
       because it's step-1 and a[7] == 4)
    */
    int t_example[] = {6,5,4,3,7,6,5,4,3,2};
    run_test(t_example, 10, "Prompt example");

    /* === Hand-picked cases === */
    int t1[] = {5,4,3,2,1}; /* end values: 1 at j=4 (len=5?) => a[4]=1 !=5 ; but there are
                               smaller subsegments that may match (e.g., 4,3,2,1 where a[j]=1 == len4? no)
                               this tests various interactions */
    run_test(t1, 5, "Monotone decreasing");

    int t2[] = {4,3,2,1}; /* 4,3,2,1 (len4) a[3]=1 !=4 -> but segment 1-length maybe if a[j]==1 etc */
    run_test(t2, 4, "Decreasing small");

    int t3[] = {7,6,5,4}; /* this has segment 7,6,5,4 length4 a[3]=4 -> matches -> expected 4 */
    run_test(t3, 4, "Perfect match at end");

    int t4[] = {1,1,1,1}; /* no step-1 runs >1; singletons with a[j]==1 count; expected 1 */
    run_test(t4, 4, "All ones");

    int t5[] = {2,1,1,1}; /* a[1]=1 and segment 0..1: 2,1 step ok, len2 but a[1]==1 !=2 -> invalid.
                              singletons with value 1 count */
    run_test(t5, 4, "Leading 2 then ones");

    int t6[] = {3,2,1,3,2,1,4,3,2,1}; /* multiple runs; check best detection */
    run_test(t6, 10, "Multiple runs");

    int t7[] = {10}; run_test(t7, 1, "Single element (10)"); /* a[0]!=1 -> expected 0 */
    int t8[] = {1}; run_test(t8, 1, "Single element (1)");   /* a[0]==1 -> expected 1 */

    int t9[] = {5,4,3,2}; /* a[3]==2 but len=4 -> doesn't match; maybe subsegments qualify */
    run_test(t9, 4, "Len mismatch");

    int t10[] = {3,2,1,0,-1,-2,-3}; /* the last element -3 cannot equal positive length -> expect 0 or maybe smaller */
    run_test(t10, 7, "Negative tail");

    int t11[] = {4,3,2,1, 3,2,1, 5,4,3,2,1}; /* best is 5 at the end (5,4,3,2,1 with a[j]==1? no),
                                                  but actually 5,4,3,2,1: last is 1 !=5 => invalid.
                                                  There might be a smaller matching segment. Tests nuanced cases. */
    run_test(t11, 12, "Complex pattern");

    int t12[] = {7,6,5,4,3,2,1,4}; /* check segments finishing where a[j]==len */
    run_test(t12, 8, "Long then short");

    /* The array that should have a 4-length segment matching the rule (7,6,5,4) */
    int t13[] = {0,7,6,5,4,9}; run_test(t13, 6, "Embedded 7,6,5,4");

    /* Edge case: empty array */
    int empty[1];
    run_test(empty, 0, "Empty array");

    /* === Deterministic crafted tests to assert known outputs === */
    /* 7,6,5,4 is at indices 4..7 of the prompt example and yields 4 -> already tested above */

    /* === Random tests with verification by brute force === */
    for (int trial = 0; trial < 50; ++trial) {
        int n = 1 + (rand() % 25); /* length 1..25 */
        int a[30];
        for (int i = 0; i < n; ++i) {
            /* to increase chance of step runs, bias numbers moderately */
            a[i] = (rand() % 12) + (rand() % 6); /* small-ish numbers 0..17 */
            if ((rand() & 7) == 0) {
                /* occasionally insert larger numbers */
                a[i] += (rand() % 40);
            }
            if ((rand() & 31) == 0) {
                /* occasionally insert negative */
                a[i] = - (rand() % 10);
            }
        }
        char name[40];
        sprintf(name, "Random test %02d", trial+1);
        run_test(a, n, name);
    }

    return 0;
}