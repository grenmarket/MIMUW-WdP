#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* create_BRT() {
    Node *root = create_node(0);
    root->left = create_node(0);
    root->right = create_node(0);
    root->left->left = create_node(1);
    root->left->right = create_node(1);
    root->right->left = create_node(1);
    root->right->right = create_node(1);
    root->left->left->left = create_node(0);
    root->left->left->right = create_node(0);
    root->left->right->left = create_node(0);
    root->left->right->right = create_node(0);
    root->right->left->left = create_node(0);
    root->right->left->right = create_node(0);
    root->right->right->left = create_node(0);
    root->right->right->right = create_node(0);
    return root;
}

int is_black_red(Node *root) {
    if (root == NULL) {
        return 1;
    }
    int left = is_black_red(root->left);
    int right = is_black_red(root->right);
    if (left == -1 || right == -1) {
        return -1;
    }
    if (left != right) {
        return -1;
    }
    if (root->left == NULL && root->right == NULL) {
        if (root->value == 0) {
            return 1;
        }
        return -1;
    }
    if (root->value == 1) {
        if (root->left && root->left->value == 1) {
            return -1;
        }
        if (root->right && root->right->value == 1) {
            return -1;
        }
    }
    return left + (root->value == 0 ? 1 : 0);
}

int main() {
    Node *tree = create_BRT();
    printf("%d\n", is_black_red(tree) > -1);
    free_tree(tree);
}