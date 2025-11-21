#include <stdio.h>
#include <stdlib.h>

int plwz(int A[], int n) {
    if (n == 1) {
        return 1;
    }
    int i = 0;
    int j = n-1;
    int s;
    while (i < j) {
        s = (i+j)/2;
        if (A[s] < A[s+1]) {
            i = s+1;
        } else {
            j = s;
        }
    }
    int start = i;
    j = n-1;
    while (i < j) {
        s = (i+j+1)/2;
        if (A[s-1] > A[s]) {
            j = s-1;
        } else {
            i = s;
        }
    }
    return i - start + 1;
}

int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik;
    wynik = plwz(A, N);
    printf("%d\n", wynik);
    return 0;
}