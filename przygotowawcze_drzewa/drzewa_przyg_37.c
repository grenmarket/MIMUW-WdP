#include <stdbool.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
} Node;

static int first_one_index(int A[], int n) {
    for (int i = 0; i < n; i++)
        if (A[i] == 1) return i;
    return -1;
}

static bool is_leaf(const Node *d) {
    return d && d->left == NULL && d->right == NULL;
}

/*
  startA = indeks pierwszej jedynki w A, albo -1 gdy A==0
  lenA   = długość kanonicznego zapisu A (dla A==0 przyjmujemy 1: "0")

  started: czy ścieżka już weszła w część znaczącą (czy pojawiła się '1')
  len    : ile bitów znaczących mamy już na ścieżce
  rel    : -1 (mniejsze), 0 (równe), 1 (większe) względem A, ale tylko przy len==lenA
*/
static bool dfs(const Node *d, int A[], int startA, int lenA,
                bool started, int len, int rel)
{
    if (!d) return false;

    if (is_leaf(d)) {
        if (!started) return false;      // ścieżka = 0
        if (len > lenA) return true;     // dłuższy zapis => większa liczba
        if (len < lenA) return false;
        return (rel == 1);               // ta sama długość: musi być większa
    }

    /* Przejście w lewo (bit 0) i w prawo (bit 1) */
    for (int bit = 0; bit <= 1; bit++) {
        const Node *child = (bit == 0 ? d->left : d->right);
        if (!child) continue;

        bool started2 = started;
        int  len2 = len;
        int  rel2 = rel;

        if (!started) {
            if (bit == 1) {
                started2 = true;
                len2 = 1;

                /* Porównanie pierwszego bitu znaczącego z A */
                int Abit = (startA == -1 ? 0 : 1);  // dla A>0 pierwszy bit to 1
                if (bit > Abit) rel2 = 1;
                else if (bit < Abit) rel2 = -1;
                else rel2 = 0;
            }
            /* jeśli bit==0: nadal nie zaczęliśmy, len=0, rel=0 */
        } else {
            len2 = len + 1;

            if (len2 > lenA) return true;  // natychmiast: dłuższe => większe

            if (rel == 0) {
                int Abit = A[startA + (len2 - 1)];  // kolejny bit A
                if (bit > Abit) rel2 = 1;
                else if (bit < Abit) rel2 = -1;
                else rel2 = 0;
            }
            /* jeśli rel != 0, zostaje bez zmian */
        }

        if (dfs(child, A, startA, lenA, started2, len2, rel2))
            return true;
    }

    return false;
}

bool WiekszyKod(Node *d, int n, int A[])
{
    if (!d || !A || n <= 0) return false;

    int startA = first_one_index(A, n);

    /* kanoniczna długość A */
    int lenA = (startA == -1) ? 1 : (n - startA);

    return dfs(d, A, startA, lenA, false, 0, 0);
}
