#include <stdio.h>
#include <stdlib.h>

static inline int min3(int a, int b, int c) {
    int m = (a < b) ? a : b;
    return (m < c) ? m : c;
}

// Returns area of the largest all-1s square
int largest_square_ones(int **mat, int R, int C) {
    int *dp = (int*)calloc(C, sizeof(int));  // dp[c] = dp value for current row at column c
    int prev_diag = 0;                       // dp[r-1][c-1]
    int best_side = 0;

    for (int r = 0; r < R; r++) {
        prev_diag = 0;
        for (int c = 0; c < C; c++) {
            int temp = dp[c]; // saves old dp[c] == dp[r-1][c] before overwriting

            if (mat[r][c] == 1) {
                if (r == 0 || c == 0) {
                    dp[c] = 1;
                } else {
                    dp[c] = 1 + min3(dp[c],          // top    = dp[r-1][c]
                                     (c > 0 ? dp[c-1] : 0), // left   = dp[r][c-1]
                                     prev_diag);     // diag   = dp[r-1][c-1]
                }
                if (dp[c] > best_side) best_side = dp[c];
            } else {
                dp[c] = 0;
            }

            prev_diag = temp; // move diag for next column
        }
    }

    free(dp);
    return best_side * best_side; // area
}
