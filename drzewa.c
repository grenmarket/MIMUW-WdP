#include <stdio.h>
#include <stdlib.h>
#include <_strings.h>

struct wezel {
    int w;
    struct wezel *lsyn;
    struct wezel *psyn;
};

typedef struct wezel Twezel;

void free_drz(Twezel *d) {
    if (!d) return;
    free_drz(d->lsyn);
    free_drz(d->psyn);
    if (d->lsyn == NULL && d->psyn == NULL) {
        free(d);
    }
}

Twezel* drzewo(Twezel *d, int *index, int depth) {
    if (*index > 14 || depth > 3) {
        return NULL;
    }
    if (!d) {
        Twezel *nowy = (Twezel *)malloc(sizeof(Twezel));
        nowy->w = *index;
        (*index)++;
        nowy->lsyn = drzewo(nowy->lsyn, index, depth + 1);
        nowy->psyn = drzewo(nowy->psyn, index, depth + 1);
        return nowy;
    }
}

int liczba_lisci(Twezel *d) {
    if (!d) return 0;
    if (d->lsyn == NULL && d->psyn == NULL) {
        return 1;
    }
    return liczba_lisci(d->lsyn) + liczba_lisci(d->psyn);
}

void ob_pref_L(Twezel *d) {
    if (d) {
        printf("%d ", d->w);
        ob_pref_L(d->lsyn);
        ob_pref_L(d->psyn);
    }
}

int wys_rek(Twezel *d) {
    if (!d) return 0;
    int lewa = wys_rek(d->lsyn);
    int prawa = wys_rek(d->psyn);
    int max = lewa > prawa ? lewa : prawa;
    return max + 1;
}

void dodaj_rodzica(Twezel *d, int n) {
    if (d) {
        d->w += n;
        dodaj_rodzica(d->lsyn, d->w);
        dodaj_rodzica(d->psyn, d->w);
    }
}

void dodaj_dzieci(Twezel *d, int *n) {
    int dodac;
    if (!d) {
        *n = 0;
    } else {
        dodaj_dzieci(d->lsyn, &dodac);
        d->w += dodac;
        dodaj_dzieci(d->psyn, &dodac);
        d->w += dodac;
        *n = d->w;
    }
}


int main() {
    int index = 0;
    Twezel *d = drzewo(NULL, &index, 0);
    int liczba;
    dodaj_dzieci(d, &liczba);
    ob_pref_L(d);
    free_drz(d);
    return 0;
}