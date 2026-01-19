#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

bool czy_zrownowazone(Node *tree, int *height) {
    if (tree == NULL) {
        *height = -1;
        return true;
    }
    int l_height = 0;
    int r_height = 0;
    bool l_zrownowazone = czy_zrownowazone(tree->left, &l_height);
    bool p_zrownowazone = czy_zrownowazone(tree->right, &r_height);
    int max_h = l_height > r_height ? l_height : r_height;
    *height = max_h + 1;
    return l_zrownowazone && p_zrownowazone && abs(l_height - r_height) <= 1;
}

int main() {
    Node *bst = create_BST();
    int ile = 0;
    printf("%d\n", czy_zrownowazone(bst, &ile));
}