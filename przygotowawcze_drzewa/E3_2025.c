#include <stdbool.h>
#include <stddef.h>

#include "tree.h"

void spacer(Node *d, int *ile_smacznych, bool *czy_smaczny, int k, bool *koniec) {
    if (!(*koniec)) {
        if (d->left == d->right) { // d - liść
            *ile_smacznych = 1;
            *czy_smaczny = true;
        } else {
            int ilesl = 0, ilesp = 0;
            bool czysl = false, czysp = false;
            if (d->left != NULL) spacer(d->left, &ilesl, &czysl, k, koniec);
            if (d->right != NULL) spacer(d->right, &ilesp, &czysp, k, koniec);

            *czy_smaczny = czysl && czysp;
            *ile_smacznych = ilesl + ilesp + (*czy_smaczny ? 1 : 0);
        }
        if (*ile_smacznych >= k) *koniec = true;
    }
}

bool zyrafa(Node *d, int k) {
    if (d == NULL) return k == 0;
    int iles;
    bool czys, koniec = false;
    spacer(d, &iles, &czys, k, &koniec);
    return iles >= k;
}