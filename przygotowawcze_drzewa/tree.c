#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

static Node *create_node(int value);
static void insert_random(Node **root, int value);

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

void insert_random(Node **root, int value) {
    if (*root == NULL) {
        *root = create_node(value);
        return;
    }

    Node *current = *root;
    while (1) {
        if (rand() % 2 == 0) {
            if (current->left == NULL) {
                current->left = create_node(value);
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = create_node(value);
                return;
            }
            current = current->right;
        }
    }
}

Node *create_random_tree(int n) {
    Node *root = NULL;

    for (int i = 1; i <= n; i++) {
        insert_random(&root, i);
    }

    return root;
}

Node *create_BST() {
    Node *root = create_node(10);
    Node *curr = root;
    root->left = create_node(5);
    root->right = create_node(15);
    curr = curr->left;
    curr->left = create_node(2);
    curr->right = create_node(8);
    curr = curr->left;
    curr->left = create_node(1);
    curr->right = create_node(3);
    curr = root->left->right;
    curr->left = create_node(7);
    curr->right = create_node(9);
    curr = root->right;
    curr->left = create_node(13);
    curr->right = create_node(18);
    curr = curr->left;
    curr->left = create_node(11);
    curr->right = create_node(14);
    curr = root->right->right;
    curr->left = create_node(17);
    curr->right = create_node(20);
    return root;
}

void pretty_print(Node *root, int depth) {
    if (root == NULL)
        return;

    pretty_print(root->right, depth + 1);

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%d\n", root->value);

    pretty_print(root->left, depth + 1);
}

void free_tree(Node *root) {
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}