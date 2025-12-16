#include <stdio.h>
#include <stdlib.h>

struct lista {
    int w;
    struct lista *nast;
};
typedef struct lista Tlista;

int test[] = {1,3,5,6,8,10,12,13,14,15,16,17,18,20,22};

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

int main() {
    Tlista* lista = init(test, 15);
    usunSrednie(lista);
    print(lista);
}