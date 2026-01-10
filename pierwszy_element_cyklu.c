#include <stddef.h>

typedef struct Tlista {
    Tlista* next;
} Tlista;

int odwroc_count(Tlista **l) {
    Tlista* p;
    Tlista* k;
    Tlista* t;
    k = *l;
    p = NULL;
    int count = 0;
    while (k != NULL) {
        t = k->next;
        k->next = p;
        p = k;
        k = t;
        count++;
    }
    *l = p;
    return count;
}

Tlista* pierwszy(Tlista *l) {
    int d = odwroc_count(&l);
    Tlista* t = l;
    for (int i = 0; i < d/2; i++) {
        t = t->next;
    }
    int c = 1;
    Tlista* m = t;
    while (t->next != m) {
        c++;
        t = t->next;
    }
    int p = (d-1-c)/2;
    odwroc_count(&l);
    for (int i = 0; i < p; i++) {
        l = l->next;
    }
    return l;
}