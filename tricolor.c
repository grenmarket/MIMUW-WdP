#include <stdbool.h>
#include <stdio.h>

bool all_found(bool one, bool two, bool three) {
    return one && two && three;
}

bool tricolor(int N, int a[]) {
    if (N < 3) {
        return false;
    }
    bool white = false;
    bool blue = false;
    bool red = false;
    int i = 0;
    while (!all_found(white, blue, red) && i < N) {
        int curr = a[i];
        if (curr == 0) {
            white = true;
        } else if (curr == 1) {
            blue = true;
        } else if (curr == 2) {
            red = true;
        }
        i++;
    }
    return all_found(white, blue, red);
}

void run_test(int test_num, int a[], int N, bool expected) {
    bool result = tricolor(N, a);
    if (result == expected)
        printf("Test %2d passed\n", test_num);
    else
        printf("Test %2d failed (expected %d, got %d)\n", test_num, expected, result);
}

int main(void) {
    int test_num = 1;

    // 1. Empty array
    int t1[] = {};
    run_test(test_num++, t1, 0, false);

    // 2. Array with only 0
    int t2[] = {0};
    run_test(test_num++, t2, 1, false);

    // 3. Array with only 1
    int t3[] = {1};
    run_test(test_num++, t3, 1, false);

    // 4. Array with only 2
    int t4[] = {2};
    run_test(test_num++, t4, 1, false);

    // 5. Array with 0 and 1, missing 2
    int t5[] = {0, 1, 1, 0};
    run_test(test_num++, t5, 4, false);

    // 6. Array with 0 and 2, missing 1
    int t6[] = {2, 0, 2};
    run_test(test_num++, t6, 3, false);

    // 7. Array with 1 and 2, missing 0
    int t7[] = {1, 2, 2, 1};
    run_test(test_num++, t7, 4, false);

    // 8. Array with 0, 1, and 2 (exact one each)
    int t8[] = {0, 1, 2};
    run_test(test_num++, t8, 3, true);

    // 9. Array with multiple 0s, 1s, 2s
    int t9[] = {0, 0, 1, 2, 1, 2, 0};
    run_test(test_num++, t9, 7, true);

    // 10. Array with 0, 1, 2 scattered randomly
    int t10[] = {5, 7, 0, 3, 1, 8, 9, 2};
    run_test(test_num++, t10, 8, true);

    // 11. Array with no 0/1/2 at all
    int t11[] = {3, 4, 5, 6};
    run_test(test_num++, t11, 4, false);

    // 12. Large array with 2 at end
    int t12[1000];
    for (int i = 0; i < 999; i++) t12[i] = 0;
    t12[999] = 2;
    run_test(test_num++, t12, 1000, false);

    // 13. Large array with all three present
    int t13[1000];
    for (int i = 0; i < 1000; i++) t13[i] = i % 3;
    run_test(test_num++, t13, 1000, true);

    // 14. Array where all 0, 1, 2 appear early
    int t14[] = {2, 1, 0, 5, 9};
    run_test(test_num++, t14, 5, true);

    // 15. Array with negative and large values mixed in
    int t15[] = {-5, 0, 100, 1, 2, 999};
    run_test(test_num++, t15, 6, true);

    printf("\nAll tests completed.\n");
    return 0;
}