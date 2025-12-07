/*
 * tablica wykorzystanych elementów
 * wykorzystujemy tylko pierwszą z grupy tych samych (niewykorzystanych) cyfr
 */

#include <stdio.h>
#include <stdlib.h>

void print(int T[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", T[i]);
    printf("\n");
}

void w(int T[], int A[], int B[], int n, int index) {
    if (index == n) {
        print(A, n);
    } else {
        for (int i = 0; i < n; i++) {
            // nie było i albo początek tablicy, albo poprzednia inną liczbą, albo poprzednia taka sama wykorzystana
            if (B[i] == 0 && (i == 0 || T[i-1] != T[i] || (T[i-1] == T[i] && B[i-1] == 1))) {
                A[index] = T[i];
                B[i] = 1;
                w(T, A, B, n, index+1);
                B[i] = 0;
            }
        }
    }
}

void wypisz(int T[], int n) {
    int* A = (int*)malloc(sizeof(int) * n);
    int* B = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        B[i] = 0;
    }
    w(T, A, B, n, 0);
    free(A);
    free(B);
}

void swap(int T[], int a, int b) {
    int temp = T[a];
    T[a] = T[b];
    T[b] = temp;
}

// ?????
void wypisz_stala_pamiec(int T[], int n, int i) {
    // ostatni element zawsze ok
    if (i == n-1) {
        print(T, n);
    }
    else {
        wypisz_stala_pamiec(T, n, i+1);
        for (int k = i+1; k < n; k++) {
            if (T[k] != T[k-1] && T[i] != T[k]) {
                swap(T, i, k);
                wypisz_stala_pamiec(T, n, i+1);
                swap(T, i, k);
            }
        }
    }
}

int main() {
    int T[] = {2,2,3,3};
    wypisz_stala_pamiec(T, 4, 0);
}