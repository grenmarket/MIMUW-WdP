#include <stdio.h>

void print(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", A[i]);
    }
    printf(" ");
}

void hanoi_h(int A[], int index, int n1, int n2) {
    if (n1 == 0 && n2 == 0) {
        print(A, index);
    } else {
        if (n1 > 0) {
            A[index] = 1;
            hanoi_h(A, index + 1, n1 - 1, n2 + 1);
        }
        if (n2 > 0) {
            A[index] = 2;
            hanoi_h(A, index + 1, n1, n2 - 1);
        }
    }
}

void hanoi(int n) {
    int A[2*n];
    hanoi_h(A, 0, n, 0);
}

int main() {
    hanoi(5);
    return 0;
}