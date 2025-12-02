#include <stdbool.h>
#include <stdio.h>

int f(int *A, int *B, int i) {
    return A[i] - B[i];
}

// Binary search for zero in a monotonic section
bool binsearchZero(int *A, int *B, int lewy, int prawy, bool rosnie) {
    while (lewy <= prawy) {
        int mid = lewy + (prawy - lewy) / 2;
        long v = f(A, B, mid);

        if (v == 0) return true;

        if (rosnie) {
            if (v < 0) lewy = mid + 1;
            else prawy = mid - 1;
        } else {
            if (v < 0) prawy = mid - 1;
            else lewy = mid + 1;
        }
    }
    return false;
}

bool tesame(int *A, int *B, int n) {
    int lewy = 0, prawy = n - 1;

    while (lewy < prawy) {
        int mid = lewy + (prawy - lewy) / 2;
        if (f(A, B, mid) > f(A, B, mid + 1))
            lewy = mid + 1;
        else
            prawy = mid;
    }

    int m = lewy;

    long vm = f(A, B, m);
    if (vm == 0) return true;

    // nie może być rozwiązania
    if (vm > 0) return false;

    // lewo
    if (binsearchZero(A, B, 0, m - 1, false))
        return true;

    // prawo
    if (binsearchZero(A, B, m + 1, n - 1, true))
        return true;

    return false;
}

int main() {
    int a[] = {1,2,1,3,1,4,5,9,2,7,1,7,19,26,10,18,5,14};
    int b[] = {10,20,2,11,3,11,6,13,6,12,2,6,15,18,13,15,2,3};

    for (int i = 0; i < 17; i++) {
        printf("%d ", f(a,b,i) - f(a,b,i+1));
    }
}