#include <stdio.h>

int znajdz(int a[], int n, int x) {
    int i = 0, j = n-1;
    int s;
    while (i < j) {
        s = (i + j) / 2;
        if (x > a[s]) {
            i = s + 1;
        } else {
            j = s;
        }
    }
    // zawsze lewy pasujący indeks lub indeks na którym znajdowałoby się x
    return i;
}

int main() {
    int a1[] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10};
    int a2[] = {1, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10};
    int a3[] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 10};
    int a4[] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10};
    int a5[] = {1, 2, 3, 5, 5, 6, 7, 8, 9, 10};
    printf("%d\n", znajdz(a1, 11, 5));
    printf("%d\n", znajdz(a2, 12, 1));
    printf("%d\n", znajdz(a3, 12, 10));
    printf("%d\n", znajdz(a4, 11, 10));
    printf("%d\n", znajdz(a5, 10, 0));
}