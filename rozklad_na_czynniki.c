#include <stdio.h>
void r(int n, int toUse, int A[], int index) {
    if (toUse == 1) {
        printf("%d = ", n);
        for (int i = 0; i < index; i++) {
            if (i > 0) {
                printf(" * ");
            }
            printf("%d", A[i]);
        }
        printf("\n");
    } else {
        int start = index == 0 ? 2 : A[index - 1];
        for (int i = start; i <= n; i++) {
            if (toUse % i == 0) {
                A[index] = i;
                r(n, toUse/i, A, index+1);
            }
        }
    }
}

void rozklad(int n) {
    int A[n];
    r(n, n, A, 0);
}

int main() {
    rozklad(100);
}