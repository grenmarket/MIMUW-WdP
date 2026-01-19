#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

bool istnieje(Node *tree, int *ile_wezlow) {
    if (tree == NULL) {
        *ile_wezlow = 0;
        return false;
    }
    if (!tree->left && !tree->right) {
        *ile_wezlow = 1;
        return false;
    }
    int l_wezlow = 0;
    int p_wezlow = 0;
    bool l_istnieje = istnieje(tree->left, &l_wezlow);
    bool p_istnieje = istnieje(tree->right, &p_wezlow);
    return l_istnieje || p_istnieje || (l_wezlow == p_wezlow && l_wezlow > 0);
}

int main() {
    Node *root = create_random_tree(4);
    int ile = 0;
    printf("%d\n", istnieje(root, &ile));
}