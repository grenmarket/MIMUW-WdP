#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* ===== STRUKTURA LISTY ===== */

typedef struct Tlista {
    int w;
    struct Tlista *nast;
} Tlista;

/* ===== PODSTAWOWE OPERACJE NA LIŚCIE ===== */

Tlista *nowy(int w, Tlista *nast, int *suma, int *count) {
    Tlista *wynik = malloc(sizeof *wynik);
    assert(wynik != NULL);
    wynik->w = w;
    wynik->nast = nast;
    (*suma)+=w;
    (*count)++;
    return wynik;
}

Tlista *czytaj(int *suma, int *count) {
    Tlista *wartownik = nowy(0, NULL, suma, count);
    Tlista *p = wartownik;

    int w;
    while (scanf("%d", &w) == 1) {
        p->nast = nowy(w, NULL, suma, count);
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

Tlista* odwroc(Tlista* lista) {
    Tlista* prev = NULL;
    Tlista* next;
    while (lista) {
        next = lista->nast;
        Tlista *wynik = malloc(sizeof(Tlista));
        assert(wynik != NULL);
        wynik->w = lista->w;
        wynik->nast = prev;
        prev = wynik;
        lista = next;
    }
    return prev;
}

int main(void) {
    int count = 0;
    int suma = 0;
    int curr = 0;
    Tlista *lista = czytaj(&suma, &count);
    Tlista *odwrotna = odwroc(lista);
    int result = 0;
    int i = 0;
    Tlista *c1 = lista;
    Tlista *c2 = odwrotna;
    while (i < (count + 1) / 2) {
        if (curr != suma - c2->w) {
            result++;
        }
        i++;
        c1 = c1->nast;
        c2 = c2->nast;
    }

    printf("Lista: ");
    pisz(lista);

    printf("Liczba samotnych: %d\n", result);

    usun(lista);
    usun(odwrotna);
    return 0;
}
