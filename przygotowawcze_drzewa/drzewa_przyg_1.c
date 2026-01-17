#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

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

void najwiekszy_podwieszony_lisc(Node *tree, int *max) {
    int maxL, maxR;
    if (tree == NULL) {
        *max = 0;
    } else if (!tree->left && !tree->right) {
        *max = *max > tree->value ? *max : tree->value;
    } else {
        najwiekszy_podwieszony_lisc(tree->left, &maxL);
        najwiekszy_podwieszony_lisc(tree->right, &maxR);
        *max = maxL > maxR ? maxL : maxR;
        tree->value = *max;
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    Node *tree = create_random_tree(20);
    pretty_print(tree, 0);
    int max;
    najwiekszy_podwieszony_lisc(tree, &max);
    printf("\n\n\n");
    pretty_print(tree, 0);

    free_tree(tree);
    return 0;
}