// W urnach numerowanych od 1 do n znajdują się tylko żetony białe i czerwone. Robot
// potrafi wykonywać drogą instrukcję Kol(i) przyjmującą wartości ze zbioru {biały,
// czerwony}.
// Białym segmentem nazwiemy taką parę (i,j), że 1<=i<=j<=n oraz dla każdego k: jeśli
// i<=k<=j, to Kol(k)=biały.
// Napisz fragment programu, który zmiennej bs nada wartość równą liczbie białych
// segmentów.
// Określ, ile razy w najgorszym przypadku wykona się funkcja Kol.

#include <stdbool.h>
#include <stdio.h>

bool bialy(int index, int a[]) {
    return a[index] == 0;
}

int count(int N, int a[]) {
    if (N == 0) {
        return 0;
    }
    int bs = 0;
    int i = 0;
    while (i < N) {
        if (bialy(i, a)) {
            int j = i+1;
            while (j < N && bialy(j, a)) {
                j++;
            }
            int dlugosc = j - i;
            int ile = 0;
            for (int k = 1; k <= dlugosc; k++) {
                ile += k;
            }
            bs += ile;
            i = j+1;
        } else {
            i++;
        }
    }
    return bs;
}

int main() {
    int a1[] = {}; //0
    int a2[] = {0}; //1
    int a3[] = {1}; //0
    int a4[] = {0,0,1,0}; //4
    int a5[] = {1,0,0,0,1}; //6
    int a6[] = {0,1,0,1,0,1,0,0}; //6
    int a7[] = {0,0,0,0,0,0,0,0}; //36
    int a8[] = {1,1,1,1,1,1,1}; //0
    int a9[] = {0,1,0,0,1,0,0,0,1,0,0,0,0,1}; //20

    printf("%d,", count(0, a1));
    printf("%d,", count(1, a2));
    printf("%d,", count(1, a3));
    printf("%d,", count(4, a4));
    printf("%d,", count(5, a5));
    printf("%d,", count(8, a6));
    printf("%d,", count(8, a7));
    printf("%d,", count(7, a8));
    printf("%d,", count(14, a9));
}