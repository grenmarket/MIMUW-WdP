// ile trójek występuje w rozkładzie n!

#include <stdio.h>

int ile_trojek(int N) {
    int result = 0;
    int k = 3;
    while (k <= N) {
        result += N/k;
        k *= 3;
    }
    return result;
}

int main() {
    printf("%d\n", ile_trojek(1));
    printf("%d\n", ile_trojek(3));
    printf("%d\n", ile_trojek(6));
    printf("%d\n", ile_trojek(10));
    printf("%d\n", ile_trojek(20));
    printf("%d\n", ile_trojek(100));
}