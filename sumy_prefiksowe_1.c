/*
 * Segment nieparzysty - spójny podciąg 0<=i<=j<=n taki że suma elementów jest nieparzysta.
 * Znajdź liczbę takich segmentów.
 *
 * np. [1,1,1,1...] tablica n elementów: n + (n-2) + (n-4) + ...
 * czyli segmenty dł. 1, 3, 5...
 *
 * Suma prefiksowa dla i - ściśle przed i.
 */

#include <stdio.h>

int segmenty(int a[], int n) {
    int parz = 1;
    int niep = 0;
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += a[i];
        if (suma % 2 == 0) {
            parz++;
        } else {
            niep++;
        }
    }
    return parz * niep;
}

int main() {
    int a[] = {2,0,2,5,2,1,3,7,6,7};
    printf("%d", segmenty(a, 10));
}