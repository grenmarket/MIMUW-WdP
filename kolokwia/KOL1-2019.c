// niezmiennik N(a,c,n)
/*
 * - zakresy
 * - podia w każdym momencie to liczba trójek takich że j są pomiędzy a-c łącznie
 *
 */

int podia(int A[], int n) {
    int a = 0;
    while (a < n && A[a] < A[a+1]) a++;
    int c = 0;
    while (c < n-1 && A[n-1-c] < A[n-2-c]) c++;
    int b = n-a-c;
    int podia = a*b*c;
    while (a >= 0 && c >= 0) {
        if (A[a-1] > A[n-c]) {
            a--;
            podia += a*c;
        }
        if (A[a-1] < A[n-c]) {
            c--;
            podia += a*c;
        }
        if (A[a-1] == A[n-c]) {
            a--;
            c--;
            podia += 2*a*c;
        }
    }
    return podia;
}