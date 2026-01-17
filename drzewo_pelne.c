#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct wezel {
    int w;
    struct wezel *lsyn;
    struct wezel *psyn;
};

typedef struct wezel Twezel;

int max(int a, int b) {
    return a > b ? a : b;
}

void usun(Twezel *d) {
    if (d == NULL)
        return;

    usun(d->lsyn);
    usun(d->psyn);
    free(d);
}

void spacer(Twezel *d, bool *pelne, int *h) {
    if (d == NULL) {
        *pelne = true;
        *h = -1;
    } else {
        int hl, hp;
        bool p_l, p_p;
        spacer(d->lsyn, &p_l, &hl);
        spacer(d->psyn, &p_p, &hp);
        *pelne = p_l && p_p && hl == hp;
        *h = 1 + max(hl, hp);
        if (!*pelne) {
            if (p_l) {
                usun(d->lsyn);
            }
            if (p_p) {
                usun(d->psyn);
            }
        }
    }
}

Twezel* usun_pelne(Twezel *d) {
    bool pelne;
    int h;
    spacer(d, &pelne, &h);
    if (pelne) {
        usun(d);
        return NULL;
    }
    return d;
}