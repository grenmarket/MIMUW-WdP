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

int main() {
    int T[] = {2,2,3};
    wypisz(T, 3);
}