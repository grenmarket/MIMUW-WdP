#include <stdio.h>

void w(char a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
    }
    printf("\n");
}

void zj(char a[], int n, int zera, int jedynki) {
    if (zera == 0 && jedynki == 0) {
        w(a, 2 * n);
    } else {
        if (zera > 0) {
            a[2 * n - zera - jedynki] = 0;
            zj(a, n, zera - 1, jedynki);
        }
        if (jedynki > 0) {
            a[2 * n - zera - jedynki] = 1;
            zj(a, n, zera, jedynki - 1);
        }
    }
}

void zera_jedynki(int n) {
    char a[2 * n];
    zj(a, n, n, n);
}

int main() {
    zera_jedynki(5);
}