#include <stdio.h>

void print_array(int A[], int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d", A[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]\n");
}

void sort(int N, int a[]) {
    int neg = 0;
    int zero = 0;
    int pos = 0;

    while (pos < N) {
        if (a[pos] > 0) {
            pos++;
        } else if (a[pos] == 0) {
            int temp = a[zero];
            a[zero] = a[pos];
            a[pos] = temp;
            zero++;
            pos++;
        } else {
            int temp = a[neg];
            a[neg] = a[pos];
            a[pos] = temp;
            if (neg != zero) {
                int temp = a[zero];
                a[zero] = a[pos];
                a[pos] = temp;
            }
            neg++;
            zero++;
            pos++;
        }
    }
}

int main(void) {
    int a[] = {0, 9, -8, 7, -6, 5, -4, 0, 3, -2, 0, 0, 1, -1};
    sort(14, a);
    print_array(a, 14);
}
