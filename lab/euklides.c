#include <stdio.h>

int euklides(int a, int b) {
    int m = a;
    int n = b;
    if (b > a) {
        m = b;
        n = a;
    }
    if (n == 0) {
        return m;
    }
    if (m % 2 == 0) {
        if (n % 2 == 0) {
            return 2 * euklides(m / 2, n / 2);
        }
        return euklides(m / 2, n);
    }
    if (n % 2 == 0) {
        return euklides(m, n / 2);
    }
    return euklides(m - n, n);
}

int main() {
    int a = 0, b = 0;
    scanf("%d %d", &a, &b);
    printf("%d\n", euklides(a, b));
}
