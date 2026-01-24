#include <stdio.h>
#include <stdlib.h>

static int max_int(int a, int b) { return a > b ? a : b; }

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        fprintf(stderr, "Bledne n/m.\n");
        return 1;
    }

    // Alokacja macierzy A
    unsigned char *A = (unsigned char*)malloc((size_t)n * (size_t)m);
    if (!A) { fprintf(stderr, "Brak pamieci.\n"); return 1; }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            if (scanf("%d", &x) != 1 || (x != 0 && x != 1)) {
                fprintf(stderr, "Bledne dane w tablicy.\n");
                free(A);
                return 1;
            }
            A[i*m + j] = (unsigned char)x;
        }
    }

    // Tablice DP: L, R, U, D (liczba kolejnych jedynek w danym kierunku, z komórką włącznie)
    int *L = (int*)calloc((size_t)n * (size_t)m, sizeof(int));
    int *R = (int*)calloc((size_t)n * (size_t)m, sizeof(int));
    int *U = (int*)calloc((size_t)n * (size_t)m, sizeof(int));
    int *D = (int*)calloc((size_t)n * (size_t)m, sizeof(int));
    if (!L || !R || !U || !D) {
        fprintf(stderr, "Brak pamieci (DP).\n");
        free(A); free(L); free(R); free(U); free(D);
        return 1;
    }

    // L i U: przebieg od góry-lewej do dołu-prawej
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i*m + j] == 1) {
                L[i*m + j] = 1 + (j > 0 ? L[i*m + (j-1)] : 0);
                U[i*m + j] = 1 + (i > 0 ? U[(i-1)*m + j] : 0);
            }
        }
    }

    // R i D: przebieg od dołu-prawej do góry-lewej
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (A[i*m + j] == 1) {
                R[i*m + j] = 1 + (j + 1 < m ? R[i*m + (j+1)] : 0);
                D[i*m + j] = 1 + (i + 1 < n ? D[(i+1)*m + j] : 0);
            }
        }
    }

    // Szukamy najlepszego skrzyżowania
    int best_i = -1, best_j = -1;
    int best_sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i*m + j] == 1) {
                int sum = L[i*m + j] + R[i*m + j] + U[i*m + j] + D[i*m + j] - 3;
                if (sum > best_sum) {
                    best_sum = sum;
                    best_i = i;
                    best_j = j;
                }
            }
        }
    }

    if (best_i == -1) {
        // brak jedynek
        printf("Brak elementu (tablica nie zawiera jedynek).\n");
    } else {
        // Wypisujemy współrzędne i wynik; indeksy 0..n-1, 0..m-1 jak w treści
        printf("Najlepsze skrzyzowanie: (%d, %d)\n", best_i, best_j);
        printf("Maksymalna laczna dlugosc korytarzy (z komorka raz): %d\n", best_sum);

        // (opcjonalnie) długości w czterech kierunkach "od komórki" bez podwójnego liczenia:
        // w lewo bez komórki: L-1, w prawo: R-1 itd.
        printf("Lewo=%d Prawo=%d Gora=%d Dol=%d (liczby jedynek od komorki wlacznie)\n",
               L[best_i*m + best_j], R[best_i*m + best_j],
               U[best_i*m + best_j], D[best_i*m + best_j]);
    }

    free(A); free(L); free(R); free(U); free(D);
    return 0;
}
