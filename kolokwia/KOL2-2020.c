#include <stdio.h>

int ile_cykli(int a[], int n) {
    int cykle = 0;
    int i = 0;
    while (i < n) {
        if (a[i] >= 0) {
            while (a[i] >= 0) {
                a[i] -= n;
                i = a[i] + n;
            }
            cykle++;
        }
        i++;
    }
    i = 0;
    while (i < n) {
        a[i] += n;
        i++;
    }
    return cykle;
}

int main() {
    int a[] = {2,1,3,0,6,7,5,4};
    printf("%d", ile_cykli(a, 8));
}