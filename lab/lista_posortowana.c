#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    struct List* next;
    struct List* last;
    int v;
} List;

void print_list(List *head) {
    if (head == NULL) {
        return;
    }
    printf("%d", head->v);
    List *cur = head->next;
    while (cur != NULL) {
        printf(" %d", cur->v);
        cur = cur->next;
    }
    printf("\n");
}

void insert_sorted(int n, List** list) {
    if (*list == NULL) {
        // pierwszy element
        List *ls = (List*)malloc(sizeof(List));
        ls->v = n;
        ls->next = NULL;
        ls->last = ls;
        *list = ls;
    } else {
        List *curr = *list;
        if (curr->v > n) {
            // insert na początek
            List *new_node = (List*)malloc(sizeof(List));
            new_node->v = n;
            new_node->next = *list;
            new_node->last = (*list)->last;
            *list = new_node;
        } else {
            while (curr->next != NULL && curr->next->v < n) {
                curr = curr->next;
            }
            List *new_node = (List*)malloc(sizeof(List));
            new_node->v = n;
            new_node->next = curr->next;
            curr->next = new_node;
            if (new_node->next == NULL) {
                // update last jeśli nowy node jest ostatnim
                (*list)->last = new_node;
            }
        }
    }
}

int get_min(List* list) {
    return list->v;
}

int get_max(List* list) {
    return list->last->v;
}

int main() {
    List* list = NULL;
    int n;
    while (scanf("%d", &n) == 1) {
        insert_sorted(n, &list);
    }
    print_list(list);
    printf("%d\n", get_min(list));
    printf("%d\n", get_max(list));
}