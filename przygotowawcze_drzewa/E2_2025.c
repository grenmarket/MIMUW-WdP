#include "tree.h"

// ile jest węzłów w których poddrzewach zawiera się dokładnie jeden z d1, d2

void spacer(Node *d, Node *d1, Node *d2, int *jeden, int *ile) {
    if (d) {
        int jeden_l, jeden_p;
        spacer(d->left, d1, d2, &jeden_l, ile);
        spacer(d->right, d1, d2, &jeden_p, ile);
        int sam = d == d1 || d == d2;
        *jeden = (jeden_l + jeden_p + sam) % 2;
        if (*jeden == 1) {
            (*ile)++;
        }
    } else {
        *jeden = 0;
    }
}

int main() {
    int ile = 0;
    int kosz;
    Node *d, *d1, *d2;
    spacer(d, d1, d2, &kosz, &ile);
}