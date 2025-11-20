#include <stdio.h>

void hanoi(int n, int from, int to) {
    if (n == 0) {
        return;
    }
    hanoi(n-1, from, 6 - from - to);
    printf("Przenoszę krążek %d z wieży nr %d na wieżę numer %d\n", n, from, to);
    hanoi(n-1, 6 - from - to, to);
}
