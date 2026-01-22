#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

typedef struct {
    Node  **a;
    int  n, cap;
} Stack;

void st_grow(Stack *st) {
    int new_cap = st->cap ? st->cap * 2 : 16;
    Node **new_a = realloc(st->a, new_cap * sizeof(*new_a));
    st->a = new_a;
    st->cap = new_cap;
}

void st_push(Stack *st, Node *x) {
    if (st->n == st->cap) st_grow(st);
    st->a[st->n++] = x;
}

void push_left(Stack *st, Node *node) {
    for (Node *cur = node; cur; cur = cur->left) {
        st_push(st, cur);
    }
}

Node* pop(Stack *st) {
    if (st->n == 0) return NULL;

    Node *x = st->a[--st->n];
    if (x->right)
        push_left(st, x->right);
    return x;
}

void stack_init(Stack *st) { st->a = NULL; st->n = st->cap = 0; }
void stack_free(Stack *st) { free(st->a); st->a = NULL; st->n = st->cap = 0; }