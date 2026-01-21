#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

void spacer(Node *d, int *i, bool lewy, bool korzen, bool *ok, bool pisz) {
    if (d && *ok) {
        spacer(d->left, i, true, false, ok, pisz);
        (*i)++;
        if (!korzen && ((lewy && *i % 2 == 0) || (!lewy && *i % 2 == 1))) {
            *ok = false;
        }
        if (pisz) {
            d->value = *i;
        }
        spacer(d->right, i, false, false, ok, pisz);
    }
}

bool intrygujace(Node *d) {
    bool intr = true;
    int i = 0;
    spacer(d, &i, true, true,  &intr, false);
    if (intr) {
        i = 0; // !!!
        spacer(d, &i, true, true,  &intr, true);
    }
    return intr;
}

int main() {
    Node *root = create_random_tree(20);
    printf("%d\n", intrygujace(root));
    free(root);
}