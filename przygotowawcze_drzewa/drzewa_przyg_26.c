#include <stddef.h>

#include "tree.h"

// l - poprzedni liść
void listuj_liscie(Node *d, Node **l) {
    if (d) {
        listuj_liscie(d->left, l);
        listuj_liscie(d->right, l);
        if (d->left == d->right) {
            (*l)->right = d;
            *l = d;
        }
    }
}

void listuj_liscie_lepiej(Node *d, Node **l) {
    if (d) {
        // odwrotna kolejność
        listuj_liscie_lepiej(d->right, l);
        listuj_liscie_lepiej(d->left, l);
        if (d->left == d->right) {
            d->right = *l;
            *l = d;
        }
    }
}

void napraw(Node *l) {
    Node *p;
    while (l) {
        p = l->right;
        l->right = NULL;
        l = p;
    }
}