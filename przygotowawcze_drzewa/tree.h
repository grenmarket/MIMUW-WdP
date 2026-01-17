#ifndef TREE_H
#define TREE_H

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_random_tree(int n);
void pretty_print(Node *root, int depth);
void free_tree(Node *root);

#endif