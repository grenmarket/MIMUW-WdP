/*
 *Dwa niepuste stałe segmenty
 * _______
 *        _____
 */

int klif(int a[], int n) {
    int l = 0;
    int p = n-1;
    int s;
    while (l < p) {
        s = (l+p+1)/2;
        if (a[l] == a[p]) {
            // to może być ostatni, więc trzeba złapać prawostronnie
            l = s;
        } else {
            p = s+1;
        }
    }
    return l;
}