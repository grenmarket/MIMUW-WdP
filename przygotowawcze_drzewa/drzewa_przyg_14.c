#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Twęzełf {
    int w;
    struct Twęzełf *lsyn;
    struct Twęzełf *psyn;
    struct Twęzełf *link;
} Twęzełf;

Twęzełf* create(int w) {
    Twęzełf *node = malloc(sizeof(Twęzełf));
    node->w = w;
    return node;
}

void apply(Twęzełf *d, Twęzełf **max) {
    if (!d) {
        *max = NULL;
        return;
    }
    Twęzełf *lmax = NULL;
    Twęzełf *pmax = NULL;
    apply(d->lsyn, &lmax);
    apply(d->psyn, &pmax);
    Twęzełf *res_max = lmax;
    if (pmax && (!lmax || pmax->w > lmax->w)) {
        res_max = pmax;
    }
    d->link = res_max;
    Twęzełf *global_max = d;
    if (res_max && res_max->w > global_max->w) {
        global_max = res_max;
    }
    *max = global_max;
}

int main() {
    Twęzełf *root = create(1);
    root->lsyn = create(2);
    root->psyn = create(3);
    root->lsyn->lsyn = create(4);
    root->lsyn->psyn = create(5);
    root->psyn->lsyn = create(6);
    root->psyn->psyn = create(7);
    Twęzełf *max = NULL;
    apply(root, &max);
    printf("%d\n", root->link->w);
    printf("%d\n", root->lsyn->link->w);
}