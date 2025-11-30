#include <stdbool.h>

int pomiedzy(int a[], int start, int end) {
    if (a[start] == a[end] || end - start == 1) {
        return -1;
    }
    int v1 = a[start];
    int v2 = a[end];

    int i = start;
    int j = end;
    int s;
    bool found = false;
    while (!found && i < j) {
        s = (i + j) / 2;
        if (a[s] == v1) {
            return pomiedzy(a, s, end);
        }
        if (a[s] == v2) {
            return pomiedzy(a, start, s);
        }
        found = true;
    }
    return s;
}

bool trzy(int a[], int n) {
    if (n < 3 || a[n-1] - a[0] < 2) {
        return false;
    }
    int s = pomiedzy(a, 0, n - 1);
    if (s == -1) {
        return false;
    }
    return pomiedzy(a, 0, s) == -1 && pomiedzy(a, s, n - 1) == -1;
}
