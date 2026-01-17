#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

void najwiekszy_podwieszony_lisc(Node *tree, int *max) {
    int maxL = 0, maxR = 0;
    if (tree == NULL) {
        *max = 0;
    } else if (!tree->left && !tree->right) {
        *max = *max > tree->value ? *max : tree->value;
    } else {
        najwiekszy_podwieszony_lisc(tree->left, &maxL);
        najwiekszy_podwieszony_lisc(tree->right, &maxR);
        *max = maxL > maxR ? maxL : maxR;
        tree->value = *max;
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    Node *tree = create_random_tree(20);
    pretty_print(tree, 0);
    int max = 0;
    najwiekszy_podwieszony_lisc(tree, &max);
    printf("\n\n\n");
    pretty_print(tree, 0);

    free_tree(tree);
    return 0;
}