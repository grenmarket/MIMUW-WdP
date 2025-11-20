#include <stdio.h>
int forbiddenFrom = 1;
int forbiddenTo = 2;

void hanoi(int n, int from, int to) {
    if (n == 0) {
        return;
    }
    if (from == forbiddenFrom && to == forbiddenTo) {
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