#include <stdio.h>
#include <stdlib.h>

int snap(int A[], int N) {
    int wynik;

    wynik = 0;
    if (N == 0) {
        return 0;
    }
    if (N == 1) {
        if (A[0] > 0) {
            wynik = A[0];
        }
        return wynik;
    }
    int segment_start[N];
    int mins[N];
    int sums[N];

    int last = 0;

    for (int i = 0; i < N; i++) {
        if (A[i] > 0) {
            if (last == -1) {
                segment_start[i] = segment_start[i-1];
                sums[i] = sums[i-1] + A[i];
            } else {
                segment_start[i] = i;
                sums[i] = A[i];
            }
            last = 1;
        } else {
            if (last == 1) {
                segment_start[i] = segment_start[i-1];
                sums[i] = sums[i-1] + A[i];
            } else {
                segment_start[i] = i;
                sums[i] = A[i];
            }
            last = -1;
        }
    }
    int m = N-1;
    while (m >= 0) {
        int j = segment_start[m];
        int c = 0;
        int min = 0;
        while (j <= m) {
            if (c < 1) {
                mins[j] = 0;
                c++;
            } else {
                int curr = sums[j-1];
                if (curr < min) {
                    min = curr;
                }
                mins[j] = min;
            }
            j++;
        }
        m = segment_start[m]-1;
    }

    int i = N-1;
    while (i >= 0) {
        int j = segment_start[i];
        for (int k = j; k <= i; k++) {
            int curr = sums[k] - mins[k];
            if (curr > wynik) {
                wynik = curr;
            }
        }
        i = j - 1;
    }

    return wynik;
}

int bruteforce(int A[], int N) {
    int max = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int go = 1;
            int k = i;
            int sum = 0;
            int last = 0;
            while (go && k <= j) {
                if (A[k] < 0) {
                    if (last >= 0) {
                        sum += A[k];
                        last = -1;
                    } else {
                        go = 0;
                    }
                } else {
                    if (last <= 0) {
                        sum += A[k];
                        last = 1;
                    } else {
                        go = 0;
                    }
                }
                k++;
            }
            if (go && sum > max) {
                max = sum;
            }
        }
    }
    return max;
}

int random_3_to_15(void) {
    return 3 + rand() % (15 - 3 + 1);  // 3 + rand() % 13
}

void fill_random_nonzero(int *arr, int N) {
    for (int i = 0; i < N; i++) {
        int r;
        do {
            r = (rand() % 41) - 20;
        } while (r == 0);
        arr[i] = r;
    }
}

int main() {
    for (int i = 0; i < 500000; i++) {
        int n = random_3_to_15();
        int A[n];
        fill_random_nonzero(A, n);
        int correct = bruteforce(A, n);
        int sn = snap(A, n);
        if (correct != sn) {
            printf("%d/%d\n", correct, sn);
            for (int j = 0; j < n; j++) {
                printf("%d ", A[j]);
            }
            printf("\n");
        }
    }
}