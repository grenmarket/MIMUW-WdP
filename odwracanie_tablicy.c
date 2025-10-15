#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

int* reverse(int N, int A[]) {
    if (N == 0 || N == 1) {
        return A;
    }
    int i = 0;
    int j = N-1;
    while (j-i > 0) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        i++;
        j--;
    }
    return A;
}

void print_array(int A[], int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d", A[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]");
}

// Utility to compare arrays for equality
int arrays_equal(int A[], int B[], int N) {
    for (int i = 0; i < N; i++) {
        if (A[i] != B[i]) return 0;
    }
    return 1;
}

// Run a single test
void run_test(const char* test_name, int input[], int expected[], int N) {
    int* arr = malloc(N * sizeof(int));
    memcpy(arr, input, N * sizeof(int));

    printf("Running %s...\n", test_name);
    reverse(N, arr);

    printf("  Input:    ");
    print_array(input, N);
    printf("\n  Expected: ");
    print_array(expected, N);
    printf("\n  Got:      ");
    print_array(arr, N);
    printf("\n");

    assert(arrays_equal(arr, expected, N) && "Test failed!");
    printf("✅ %s passed.\n\n", test_name);

    free(arr);
}

int main(void) {
    // --- TEST 1: Empty array ---
    {
        int input[] = {};
        int expected[] = {};
        run_test("Test 1: Empty array", input, expected, 0);
    }

    // --- TEST 2: Single element ---
    {
        int input[] = {42};
        int expected[] = {42};
        run_test("Test 2: Single element", input, expected, 1);
    }

    // --- TEST 3: Two elements ---
    {
        int input[] = {1, 2};
        int expected[] = {2, 1};
        run_test("Test 3: Two elements", input, expected, 2);
    }

    // --- TEST 4: Odd number of elements ---
    {
        int input[] = {1, 2, 3, 4, 5};
        int expected[] = {5, 4, 3, 2, 1};
        run_test("Test 4: Odd length array", input, expected, 5);
    }

    // --- TEST 5: Even number of elements ---
    {
        int input[] = {10, 20, 30, 40};
        int expected[] = {40, 30, 20, 10};
        run_test("Test 5: Even length array", input, expected, 4);
    }

    // --- TEST 6: Negative numbers ---
    {
        int input[] = {-1, -2, -3, -4, -5};
        int expected[] = {-5, -4, -3, -2, -1};
        run_test("Test 6: Negative numbers", input, expected, 5);
    }

    // --- TEST 7: Duplicates ---
    {
        int input[] = {1, 2, 2, 3, 3, 3, 4};
        int expected[] = {4, 3, 3, 3, 2, 2, 1};
        run_test("Test 7: Duplicates", input, expected, 7);
    }

    // --- TEST 8: Already reversed array ---
    {
        int input[] = {9, 8, 7, 6};
        int expected[] = {6, 7, 8, 9};
        run_test("Test 8: Already reversed array", input, expected, 4);
    }

    // --- TEST 9: Large numbers ---
    {
        int input[] = {1000000, 2000000, 3000000};
        int expected[] = {3000000, 2000000, 1000000};
        run_test("Test 9: Large numbers", input, expected, 3);
    }

    // --- TEST 10: Large array ---
    {
        int N = 1000;
        int* input = malloc(N * sizeof(int));
        int* expected = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            input[i] = i;
            expected[i] = N - i - 1;
        }
        run_test("Test 10: Large array (1000 elements)", input, expected, N);
        free(input);
        free(expected);
    }

    printf("🎉 All tests passed successfully!\n");
    return 0;
}
