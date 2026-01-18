#ifndef TREE_H
#define TREE_H

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_random_tree(int n);
Node *create_BST();
void pretty_print(Node *root, int depth);
void free_tree(Node *root);

#endif