/**
Elementy e1 i e2 listy prostej l nazwiemy zaprzyjaźnionymi w l jeżeli:
 - liczba elementów znajdujących się przed e1 w l jest równa liczbie elementów znajdujących się za e2 w l,
 - suma wartości w elementach znajdujących się przed e1 (bez e1) jest równa sumie wartości w elementach znajdujących się przed e2 (bez e2) w l.

Elementy, które nie są zaprzyjaźnione z żadnym elementem w l nazwiemy samotnymi w l. Element może być zaprzyjaźniony z samym sobą.

Napisz funkcję: int ile_samotnych(Tlista *l);
która określi liczbę elementów samotnych listy l.
**/

#include <stddef.h>

typedef struct Tlista {
    int w;
    struct Tlista *nast;
} Tlista;

Tlista *odwroc(Tlista *l) {
    Tlista *l2 = NULL;
    while (l) {
        Tlista *w = l;
        l = l->nast;
        w->nast = l2;
        l2 = w;
    }
    return l2;
}

int ile_samotnych(Tlista *l) {
    int n = 0; // liczba elementow listy
    int suma = 0; // suma elementow listy
    Tlista *w = l, *w2;
    while (w) {
        n++;
        suma += w->w;
        w = w->nast;
    }

    int m = n / 2;
    if (m == 0)
        return 0;
    Tlista *k1 = l; // k1: koniec 1-szej czesci
    for (int i = 0; i < m - 1; i++)
        k1 = k1->nast;
    Tlista *l2 = odwroc(k1->nast); // poczatek 2-giej czesci
    k1->nast = NULL;

    int wynik = 2 * m;
    int suma1 = 0, suma2 = 0;
    w = l, w2 = l2;
    while (w && w2) {
        suma2 += w2->w;
        if (suma1 == suma - suma2)
            wynik -= 2;
        suma1 += w->w;
        w = w->nast;
        w2 = w2->nast;
    }

    k1->nast = odwroc(l2);
    return wynik;
}
