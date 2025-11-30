#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR_START 4
#define MNOZNIK 2

void znajdz_palindrom(int *tablica, int n, int *poczatek, int *dlugosc) {
    int max = 1;
    int start = 0;

    for (int i = 0; i < n; i++) {
        int l = i;
        int r = i;
        while (l >= 0 && r < n && tablica[l] == tablica[r]) {
            int dl = r - l + 1;
            if (dl > max) {
                max = dl;
                start = l;
            }
            l--;
            r++;
        }

        l = i;
        r = i + 1;
        while (l >= 0 && r < n && tablica[l] == tablica[r]) {
            int dl = r - l + 1;
            if (dl > max) {
                max = dl;
                start = l;
            }
            l--;
            r++;
        }
    }

    *poczatek = start;
    *dlugosc = max;
}

int main() {
    int *tablica = NULL;
    int rozmiar = 0;
    int pojemnosc = 0;

    int x;
    int wynik = scanf("%d", &x);

    while (wynik != EOF) {
        if (pojemnosc == rozmiar) {
            pojemnosc = (pojemnosc == 0 ? ROZMIAR_START : pojemnosc * MNOZNIK);
            int *nowa = realloc(tablica, pojemnosc * sizeof(int));
            assert(nowa != NULL);
            tablica = nowa;
        }
        tablica[rozmiar] = x;
        rozmiar++;
        wynik = scanf("%d", &x);
    }

    int poczatek;
    int dlugosc;
    znajdz_palindrom(tablica, rozmiar, &poczatek, &dlugosc);

    for (int i = 0; i < dlugosc; i++) {
        printf("%d ", tablica[poczatek + i]);
    }
    printf("\n");

    free(tablica);
    return 0;
}