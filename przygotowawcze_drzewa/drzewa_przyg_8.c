#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

int max(int a, int b, int c) {
    int m1 = a > b ? a : b;
    return m1 > c ? m1 : c;
}

int srednica(Node *root, int *height) {
    if (!root) {
        *height = -1;
        return 0;
    }
    int l_height = 0, r_height = 0;
    int lewa_srednica = srednica(root->left, &l_height);
    int prawa_srednica = srednica(root->right, &r_height);
    int max_height = l_height > r_height ? l_height : r_height;
    *height = max_height + 1;
    return max(lewa_srednica, prawa_srednica, l_height + r_height + 2);
}

int main() {
    Node *bst = create_BST();
    int height = 0;
    printf("%d\n", srednica(bst, &height));
}