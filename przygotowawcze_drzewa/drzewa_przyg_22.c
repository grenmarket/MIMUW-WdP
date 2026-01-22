#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

void spacer(Node *d, int *count, int h, int *depth) {
    if (d) {
        int l_depth = 0;
        int p_depth = 0;
        spacer(d->left, count, h+1, &l_depth);
        spacer(d->right, count, h+1, &p_depth);
        *depth = l_depth > p_depth ? l_depth + 1: p_depth + 1;
        if (*depth == h) {
            (*count)++;
        }
    } else {
        *depth = -1;
    }
}

int ile_centralnych(Node *d) {
    int count = 0;
    int depth = 0;
    spacer(d, &count, 0, &depth);
    return count;
}

int main() {
    Node *d = create_BST();
    Node *d1 = malloc(sizeof(Node));
    Node *d2 = malloc(sizeof(Node));
    d->left->left->left->left = d1;
    d->right->right->right->right = d2;
    printf("%d\n", ile_centralnych(d));
    free_tree(d);
    return 0;
}