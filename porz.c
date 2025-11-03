#include <stdio.h>

int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik;
    if (N < 2) {
        wynik = 0;
        printf("%d\n", wynik);
        return 0;
    }
    wynik = 0;
    int non_neg = 0;
    int sum[N];
    for (int i = 0; i < N; i++) {
        sum[i] = 0;
    }
    for (int i = N-2; i >= 0; i--) {
        if (A[i+1] >= 0) {
            non_neg++;
        }
        sum[i] = non_neg;
    }
    for (int i = 0; i < N; i++) {
        if (A[i] < 0) {
            wynik += sum[i];
        }
    }

    printf("%d\n", wynik);
    return 0;
}
