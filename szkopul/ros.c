#include <stdio.h>
#include <stdlib.h>
int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik;

    if (N < 2) {
        wynik = 1;
        printf("%d\n", wynik);
        return 0;
    }

    int prev = A[0];
    int satisfied = 1;
    int i = 1;

    while (satisfied && i < N) {
        int curr = A[i];
        if (curr > prev) {
            i++;
            prev = curr;
        } else {
            satisfied = 0;
        }
    }

    wynik = satisfied ? 1 : 0;

    printf("%d\n", wynik);
    return 0;
}
