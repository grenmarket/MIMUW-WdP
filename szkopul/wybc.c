#define MAX 30
#include <stdio.h>

int N;
int A[MAX];

int T[MAX];
int ileT=0;

void wypisz(int i, int suma){
    if (i == N) {
        if (ileT % 2 == 0 && suma % 2 == 1) {
            for(int j=0; j<ileT; j++)
                printf("%d ",T[j]);
            printf("\n");
        }
    } else {
        T[ileT++] = A[i];
        wypisz(i+1, suma+A[i]);
        ileT--;
        wypisz(i+1, suma);
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &A[i]);

    wypisz(0, 0);

    return 0;
}
