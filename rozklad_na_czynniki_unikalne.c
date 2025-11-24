#include <stdio.h>

int min(int a, int b) {
    return a < b ? a : b;
}

void r(int n, int toUse, int max, int A[], int index, int used[]) {
    if (toUse == 0) {
        printf("%d = ", n);
        for (int i = 0; i < index; i++) {
            if (i > 0) {
                printf(" + ");
            }
            printf("%d", A[i]);
        }
        printf("\n");
    } else {
        for (int i = min(toUse, max); i >= 1; i--) {
            if (used[i] == 0) {
                A[index] = i;
                used[i] = 1;
                r(n, toUse - i, i, A, index+1, used);
            }
        }
        for (int i = 0; i < n; i++) {
            used[i] = 0;
        }
    }
}

void rozklad(int n) {
    int A[n];
    int used[n];
    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }
    r(n, n, n, A, 0, used);
}

int main() {
    rozklad(10);
}