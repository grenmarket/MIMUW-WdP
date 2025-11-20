#include <stdio.h>
int ff1 = 1;
int ft1 = 2;
int ff2 = 2;
int ft2 = 3;
int ff3 = 3;
int ft3 = 1;

void hanoi(int n, int from, int to) {
    if (n == 0) {
        return;
    }
    if ((from == ff1 && to == ft1) || (from == ff2 && to == ft2) || (from == ff3 && to == ft3)) {
        hanoi(n-1, from, to);
        printf("Przenoszę krążek %d z wieży nr %d na wieżę numer %d\n", n, from, 6 - from - to);
        hanoi(n-1, to, from);
        printf("Przenoszę krążek %d z wieży nr %d na wieżę numer %d\n", n, 6 - from - to, to);
        hanoi(n-1, from, to);
    } else {
        hanoi(n-1, from, 6 - from - to);
        printf("Przenoszę krążek %d z wieży nr %d na wieżę numer %d\n", n, from, to);
        hanoi(n-1, 6 - from - to, to);
    }
}

int main() {
    int n = 3;
    hanoi(n, 1, 3);
}