#include <math.h>
#include <stdio.h>

void print(int n, int first) {
    if (n == 1) {
        return;
    }
    if (first) {
        printf("%d", n);
    } else {
        printf(" * %d", n);
    }
}

void rozklad(int n) {
    printf("%d = ", n);
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    const int primes_size = 12;
    int curr = n;
    int first = 1;
    int small_divisor = 1;
    while (curr > 1 && small_divisor) {
        int found = 0;
        int i = 0;
        while (i < primes_size && !found) {
            if (curr % primes[i] == 0) {
                curr /= primes[i];
                found = 1;
                print(primes[i], first);
                first = 0;
            }
            i++;
        }
        if (i >= primes_size) {
            small_divisor = 0;
        }
    }
    int max_possible_divisor = sqrt(curr) + 1;
    int possible_divisor = 41;
    if (possible_divisor > max_possible_divisor) {
        print(curr, first);
    } else {
        while (possible_divisor < max_possible_divisor) {
            if (curr % possible_divisor == 0) {
                curr /= possible_divisor;
                print(possible_divisor, first);
                possible_divisor = 41;
                first = 0;
            } else {
                possible_divisor += 2;
            }
        }
        print(curr, first);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    rozklad(n);
    printf("\n");
}
