#include <stdbool.h>
#include <stdio.h>

int other_color(int a) {
    return a == 0 ? 1 : 0;
}

bool one_different_neighbour(int N, int a[]) {
    if (N < 2 || N % 2 != 0) {
        return false;
    }
    int i = 1;
    int curr_color = a[0];
    int count = 0;
    bool condition_satisfied = true;
    while (condition_satisfied && i < N) {
        int expected_color = count > 0 ? curr_color : other_color(curr_color);
        int actual_color = a[i];
        if (actual_color != expected_color) {
            condition_satisfied = false;
        }
        if (count == 0) {
            count = 1;
            curr_color = other_color(curr_color);
        } else {
            count--;
        }
        i++;
    }
    return condition_satisfied;
}

int main() {
    int a1[] = {1,0,0,1};
    int a2[] = {1,0,0,1,1,0,0,1};
    int a3[] = {1,0,0,1,1,0};
    int a4[] = {1,0,0,1,0,0,1};
    int a5[] = {1,0,0,1,1,0,0,0};
    int a6[] = {1,0,0,1,1,0,0,1,0,1};
    printf("%d\n", one_different_neighbour(4, a1));
    printf("%d\n", one_different_neighbour(8, a2));
    printf("%d\n", one_different_neighbour(6, a3));
    printf("%d\n", one_different_neighbour(7, a4));
    printf("%d\n", one_different_neighbour(8, a5));
    printf("%d\n", one_different_neighbour(10, a6));
}
