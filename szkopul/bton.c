#include <stdio.h>
#include <stdlib.h>

int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik;
    int i = 1;
    int changes_left = 1;

    if (N == 0) {
        wynik = 0;
        printf("%d\n", wynik);
        return 0;
    }

    if (N == 1) {
        wynik = 1;
        printf("%d\n", wynik);
        return 0;
    }

    int prev = A[0];
    while (i < N) {
        int curr = A[i];
        if (curr > prev) {
            if (changes_left == 1) {
                i++;
                prev = curr;
            } else {
                wynik = 0;
                changes_left = -1;
                break;
            }
        } else if (curr < prev) {
            changes_left = 0;
            i++;
            prev = curr;
        } else {
            wynik = 0;
            changes_left = -1;
            break;
        }
    }
    if (changes_left >= 0) {
        wynik = 1;
    }

    printf("%d\n", wynik);
    return 0;
}