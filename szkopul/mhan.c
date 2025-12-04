#include <stdio.h>

void przenies(int from, int to, int rozmiar) {
    printf("%d %d %d\n", from, to, rozmiar);
}

void m_hanoi(int a[], int krazek, int from, int to) {
    if (krazek >= 0) {
        int curr = krazek - 1;
        while (curr >= 0 && a[krazek] == a[curr]) {
            curr--;
        }
        m_hanoi(a, curr, from, 6 - to - from);
        for (int i = curr + 1; i <= krazek; i++) {
            przenies(from, to, a[i]);
        }
        m_hanoi(a, curr, 6 - to - from, to);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = n-1; i >= 0; i--) {
        scanf("%d", &a[i]);
    }
    m_hanoi(a, n-1, 1, 3);
}
