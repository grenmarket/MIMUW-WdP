#include <stdio.h>

void hanoi(int start[], int end[], int n, int disc) {
    if (disc == 0) {
        return;
    }
    int curr = start[disc-1];
    int goal = end[disc-1];
    if (curr == goal) {
        hanoi(start, end, n, disc-1);
    } else {
        int help = 6 - curr - goal;
        int H[n];
        for (int i = 0; i < n; i++) {
            H[i] = help;
        }
        hanoi(start, H, n, disc-1);
        printf("Przenoszę krążek %d z wieży nr %d na wieżę numer %d\n", disc, curr, goal);
        start = H;
        start[disc-1] = goal;
        hanoi(start, end, n, disc-1);
    }
}

int main() {
    int start[] = {1,1,2,2};
    int end[] = {3,3,3,3};
    hanoi(start, end, 4, 4);
    return 0;
}