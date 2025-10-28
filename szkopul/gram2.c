#include <stdio.h>
#include <stdlib.h>
int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik;
    if (N == 0) {
        wynik = 1;
        printf("%d\n", wynik);
        return 0;
    }
    if (N == 1) {
        wynik = 0;
        printf("%d\n", wynik);
        return 0;
    }
    int i = 0, j = N-1;
    int left = 0, right = 0;
    int matches = 1;
    while (i < j && matches) {
        int a = A[i], b = A[j];
        while (a != 0 && (a == 1 || a == 2 || a == 3)) {
            i++;
            a = A[i];
        }
        if (a == 0) {
            left++;
            i++;
        } else {
            matches = 0;
        }
        while (b != 1 && (b == 0 || b == 2 || b == 3)) {
            j--;
            b = A[j];
        }
        if (b == 1) {
            right++;
            j--;
        } else {
            matches = 0;
        }
    }
    wynik = matches && (j == i-1) && (left == right);

    printf("%d\n", wynik);
    return 0;
}