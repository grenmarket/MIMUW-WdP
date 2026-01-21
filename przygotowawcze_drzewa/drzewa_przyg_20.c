#include <stdio.h>
#include <string.h>

#include "tree.h"

static int maxHeight(Node *t) {
    if (!t) return 0;
    int hl = maxHeight(t->left);
    int hr = maxHeight(t->right);
    return (hl > hr ? hl : hr) + 1;
}

static int heightAndCount(Node *t, int cnt[]) {
    if (!t) return 0;
    int hl = heightAndCount(t->left,  cnt);
    int hr = heightAndCount(t->right, cnt);
    int h  = (hl > hr ? hl : hr) + 1;
    cnt[h]++;
    return h;
}

int equalH(Node *tree) {
    int H = maxHeight(tree);
    if (H <= 1) return 0;

    int cnt[H + 1];
    memset(cnt, 0, sizeof cnt);

    heightAndCount(tree, cnt);

    int pairs = 0;
    for (int h = 1; h <= H; h++) {
        pairs += (cnt[h] * (cnt[h] - 1)) / 2;
    }
    return pairs;
}

int main() {
    Node *root = create_BST();
    printf("%d\n", equalH(root));
    free_tree(root);
}