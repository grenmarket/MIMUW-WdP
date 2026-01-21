#include <stdbool.h>
#include <stddef.h>

#include "tree.h"

static bool isomorphic(const Node *a, const Node *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;

    if (a->value != b->value) return false;

    bool no_swap = isomorphic(a->left, b->left) && isomorphic(a->right, b->right);
    if (no_swap) return true;

    bool swap = isomorphic(a->left, b->right) && isomorphic(a->right, b->left);
    return swap;
}

bool subtree(Node *t1, Node *t2) {
    if (t2 == NULL) return true;
    if (t1 == NULL) return false;

    if (isomorphic(t1, t2)) return true;

    return subtree(t1->left, t2) || subtree(t1->right, t2);
}