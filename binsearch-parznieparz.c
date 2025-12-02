#include <stdio.h>

int binary_search_odd_even(int a[], int n, int x, int mode) {
    int low = mode;
    int high = (n - 1) - ((n - 1) % 2 != mode);

    int res = -1;
    int found = 0;

    while (!found && low <= high) {
        int mid = (low + high) / 2;
        if (mid % 2 != mode) {
            mid--;
        }

        if (a[mid] == x) {
            found = 1;
            res = mid;
        }
        else {
            if (a[mid] < x)
                low = mid + 2;
            else
                high = mid - 2;
        }
    }
    return res;
}

int main(void) {
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    printf("%d", binary_search_odd_even(a, 15, 16, 0));
}