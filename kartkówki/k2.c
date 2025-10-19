// Napisz funkcję ilezer(n:Integer):Integer (lub fragment programu nadający zmiennej ilezer stosowną wartość), która obliczy
// iloma zerami kończy się liczba n! Możesz korzystać z funkcji div i mod, które wyznaczają odpowiednio wynik i resztę z dzielenia.

#include <stdio.h>

int ilezer(int n) {
    int divisor = 5;
    int result = 0;
    while (divisor <= n) {
        int count = n / divisor;
        result += count;
        divisor *= 5;
    }
    return result;
}

int main() {
    printf("%d\n", ilezer(1));
    printf("%d\n", ilezer(4));
    printf("%d\n", ilezer(5));
    printf("%d\n", ilezer(9));
    printf("%d\n", ilezer(30));
    printf("%d\n", ilezer(100));
}