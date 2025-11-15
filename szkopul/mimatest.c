#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min_max(int a1, int b1, int a2, int b2) {
    int c1 = (a1 > b1) ? a1 : b1;
    int c2 = (a2 > b2) ? a2 : b2;
    return c1 < c2 ? c1 : c2;
}

int mima_h(int N, int A[], int B[], int i, int j) {
    if (i == j) {
        return A[i] > B[i] ? A[i] : B[i];
    }
    if (i + 1 == j) {
        return min_max(A[i], B[i], A[j], B[j]);
    }
    if (A[i] > B[i]) {
        return mima_h(N, A, B, i, i);
    }
    if (B[j] > A[j]) {
        return mima_h(N, A, B, j, j);
    }
    int s = (i+j)/2;
    if (B[s] >= A[s]) {
        return mima_h(N, A, B, s, j);
    } else {
        return mima_h(N, A, B, i, s);
    }
}

int mima(int N, int A[], int B[]) {
    return mima_h(N, A, B, 0, N-1);
}

void random_non_decreasing(int N, int *arr) {
    int first = (rand() % 41) - 20;
    arr[0] = first;
    for (int i = 1; i < N; i++) {
        arr[i] = arr[i-1] + (rand() % 4);
    }
}

void random_non_increasing(int N, int *arr) {
    int first = (rand() % 51) - 25;
    arr[0] = first;
    for (int i = 1; i < N; i++) {
        arr[i] = arr[i-1] - (rand() % 4);
    }
}

int bruteforce(int N, int A[], int B[]) {
    int min_max = 10000;
    for (int i = 0; i < N; i++) {
        int max = A[i] > B[i] ? A[i] : B[i];
        if (max < min_max) {
            min_max = max;
        }
    }
    return min_max;
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < 10000000; i++) {
        int n = rand() % 100;
        if (n == 0) {
            n = 1;
        }
        int A[n];
        random_non_decreasing(n, A);
        int B[n];
        random_non_increasing(n, B);
        int br = bruteforce(n, A, B);
        int mi = mima(n, A, B);
        if (br != mi) {
            printf("%d/%d\n", br, mi);
        }
    }
}
