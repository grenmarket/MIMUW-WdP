/*
 * Wypisz wszystkie permutacje zbioru {1..n}
 */

#include <stdio.h>
#include <stdlib.h>

void wypisz_h(int n, int* A, int* B, int index) {
    if (index == n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", A[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < n; i++) {
            // czy nieużyty
            if (B[i] == 0) {
                // liczba, czyli +1
                A[index] = i+1;
                // użyty
                B[i] = 1;
                wypisz_h(n, A, B, index+1);
                // trzeba udostępnić tę liczbę
                B[i] = 0;
            }
        }
    }
}

void wypisz(int n) {
    int* A = malloc(n*sizeof(int));
    int* B = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        B[i] = 0;
    }
    wypisz_h(n, A, B, 0);
    free(A);
    free(B);
}

int main() {
    wypisz(3);
}
