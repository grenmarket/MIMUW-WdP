#include <stdio.h>

void hanoi_h(int n, int from, int to) {
    if (n == 0) {
        return;
    }
    int help = 6 - from - to;
    hanoi_h(n-1, from, help);
    printf("%d %d %d\n", n, from, to);
    hanoi_h(n-1, help, from);
    hanoi_h(n-1, from, to);
}

void hanoi(int n) {
    hanoi_h(n-1, 1, 3);
    printf("%d %d %d\n", n, 1, 2);
    hanoi_h(n-1, 3, 1);
    printf("%d %d %d\n", n, 2, 3);
    hanoi_h(n-1, 1, 2);
    printf("%d %d %d\n", n, 3, 1);
    hanoi_h(n-1, 2, 3);
    hanoi_h(n-1, 3, 1);
}

int main() {
    hanoi(3);
}