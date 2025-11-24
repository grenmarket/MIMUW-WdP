#include <stdio.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int odd(int a) {
    return a % 2 != 0 ? a : a - 1;
}

void r(int n, int toUse, int max, int A[], int index) {
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
        for (int i = odd(min(toUse, max)); i >= 1; i -= 2) {
            A[index] = i;
            r(n, toUse - i, i, A, index+1);
        }
    }
}

void rozklad(int n) {
    int A[n];
    r(n, n, n, A, 0);
}

int main() {
    rozklad(10);
}