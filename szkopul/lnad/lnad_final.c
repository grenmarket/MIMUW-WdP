#include <stdio.h>
#include <stdlib.h>

#include "lnad.h"

void nadlista(int n, int A[n], int B[n], Tlista** lista_ptr) {
    Tlista* l = malloc(sizeof(Tlista));
    Tlista* curr = l;
    int i = 0;
    int j = 0;
    while (i < n && j < n) {
        int curr_val = A[i] < B[j] ? A[i] : B[j];
        Tlista* node = malloc(sizeof(Tlista));
        node->val = curr_val;
        curr->next = node;
        if (A[i] == curr_val) {
            i++;
        }
        if (B[j] == curr_val) {
            j++;
        }
        curr = node;
        curr->next = NULL;
    }
    while (i < n) {
        Tlista* node = malloc(sizeof(Tlista));
        node->val = A[i++];
        curr->next = node;
        curr = node;
        curr->next = NULL;
    }
    while (j < n) {
        Tlista* node = malloc(sizeof(Tlista));
        node->val = B[j++];
        curr->next = node;
        curr = node;
        curr->next = NULL;
    }
    *lista_ptr = l->next;
    free(l);
}