// Liczba n jest nieujemną liczbą całkowitą podzielną przez 3. W urnach numerowanych od 1 do n
// znajdują się żetony czerwone albo białe ustawione kolejno według wzoru ccbccbccb...ccb. Masz do
//     dyspozycji procedurę Zamień(i,j) zamieniającą zawartości urn o numerach i oraz j. Napisz
//     fragment programu, który poprzestawia żetony tak, że wszystkie czerwone znajdą się przed
//     białymi. Postaraj się wykonać możliwie mało zamian.

#include <stdbool.h>
#include <stdio.h>

void print_array(int A[], int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d", A[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]");
}

void zamien(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void sort(int N, int a[]) {
    if (N == 0) {
        printf("[]");
        return;
    }
    bool o_jeden = true;
    int i = 2;
    int j = N - 2;
    while (i < j) {
        zamien(a, i, j);
        i += 3;
        j -= o_jeden ? 1 : 2;
        o_jeden = !o_jeden;
    }
    print_array(a, N);
}

int main() {
    int a1[] = {};
    int a2[] = {1,1,0};
    int a3[] = {1,1,0,1,1,0};
    int a4[] = {1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0};
    sort(0, a1);
    sort(3, a2);
    sort(6, a3);
    sort(39, a4);
}