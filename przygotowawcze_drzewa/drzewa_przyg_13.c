#include <stdbool.h>
#include "tree.h"
#include "queue.h"

bool czy_kopiec(Node *tree) {
    if (!tree || (!tree->left && !tree->right)) {
        return true;
    }
    bool dzieci_mniejsze = (!tree->left || tree->left->value <= tree->value) && (!tree->right || tree->right->value <= tree->value);
    return dzieci_mniejsze && czy_kopiec(tree->right) && czy_kopiec(tree->left);
}

bool czy_kompletne(Node *tree, Queue *queue) {
    if (tree) {
        bool puste_dziecko = false;
        enqueue(queue, tree);
        while (!isEmpty(queue)) {
            Node *q = dequeue(queue);
            if (q->left) {
                if (puste_dziecko) return false;
                enqueue(queue, q->left);
            } else {
                puste_dziecko = true;
            }

            if (q->right) {
                if (puste_dziecko) return false;
                enqueue(queue, q->right);
            } else {
                puste_dziecko = true;
            }
        }
    }
    return true;
}

bool czy_kopiec_zupelny(Node *tree) {
    bool kopiec = czy_kopiec(tree);
    if (!kopiec) {
        return false;
    }
    Queue q;
    initQueue(&q);
    return czy_kompletne(tree, &q);
}