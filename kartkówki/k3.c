// W urnach numerowanych od 1 do n (dla n>0) znajdują się żetony białe, czerwone lub niebieskie.
// Napisz funkcję ZaniebieszczoneTrójki(n:Integer):Boolean, która przyjmie wartość true wtedy i tylko wtedy gdy
// w każdej trójce kolejnych (sąsiednich) urn znajduje się choć jeden niebieski żeton. Masz do dyspozycji
// funkcję Kol(i), która przyjmuje jedną z wartości ze zbioru {biały, czerwony, niebieski}, ale której wywołanie jest
// drogie. Napisz stosowny algorytm oraz podaj niezmiennik pętli. Podaj też liczbę wywołań funkcji Kol.
// Pamiętaj o możliwej awarii robota, gdy wywołanie funkcji Kol będzie spoza zakresu [1..n].

#include <stdbool.h>
#include <stdio.h>

bool zaniebieszczone_trojki(int N, int a[]) {
    if (N < 3) {
        return 1;
    }
    int count = 0;
    bool last = false;
    bool middle = false;
    bool first = false;
    if (a[0] == 0) {
        count++;
        last = true;
    }
    if (a[1] == 0) {
        count++;
        middle = true;
    }
    if (a[2] == 0) {
        count++;
        first = true;
    }
    int curr = 3;
    while (curr < N && count > 0) {
        bool next = a[curr] == 0;
        if (next) {
            count++;
        }
        if (last) {
            count--;
        }
        last = middle;
        middle = first;
        first = next;
        curr++;
     }
    return count > 0;

}

int main() {
    int a1[] = {1, 2};
    int a2[] = {1, 0, 2};
    int a3[] = {1, 1, 2};
    int a4[] = {0,1,2,0,1,1,0,1,1};
    int a5[] = {0,1,2,0,1,1,2,1,1};
    printf("%d\n", zaniebieszczone_trojki(2, a1));
    printf("%d\n", zaniebieszczone_trojki(3, a2));
    printf("%d\n", zaniebieszczone_trojki(3, a3));
    printf("%d\n", zaniebieszczone_trojki(9, a4));
    printf("%d\n", zaniebieszczone_trojki(9, a5));
}
