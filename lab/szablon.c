#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DigitNode {
    int value;
    struct DigitNode* next;
} Node;

Node* create_node(int value, Node *next) {
    Node *node = malloc(sizeof(Node));
    assert(node != NULL);
    node->value = value;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->value);
        cur = cur->next;
    }
    printf("NULL\n");
}

void destroy_list(Node *head) {
    Node* p = head;
    while (p) {
        Node* tmp = p;
        p = p->next;
        free(tmp);
    }
}

// Sprawdzanie czy na liście istnieje węzeł o danej wartości
bool contains(Node *head, int value) {
    if (head == NULL) {
        return false;
    }
    Node *curr = head;
    bool found = false;
    while (!found && curr != NULL) {
        if (curr->value == value) {
            found = true;
        } else {
            curr = curr->next;
        }
    }

    return found;
}

// Szukanie najmniejszego elementu; funkcja przekazuje INT_MAX dla listy pustej
int min_value(Node* head) {
    if (head == NULL) {
        return INT_MAX;
    }
    int min = INT_MAX;
    while (head != NULL) {
        if (head->value < min) {
            min = head->value;
        }
        head = head->next;
    }
    return min;
}

// Usunięcie najmniejszych elementów
void remove_min_elements(Node** head_ptr) {
    if (*head_ptr == NULL) {
        return;
    }
    int min = min_value(*head_ptr);
    Node* atrapa = (Node*)malloc(sizeof(Node));
    atrapa->next = *head_ptr;
    Node* prev = atrapa;
    Node* curr = *head_ptr;
    while (curr != NULL) {
        if (curr->value == min) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    *head_ptr = atrapa->next;
    free(atrapa);
}

int main() {
    Node *l =
            create_node(10,
            create_node(10,
            create_node(20,
            create_node(10,
            create_node(30,
            create_node(10,
            NULL))))));
    bool jest_20 = contains(l, 20);
    bool jest_25 = contains(l, 25);
    int min = min_value(l);
    printf("%d %d %d\n", jest_20, jest_25, min);
    print_list(l);
    remove_min_elements(&l);
    print_list(l);
    destroy_list(l);
}

