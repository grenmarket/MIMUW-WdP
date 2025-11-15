/*
Dane są dwie tablice A, B liczb całkowitych o długości N. Tablica A jest niemalejąca, tablica B jest nierosnąca.
Znajdź minimalną wartości wyrażenia max(A[k], B[k]) dla k z przedziału [0..N-1].
Wejście
W pierwszym wierszu standardowego wejścia znajduje się jedna liczba całkowita N (1 ≤ N ≤ 1 000 000).
W drugim wierszu znajduje się N liczb oddzielonych odstępami, odpowiadających zawartości tablicy A.
W trzecim wierszu znajduje się N liczb oddzielonych odstępami, odpowiadających zawartości tablicy B.
Wyjście
Jedyny wiersz standardowego wyjścia powinien zawierać liczbę całkowitą oznaczającą znalezioną wartość z
treści zadania, czyli min { max(A[k], B[k]) | k ∈ [0..N-1] }.
*/

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
