#include <stdio.h>

void choinka(int n) {
    int num_spaces = n-1;
    num_spaces = num_spaces == 0 ? 1 : num_spaces;
    int num_stars = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < num_spaces; j++) {
            printf(" ");
        }
        for (int j = 0; j < num_stars; j++) {
            printf("*");
        }
        for (int j = 0; j < num_spaces; j++) {
            printf(" ");
        }
        num_spaces--;
        num_stars += 2;
        printf("\n");
    }
    num_spaces = (num_stars - 5) / 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < num_spaces; j++) {
            printf(" ");
        }
        for (int j = 0; j < 3; j++) {
            printf("*");
        }
        for (int j = 0; j < num_spaces; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    choinka(n);
}
