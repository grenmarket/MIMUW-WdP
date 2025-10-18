#include <stdio.h>

int contains(int N, int a[]) {
    int count = 1;
    int candidate = a[0];
    for (int i = 1; i < N; i++) {
        if (a[i] == candidate) {
            count++;
        } else {
            if (count > 1) {
                count--;
            } else {
                candidate = a[i];
                count = 1;
            }
        }
    }
    count = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] == candidate) {
            count++;
        }
    }
    if (count > N/2) {
        return candidate;
    }
    return -1;
}

int main() {
    // większość
    int A1[] = {1}; //1
    int A2[] = {1, 1}; //1
    int A4[] = {2, 2, 2, 1, 3}; //2
    int A5[] = {5, 5, 5, 5, 1, 2, 3}; //5
    int A6[] = {0, 0, 1, 0, 2, 0, 0}; //0
    int A7[] = {9, 9, 9, 9, 9, 9}; //9
    int A10[] = {2, 3, 3, 2, 2, 3, 3}; //3
    int A12[] = {1, 2, 1, 2, 1, 2, 1}; //1
    int A13[] = {2, 1, 2, 1, 2, 1, 2}; //2
    int A16[] = {1, 1, 1, 2}; //1
    int A18[] = {1, 1, 1, 1, 2, 2, 2, 2, 1}; //1
    int A19[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5}; //5
    int A20[] = {1, 1, 2, 2, 1, 1, 3, 3, 1, 1, 1, 2, 1}; //1
    int A21[] = {10, 20, 20, 30, 30, 10, 10, 10, 10}; //10
    int A23[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; //0
    int A26[] = {9, 1, 9, 1, 9, 1, 9, 1, 9}; //9
    int A27[] = {42, 17, 42, 17, 42, 17, 17}; //17
    int A28[] = {5, 1, 5, 2, 5, 3, 5, 4, 5}; //5

    // brak większości
    int A3[] = {1, 2};
    int A8[]  = {1, 2, 3, 4, 5};
    int A9[]  = {1, 2, 3, 2, 3, 1};
    int A11[] = {1, 2, 3, 2, 2, 3, 3};
    int A14[] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    int A17[] = {1, 2, 1, 2, 1, 2};
    int A22[] = {4, 4, 4, 4, 2, 2, 2, 2};
    int A24[] = {1, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1};
    int A25[] = {3, 3, 4, 4, 3, 4, 3, 4};

#define TEST(arr)  do { \
int res = contains(sizeof(arr)/sizeof(int), arr); \
printf("wynik: %d\n", res); \
} while(0)

    printf("Testy z większością (powinny zwrócić lidera)\n");
    TEST(A1); TEST(A2); TEST(A4); TEST(A5); TEST(A6); TEST(A7); TEST(A10); TEST(A12); TEST(A13); TEST(A16); TEST(A18);
    TEST(A19); TEST(A20); TEST(A21); TEST(A23); TEST(A26); TEST(A27); TEST(A28);

    printf("\nTesty bez większości (powinny zwrócić -1)\n");
    TEST(A3); TEST(A8); TEST(A9); TEST(A11); TEST(A14); TEST(A17); TEST(A22); TEST(A24); TEST(A25);

    return 0;

}
