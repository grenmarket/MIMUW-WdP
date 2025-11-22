void hanoi(int n, int s, int d) {
    
}

void hanoi_od_i_do_j(int n, int i, int j) {
    hanoi(j, 1, 3);
    if (i > 0) {
        hanoi(i-1, 3, 1);
    }
}