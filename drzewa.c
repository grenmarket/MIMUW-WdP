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
    if (*index > 8 || depth > 3) {
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
    return NULL;
}

void wstaw(int x, Twezel **d) {
    if (*d == NULL) {
        *d = malloc(sizeof(Twezel));
        (*d)->w = x;
        (*d)->lsyn = NULL; (*d)->psyn = NULL;
    }
    else if (x<(*d)->w) wstaw(x,&(*d)->lsyn);
    else if (x>(*d)->w) wstaw(x,&(*d)->psyn);
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

void ob_inf_L(Twezel *d) {
    if (d) {
        ob_inf_L(d->lsyn);
        printf("%d ", d->w);
        ob_inf_L(d->psyn);
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

void najw_dziecko(Twezel *d, int *n) {
    if (!d) {
        return;
    }
    int max;
    if (d->lsyn == NULL && d->psyn == NULL) {
        if (n && d->w > *n) {
            *n = d->w;
        }
    } else {
        najw_dziecko(d->lsyn, &max);
        int m1 = max;
        najw_dziecko(d->psyn, &max);
        int m2 = max;
        int m = m1 > m2 ? m1 : m2;
        if (d->w < m) {
            d->w = m;
        }
        *n = d->w;
    }
}

Twezel* lisc_o_najmn_gl(Twezel *d, int *min, int curr) {
    if (d) {
        if (d->lsyn == NULL && d->psyn == NULL) {
            if (curr < *min) {
                *min = curr;
                return d;
            }
            return NULL;
        } else {
            Twezel *lewy = lisc_o_najmn_gl(d->lsyn, min, curr+1);
            Twezel *prawy = lisc_o_najmn_gl(d->psyn, min, curr+1);
            if (!lewy) {
                return prawy;
            }
            if (!prawy) {
                return lewy;
            }
            return prawy;
        }
    } else {
        return NULL;
    }
}

void *k_ty_h(Twezel *T, Twezel *R, int k, int *count) {
    if (T) {
        k_ty_h(T->lsyn, R, k, count);
        if (*count <= k) {
            if (*count == k) {
                R = T;
            }
            (*count)++;
        }
        k_ty_h(T->psyn, R, k, count);
    }
}

Twezel *k_ty(Twezel *T, int k) {
    Twezel *R = malloc(sizeof(Twezel));
    int count = 0;
    k_ty_h(T, R, k, &count);
    return R;
}

void P_NP(Twezel *T, int *niep, int *parz, int *ile) {
    if (!T) {
        *niep = 0;
        *parz = 0;
        return;
    }

    int lewy_niep, lewy_parz;
    int prawy_niep, prawy_parz;

    P_NP(T->lsyn, &lewy_niep, &lewy_parz, ile);
    P_NP(T->psyn, &prawy_niep, &prawy_parz, ile);

    *niep = lewy_niep || prawy_niep || T->w % 2 == 1;
    *parz = T->w % 2 == 0 || prawy_parz || lewy_parz;

    if (*niep && *parz) {
        (*ile)++;
    }
}


int main() {
    int n = 1;
    Twezel *drz = drzewo(NULL, &n, 0);
    ob_inf_L(drz);
    int nie = 0;
    int pa = 0;
    int ile = 0;
    P_NP(drz, &nie, &pa, &ile);
    printf("%d\n", ile);
    free_drz(drz);
    return 0;
}