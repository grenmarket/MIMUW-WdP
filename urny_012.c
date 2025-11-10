#include <stdio.h>

void s(int g[], int d[], int i) {
    int temp = g[i];
    g[i] = g[d[i]];
    g[d[i]] = temp;
}

void z(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void replace_2(int g[], int d[], int n) {
    int i = 0, j = n-1, k = 0, m = n-1;

    for (int i = 0; i < n; i++) {
        printf("%d ", g[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", d[i]);
    }
}

int main() {
    int g[] = {1, 0, 2};
    int d[] = {1, 0, 0};
    replace_2(g, d, 3);
}