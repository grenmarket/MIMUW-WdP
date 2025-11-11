#include <stdio.h>

int ind_trojkata(int a[], int n) {
    if (n == 1) {
        return 0;
    }
    int x = a[n-1] - a[0] + 1;
    int i = 0, j = n-1;
    int s;
    while (i < j) {
        s = (i+j)/2;
        if (x > a[s]) {
            i = s+1;
        }
        j = s;
    }
    return i;
}

int main() {
    int a1[] = {3,4,5,6,7};
    int a2[] = {1,1,100};
    int a3[] = {5};
    int a4[] = {5,6};
    int a5[] = {3,4,4,6,6,7};
    printf("%d\n", ind_trojkata(a1, 5));
    printf("%d\n", ind_trojkata(a2, 3));
    printf("%d\n", ind_trojkata(a3, 1));
    printf("%d\n", ind_trojkata(a4, 2));
    printf("%d\n", ind_trojkata(a5, 6));
}