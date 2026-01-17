#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

void lisc_o_najmniejszej_glebokosci(Node *drzewo, int height, int *min, Node **result) {
    if (drzewo == NULL) {
        return;
    } else if (!drzewo->left && !drzewo->right) {
        if (height<*min) {
            *min = height;
            *result = drzewo;
        }
    } else {
        lisc_o_najmniejszej_glebokosci(drzewo->left, height+1, min, result);
        lisc_o_najmniejszej_glebokosci(drzewo->right, height+1, min, result);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    Node *tree = create_random_tree(15);
    pretty_print(tree, 0);
    Node *result = NULL;
    int min = INT32_MAX;
    lisc_o_najmniejszej_glebokosci(tree, 0, &min, &result);
    printf("%d\n", result->value);

    free_tree(tree);
    return 0;
}