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
    int last = A[N-1];
    if (last != 1 && last != 2 && last != 3) {
        wynik = 0;
        printf("%d\n", wynik);
        return 0;
    }

    int terminal = 1;
    int matches = 1;
    int i = 0;
    while (i < N && matches) {
        int curr = A[i];
        while (i < N && (curr == 1 || curr == 2 || curr == 3)) {
            i++;
            curr = A[i];
        }
        if (i == N && terminal) {
            wynik = 1;
            printf("%d\n", wynik);
            return 0;
        }
        if (curr == 0) {
            terminal = 0;
            i++;
            curr = A[i];
        } else {
            matches = 0;
        }
        while (i < N && (curr == 2 || curr == 3)) {
            i++;
            curr = A[i];
        }
        if (curr == 1) {
            terminal = 1;
            i++;
        } else {
            matches = 0;
        }
    }
    wynik = matches && terminal;

    printf("%d\n", wynik);
    return 0;
}
