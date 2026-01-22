#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

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

int k_bliskie_pary(Node *d, int k) {
    Stack iter1, iter2;
    stack_init(&iter1);
    stack_init(&iter2);

    int result = 0;
    push_left(&iter1, d);
    push_left(&iter2, d);
    Node *left = pop(&iter1);
    Node *right = pop(&iter2);
    right = pop(&iter2);

    int cnt = 0; // ile elementów jest aktualnie w oknie (left, right) spełniających < k
    int ok = 1;
    while (ok && left) {
        while (right && (right->value - left->value) < k) {
            cnt++;
            right = pop(&iter2);
        }

        result += cnt;

        left = pop(&iter1);
        if (!left) {
            ok = 0;
        }

        if (cnt > 0) cnt--;

        while (ok && right == left) {
            right = pop(&iter2);
        }
    }

    stack_free(&iter1);
    stack_free(&iter2);

    return result;
}

int main() {
    Node *d = create_BST();
    printf("%d\n", k_bliskie_pary(d, 4));
}