#include <stdlib.h>

#include "tree.h"

Node* newNode(int value) {
    Node *p = malloc(sizeof(*p));
    p->value = value;
    p->left = p->right = NULL;
    return p;
}

static Node* build(const int A[], int n, int *i) {
    if (*i >= n) return NULL;

    int x = A[*i];

    Node *root = newNode(x);
    (*i)++;
    root->left  = build(A, n, i);
    root->right = build(A, n, i);
    return root;
}

Node* TworzBST(int A[], int n) {
    int i = 0;
    return build(A, n, &i);
}