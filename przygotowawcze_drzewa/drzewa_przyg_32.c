#include <limits.h>
#include <stdbool.h>

bool find_rec(int a[], int l, int r, int x)
{
    if (l > r) return false;

    int root = a[l];

    if (x == root) return true;

    /* znajdź pierwszy indeks split w (l+1..r), gdzie a[i] > root
       (czyli początek prawego poddrzewa). Jeśli nie ma, split = r+1. */
    int left = l + 1, right = r + 1;
    while (left < right) {
        int m = left + (right - left) / 2;
        if (a[m] < root) left = m + 1;
        else right = m;
    }
    int split = left;

    if (x < root) return find_rec(a, l + 1, split - 1, x);
    else          return find_rec(a, split, r, x);
}

bool jest(int Pref[], int n, int x)
{
    return find_rec(Pref, 0, n - 1, x);
}
