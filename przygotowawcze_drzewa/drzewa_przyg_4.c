#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

void nth(Node *tree, int n, int *counter, Node **result) {
    if (tree == NULL || *result != NULL) {
        return;
    }
    nth(tree->left, n, counter, result);
    if (*result != NULL) {
        return;
    }
    if (*counter == n) {
        *result = tree;
        return;
    } else {
        (*counter)++;
    }
    nth(tree->right, n, counter, result);
}

Node *kty(Node *tree, int k) {
    Node *result = NULL;
    int counter = 1;
    nth(tree, k, &counter, &result);
    return result;
}

int main() {
    srand((unsigned int)time(NULL));
    Node *tree = create_BST();
    printf("%d\n", kty(tree, 15)->value);
}
