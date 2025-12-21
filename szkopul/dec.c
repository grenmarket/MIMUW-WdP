
#include <stdio.h>

int dec(int A[], int B[], int n) {
    int i = 0;
    int j = 0;
    int finished = 0;
    int div = 1;
    while (!finished) {
        if (A[i] == 0 && B[i] == 0) {
            i++;
            j++;
        } else {
            if (B[i] == 0) {
                while (B[j] == 0) {
                    j++;
                }
                while (div && j < n) {
                    if (B[j] == A[i]) {
                        j++;
                        i++;
                    } else {
                        div = 0;
                        finished = 1;
                    }
                }
                if (div && i < n) {
                    if (A[i] == 0) {
                        i++;
                    } else {
                        div = 0;
                        finished = 1;
                    }
                }
                finished = 1;
            } else {
                while (A[j] == 0) {
                    j++;
                }
                while (div && j < n) {
                    if (A[j] == B[i]) {
                        j++;
                        i++;
                    } else {
                        div = 0;
                        finished = 1;
                    }
                }
                if (div && i < n) {
                    if (B[i] == 0) {
                        i++;
                    } else {
                        div = 0;
                        finished = 1;
                    }
                }
                finished = 1;
            }
        }
    }
    return div;
}

int main() {
    int n;
    scanf("%d", &n);
    int A[n];
    int B[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }
    printf("%d\n", dec(A, B, n));
}
