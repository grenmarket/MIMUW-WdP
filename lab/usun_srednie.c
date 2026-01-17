#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


struct lista {
    int w;
    struct lista *popr;
    struct lista *nast;
};

typedef struct lista Tlista;

/* ===== PODSTAWOWE OPERACJE NA LIŚCIE ===== */

Tlista *nowy(int w, Tlista *nast) {
    Tlista *wynik = malloc(sizeof *wynik);
    assert(wynik != NULL);
    wynik->w = w;
    wynik->popr = nast == NULL ? NULL : nast->popr;
    wynik->nast = nast;
    if (nast) {
        nast->popr = wynik;
    }
    return wynik;
}

Tlista *czytaj(void) {
    Tlista *wartownik = nowy(0, NULL);
    Tlista *p = wartownik;

    int w;
    while (scanf("%d", &w) == 1) {
        p->nast = nowy(w, NULL);
        p->nast->popr = p;
        p = p->nast;
    }

    Tlista *wynik = wartownik->nast;
    free(wartownik);
    return wynik;
}

void pisz(Tlista *l) {
    while (l != NULL) {
        printf("%d ", l->w);
        l = l->nast;
    }
    printf("\n");
}

void usun(Tlista *l) {
    while (l != NULL) {
        Tlista *p = l;
        l = l->nast;
        free(p);
    }
}

/* ===== ROZWIĄZANIE ZADANIA ===== */

void usun_srednie(Tlista **glowa) {
    Tlista *srodkowy = (*glowa)->nast;
    Tlista *poprzedni = srodkowy->popr;
    int poprz_wartosc = poprzedni->w;
    while (srodkowy != NULL) {
        Tlista *nastepny = srodkowy->nast;
        if (nastepny != NULL && 2*srodkowy->w == nastepny->w + poprz_wartosc) {
            poprzedni->nast = nastepny;
            nastepny->popr = poprzedni;
            poprz_wartosc = srodkowy->w;
            free(srodkowy);
        } else {
            poprzedni = poprzedni->nast;
            poprz_wartosc = poprzedni->w;
        }
        srodkowy = nastepny;
    }
}

int main(void) {
    Tlista *lista = czytaj();

    printf("Lista przed usunięciem średnich: ");
    pisz(lista);

    usun_srednie(&lista);

    printf("Lista po usunięciu średnich: ");
    pisz(lista);

    usun(lista);
    return 0;
}

