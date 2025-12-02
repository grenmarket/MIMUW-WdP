#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define wysokosc 4

bool duzy(int krazek) {
    return krazek > wysokosc/2;
}

bool dozwolony(int z, int na) {
    return abs(z - na) == 1;
}

void przenies(int krazek, int z, int na) {
    char *d = duzy(krazek) ? "(duży)" : "(mały)";
    printf("%d %s z %d na %d\n", krazek, d, z, na);
}

void hanoi(int krazek, int z, int na) {
    if (krazek > 0) {
        if (duzy(krazek) && !dozwolony(z, na)) {
            hanoi(krazek - 1, z, na);
            przenies(krazek, z, 6 - na - z);
            hanoi(krazek - 1, na, z);
            przenies(krazek, 6 - na - z, na);
            hanoi(krazek - 1, z, 6 - na);
        } else {
            hanoi(krazek - 1, z, 6 - z - na);
            przenies(krazek, z, na);
            hanoi(krazek - 1, 6 - z - na, na);
        }
    }
}

int main() {
    hanoi(wysokosc, 1, 3);
}