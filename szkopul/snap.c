/*
Dana jest tablica A zawierająca N liczb całkowitych różnych od zera (0 ≤ N ≤ 1 000 000). Ustaw wartość
zmiennej wynik na maksymalną sumę segmentu naprzemiennego, tj. takiego, w którym każde dwa kolejne
elementy mają przeciwne znaki (zgodnie z tą definicją segment pusty jest naprzemienny i ma sumę 0).
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik;

    wynik = 0;
    if (N == 0) {
        printf("%d\n", wynik);
        return 0;
    }
    if (N == 1) {
        if (A[0] > 0) {
            wynik = A[0];
        }
        printf("%d\n", wynik);
        return 0;
    }
    int segment_start[N];
    int mins[N];
    int sums[N];

    int last = 0;

    for (int i = 0; i < N; i++) {
        if (A[i] > 0) {
            if (last == -1) {
                segment_start[i] = segment_start[i - 1];
                sums[i] = sums[i - 1] + A[i];
            } else {
                segment_start[i] = i;
                sums[i] = A[i];
            }
            last = 1;
        } else {
            if (last == 1) {
                segment_start[i] = segment_start[i - 1];
                sums[i] = sums[i - 1] + A[i];
            } else {
                segment_start[i] = i;
                sums[i] = A[i];
            }
            last = -1;
        }
    }
    int m = N - 1;
    while (m >= 0) {
        int j = segment_start[m];
        int c = 0;
        int min = 0;
        while (j <= m) {
            if (c < 1) {
                mins[j] = 0;
                c++;
            } else {
                int curr = sums[j - 1];
                if (curr < min) {
                    min = curr;
                }
                mins[j] = min;
            }
            j++;
        }
        m = segment_start[m] - 1;
    }

    int i = N - 1;
    while (i >= 0) {
        int j = segment_start[i];
        for (int k = j; k <= i; k++) {
            int curr = sums[k] - mins[k];
            if (curr > wynik) {
                wynik = curr;
            }
        }
        i = j - 1;
    }

    printf("%d\n", wynik);
    return 0;
}
