#include <stdio.h>

int bs_1_l(int a[], int n, int x) {
    int i = 1;
    int j = n%2==0 ? n-1 : n-2;
    int s;
    while (i < j) {
        s = (i + j) / 2;
        if (s%2 == 0) {
            s = s-1;
        }
        if (x > a[s]) {
            i = s+2;
        } else {
            j = s;
        }
    }
    return i;
}

int bs_2_l(int a[], int n, int x) {
    int i = 0;
    int j = n%2==0 ? n-2 : n-1;
    int s;
    while (i < j) {
        s = (i + j) / 2;
        if (s%2 == 1) {
            s = s-1;
        }
        if (x > a[s]) {
            i = s+2;
        } else {
            j = s;
        }
    }
    return i;
}

int bs_1_p(int a[], int n, int x) {
    int i = 1;
    int j = n%2==0 ? n-1 : n-2;
    int s;
    while (i < j) {
        s = (i + j + 2) / 2;
        if (s%2 == 0) {
            s = s+1;
        }
        if (x < a[s]) {
            j = s-2;
        } else {
            i = s;
        }
    }
    return i;
}

int bs_2_p(int a[], int n, int x) {
    int i = 0;
    int j = n%2==0 ? n-2 : n-1;
    int s;
    while (i < j) {
        s = (i + j + 2) / 2;
        if (s%2 == 1) {
            s = s+1;
        }
        if (x < a[s]) {
            j = s-2;
        } else {
            i = s;
        }
    }
    return i;
}

int main() {
    int a[] = {2,1,3,1,4,1,4,1,4,2,5,2,6,3,6,4};
    printf("%d\n", bs_1_p(a, 16, 1));
}