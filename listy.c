#include <stdio.h>
#include <stdlib.h>

struct lista {
    int w;
    struct lista *nast;
};
typedef struct lista Tlista;

int test[] = {1,3,5,4,8,7,12};

void print(Tlista* lista) {
    Tlista* curr = lista;
    while (curr != NULL) {
        printf("%d ", curr->w);
        curr = curr->nast;
    }
}

Tlista* init(int t[], int n) {
    Tlista* l = (Tlista*)malloc(sizeof(Tlista));
    Tlista* start = l;
    l->w = t[0];
    for (int i = 1; i < n; i++) {
        Tlista* curr = (Tlista*)malloc(sizeof(Tlista));
        curr->w = t[i];
        l->nast = curr;
        l = curr;
    }
    return start;
}

Tlista* odwroc(Tlista* lista) {
    Tlista* prev = NULL;
    Tlista* next;
    while (lista) {
        next = lista->nast;
        lista->nast = prev;
        prev = lista;
        lista = next;
    }
    return prev;
}

void usunSrednie(Tlista* lista) {
    if (!lista || !lista->nast || !lista->nast->nast) {
        return;
    }
    Tlista* prev = lista;
    Tlista* curr = lista->nast;
    int prev_value = prev->w;
    while (curr->nast) {
        Tlista* next = curr->nast;
        if (2*curr->w == prev_value + next->w) {
            prev_value = curr->w;
            prev->nast = next;
            free(curr);
            curr = next;
        } else {
            prev = curr;
            prev_value = prev->w;
            curr = next;
        }
    }
}

/**
* Gra polega na nast˛epuj ˛acej zabawie. Uczestnicy ustawiaj ˛a si˛e na okr˛egu i ka˙zdy przy-
gotowuje kartk˛e z napisan ˛a liczb ˛a całkowit ˛a. Nast˛epnie losuje si˛e osob˛e A, od której
zaczynamy gr˛e. Ka˙zdy wygrywa tyle, ile napisał, ale pod warunkiem, ˙ze spo´sród osób,
które znajduj ˛a si˛e mi˛edzy nim, a osob ˛a A, (zgodnie z ruchem wskazówek zegara) nikt
nie napisał liczby mniejszej. W li´scie l znajduj ˛a si˛e kolejno zgłoszone do zabawy liczby.
Jako pierwsza wyst˛epuje liczba napisana przez A, a list˛e zamyka liczba napisana przez
osob˛e stoj ˛ac ˛a po prawej r˛ece A. Nale˙zy utworzy´c list˛e wygranych usuwaj ˛ac z listy l
liczby przegrane.
 */
Tlista* zabawa(Tlista* lista) {
    Tlista* prev = NULL;
    Tlista* next;
    while (lista) {
        next = lista->nast;
        lista->nast = prev;
        prev = lista;
        lista = next;
    }
    print(prev);
    printf("\n");
    int min = prev->w;
    Tlista* saved = prev;
    Tlista* curr = prev->nast;
    while (curr) {
        if (curr->w <= min) {
            min = curr->w;
            prev = curr;
            curr = curr->nast;
        } else {
            printf("remove %d\n", curr->w);
            prev->nast = curr->nast;
            free(curr);
            curr = prev->nast;
        }
    }
    Tlista* prev2 = NULL;
    Tlista* next2;
    Tlista* curr2 = saved;
    print(curr2);
    printf("\n");
    while (curr2) {
        next2 = curr2->nast;
        curr2->nast = prev2;
        prev2 = curr2;
        curr2 = next2;
    }
    return prev2;
}

int main() {
    Tlista* lista = init(test, 7);
    Tlista* zab = zabawa(lista);
    print(zab);
}