#include <stdio.h>
#include <stdlib.h>

int largest_rectangle_ones_dp(int **mat, int R, int C) {
    int **width = (int**)malloc(R * sizeof(int*));
    for (int r = 0; r < R; r++) {
        width[r] = (int*)calloc(C, sizeof(int));
    }

    // DP: width[r][c] = consecutive ones ending at (r,c) to the left
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (mat[r][c] == 1) {
                width[r][c] = (c == 0) ? 1 : width[r][c - 1] + 1;
            } else {
                width[r][c] = 0;
            }
        }
    }

    int best = 0;

    // For each cell as bottom-right, expand upward
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (width[r][c] == 0) continue;

            int minWidth = width[r][c];
            for (int up = r; up >= 0 && width[up][c] > 0; up--) {
                if (width[up][c] < minWidth) minWidth = width[up][c];
                int height = r - up + 1;
                int area = minWidth * height;
                if (area > best) best = area;
            }
        }
    }

    for (int r = 0; r < R; r++) free(width[r]);
    free(width);

    return best;
}