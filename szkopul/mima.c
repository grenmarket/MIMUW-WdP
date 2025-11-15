#include <stdio.h>

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

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    int B[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }
    printf("%d\n", mima(N, A, B));
}
