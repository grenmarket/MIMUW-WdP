#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

Node* parse_node(int infix[], int i1, int i2, int postfix[], int j1, int j2) {
    if (i1>i2 || j1>j2) {
        return NULL;
    }
    Node *node = malloc(sizeof(Node));
    node->value = postfix[j2];
    int index = i1;
    while (infix[index] != postfix[j2]) {
        index++;
    }
    node->left = parse_node(infix, i1, index - 1, postfix, j1, j2-1-(i2-index));
    node->right = parse_node(infix, index+1, i2, postfix, j2-(i2-index), j2-1);
    return node;
}

Node* parse(int infix[], int postfix[], int n) {
    return parse_node(infix, 0, n-1, postfix, 0, n-1);
}

int main() {
    int infix[] = {8,4,2,9,5,10,1,6,3,7,11};
    int postfix[] = {8,4,9,10,5,2,6,11,7,3,1};
    Node *root = parse(infix, postfix, 11);
    pretty_print(root, 0);
}