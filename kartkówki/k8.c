#include <stdio.h>

void razy_99(int a[], int n) {
    if (n == 1) {
        return;
    }
    int p = 0;
    int ostatnia = 0;
    int przedostatnia = 0;
    ostatnia = 0 - a[n-1];
    if (ostatnia < 0) {
        ostatnia += 10;
        p--;
    }
    przedostatnia = 0 - a[n-2] + p;
    if (przedostatnia < 0) {
        przedostatnia += 10;
        p = -1;
    } else {
        p = 0;
    }
    int i = n-1;
    while (i >= 0) {
        int w = i-2 >= 0 ? a[i-2] : 0;
        int curr = a[i] - w + p;
        if (curr < 0) {
            curr += 10;
            p = -1;
        } else {
            p = 0;
        }
        a[i] = ostatnia;
        ostatnia = przedostatnia;
        przedostatnia = curr;
        i--;
    }
}

int main() {
    int a1[] = {0,0,4,7,8,2,1,9,5,3,0,1,1};
    razy_99(a1, 13);
    for (int i = 0; i < 13; i++) {
        printf("%d ", a1[i]);
    }
}