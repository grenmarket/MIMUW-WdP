#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

typedef struct StackNode {
    Node *v;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} BSTIter;

static bool stack_push(BSTIter *it, Node *v) {
    StackNode *sn = (StackNode *)malloc(sizeof(*sn));
    if (!sn) return false;
    sn->v = v;
    sn->next = it->top;
    it->top = sn;
    return true;
}

static Node *stack_pop(BSTIter *it) {
    if (!it->top) return NULL;
    StackNode *sn = it->top;
    Node *v = sn->v;
    it->top = sn->next;
    free(sn);
    return v;
}

static bool push_left_spine(BSTIter *it, Node *n) {
    while (n) {
        if (!stack_push(it, n)) return false;
        n = n->left;
    }
    return true;
}

bool bst_iter_init(BSTIter *it, Node *root) {
    if (!it) return false;
    it->top = NULL;
    return push_left_spine(it, root);
}

void bst_iter_destroy(BSTIter *it) {
    if (!it) return;
    while (it->top) (void)stack_pop(it);
}

bool bst_iter_has_next(const BSTIter *it) {
    return it && it->top != NULL;
}

Node *bst_iter_next(BSTIter *it) {
    if (!bst_iter_has_next(it)) return NULL;

    Node *cur = stack_pop(it);
    // after visiting cur, next nodes come from its right subtree
    if (cur->right) {
        if (!push_left_spine(it, cur->right)) return NULL;
    }
    return cur;
}

int main() {
    Node *bst1 = create_BST();
    BSTIter ia;
    bst_iter_init(&ia, bst1);

    while (bst_iter_has_next(&ia)) {
        Node *na = bst_iter_has_next(&ia) ? bst_iter_next(&ia) : NULL;

        if (na) {
            printf("%d ", na->value);
        }
    }

    bst_iter_destroy(&ia);

    // dwa iteratory:
    // Node *l1 = NULL;
    // Node *l2 = NULL;
    //
    // /* get first leaf from tree 1 */
    // while (bst_iter_has_next(&it1)) {
    //     Node *n = bst_iter_next(&it1);
    //     if (n->left == NULL && n->right == NULL) {
    //         l1 = n;
    //         break;
    //     }
    // }
    //
    // /* get first leaf from tree 2 */
    // while (bst_iter_has_next(&it2)) {
    //     Node *n = bst_iter_next(&it2);
    //     if (n->left == NULL && n->right == NULL) {
    //         l2 = n;
    //         break;
    //     }
    // }
    //
    // /* merge-print leaves */
    // while (l1 || l2) {
    //     if (l2 == NULL || (l1 && l1->key <= l2->key)) {
    //         printf("%d\n", l1->key);
    //
    //         /* advance iterator 1 to next leaf */
    //         l1 = NULL;
    //         while (bst_iter_has_next(&it1)) {
    //             Node *n = bst_iter_next(&it1);
    //             if (n->left == NULL && n->right == NULL) {
    //                 l1 = n;
    //                 break;
    //             }
    //         }
    //     } else {
    //         printf("%d\n", l2->key);
    //
    //         /* advance iterator 2 to next leaf */
    //         l2 = NULL;
    //         while (bst_iter_has_next(&it2)) {
    //             Node *n = bst_iter_next(&it2);
    //             if (n->left == NULL && n->right == NULL) {
    //                 l2 = n;
    //                 break;
    //             }
    //         }
    //     }
    // }

}