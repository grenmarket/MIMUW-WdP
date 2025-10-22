#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1.0

double r() {
    return (double)rand() / (double)RAND_MAX;
}

double estimate(int n) {
    int count = 0;
    srand((unsigned) time(NULL));
    for (int i = 0; i < n; i++) {
        double x = r();
        double y = r();
        double z = x*x + y*y;
        if (z <= MAX) {
            count++;
        }
    }
    return 4.0 * (double)count / (double)n;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%15.10f", estimate(n));
}
