#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>
#include "tree.h"

int num_of_nodes(Node *tree) {
    if (tree == NULL) {
        return 0;
    }
    if (!tree->left && !tree->right) {
        return 1;
    }
    return num_of_nodes(tree->left) + num_of_nodes(tree->right) + 1;
}

void unwrap(Node *tree, int array[], int *i) {
    if (tree == NULL) {
        return;
    }
    if (!tree->left && !tree->right) {
        array[*i] = tree->value;
        (*i)++;
    } else {
        unwrap(tree->left, array, i);
        array[*i] = tree->value;
        (*i)++;
        unwrap(tree->right, array, i);
    }
}

Node* generate(int a[], int *index, int left) {
    if (left == 0) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->value = a[*index];
    (*index)++;
    node->left = generate(a, index, left-1);
    node->right = generate(a, index, left-1);
    return node;
}

Node* generate_tree(int array[], int size) {
    int height = log(size) / log(2) + 1;
    int index = 0;
    return generate(array, &index, height);
}

int main() {
    srand((unsigned int)time(NULL));

    Node *tree = create_random_tree(15);
    pretty_print(tree, 0);
    int num = num_of_nodes(tree);
    int array[num];
    int index = 0;
    unwrap(tree, array, &index);
    printf("\n\n\n");
    for (int i = 0; i < num; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n\n");
    Node *tree2 = generate_tree(array, num);
    pretty_print(tree2, 0);
}