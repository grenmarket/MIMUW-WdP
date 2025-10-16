#include <stdbool.h>
#include <stdio.h>

bool exists(int N, int a[], int sum) {
    int right = 0;
    int left = -1;
    int curr_sum = a[0];
    while (right < N || curr_sum > sum) {
        if (curr_sum == sum) {
            return 1;
        }
        if (curr_sum < sum) {
            right++;
            curr_sum += a[right];
        } else {
            left++;
            curr_sum -= a[left];
        }
    }
    return 0;
}

int main() {
    int A1[] = {5, 3, 8};
    int A2[] = {1, 2, 3, 4, 5};
    int A3[] = {4, 1, 2, 7};
    int A4[] = {2, 3, 1, 4};
    int A5[] = {2, 2, 2, 2, 2};
    printf("%d", exists(3, A1, 8));
    printf("%d", exists(5, A2, 9));
    printf("%d", exists(4, A3, 7));
    printf("%d", exists(4, A4, 8));
    printf("%d", exists(5, A5, 6));

    int A6[] = {1, 2, 3};
    int A7[] = {2, 4, 6};
    int A8[] = {3, 3, 3, 3};
    int A9[] = {10, 20, 30};
    int A10[] = {7};
    printf("%d", exists(3, A6, 10));
    printf("%d", exists(3, A7, 5));
    printf("%d", exists(4, A8, 5));
    printf("%d", exists(3, A9, 25));
    printf("%d", exists(1, A10, 10));
}