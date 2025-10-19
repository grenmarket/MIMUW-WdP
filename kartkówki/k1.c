// W urnach numerowanych od 1 do 2n+1 znajdują się n+1 żetonów czerwonych i n żetonów białych ułożonych we flagę polską - najpierw czerwone, a potem białe.
// Mając do dyspozycji funkcję Z(i,j) zamieniającą   miejscami urnę i-tą z j-tą doprowadź do tego, aby żadne dwa żetony tego samego koloru
// nie sąsiadowały ze sobą. Napisz stosowny algorytm oraz podaj niezmiennik głównej pętli.
//
// Uwaga: robot wykonujący zamiany może się zepsuć, jeśli którykolwiek z argumentów funkcji Z będzie spoza zakresu {1,...,2n+1}
// lub jeśli każemy mu zamienić urny o tym samym numerze. Załóż, że n>=0.

#include <stdio.h>

void print_array(int A[], int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d", A[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]");
}

void z(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void recombine(int N, int a[]) {
    if (N == 0) {
        printf("[]");
        return;
    }
    int left = N;
    int right = 2*N;
    while (left >= 0) {
        z(a, left, right);
        left = left - 2;
        right = right - 2;
    }
    print_array(a, 2*N+1);
}

int main() {
    int a0[] = {};
    int a1[] = {1, 1, 0};
    int a2[] = {1, 1, 1, 1, 0, 0, 0};
    int a3[] = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    recombine(0, a0);
    recombine(1, a1);
    recombine(3, a2);
    recombine(6, a3);
}