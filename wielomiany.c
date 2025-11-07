#define ROZMIAR 11
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int t[ROZMIAR];
} Wielomian;

typedef struct {
    int wspolczynnik;
    int stopien;
    int indeks;
} Jednomian;

typedef struct {
    int liczba;
    int indeks;
} Duzo;

void _drukuj_wielomian(Wielomian w) {
    for (int i = 10; i > 0; i--) {
        if (w.t[i] != 0) {
            if (w.t[i] != 1 && w.t[i] != -1) {
                printf("%d", w.t[i]);
            } else if (w.t[i] == -1) {
                printf("-");
            }
            printf("x^");
            printf("%d ", i);
        }
    }
    if (w.t[0] != 0) {
        printf("%d", w.t[0]);
    }
    printf("\n");
}

Wielomian zerowy_wielomian() {
    Wielomian wielomian;
    for (int i = 0; i < ROZMIAR; i++) {
        wielomian.t[i] = 0;
    }
    return wielomian;
}

Jednomian jed(int wspolczynnik, int stopien, int indeks) {
    Jednomian jednomian;
    jednomian.wspolczynnik = wspolczynnik;
    jednomian.stopien = stopien;
    jednomian.indeks = indeks;
    return jednomian;
}

Duzo duz(int liczba, int indeks) {
    Duzo duzo;
    duzo.liczba = liczba;
    duzo.indeks = indeks;
    return duzo;
}

/*
 * Zwraca następny indeks znaku, który nie jest spacją albo końcem napisu, w przeciwnym razie -1.
 */
int nastepny_indeks(char ch[], int i) {
    int d = strlen(ch);
    for (int j = i+1; j < d; j++) {
        if (ch[j] != ' ') {
            return j;
        }
    }
    return -1;
}

bool koniec_jednomianu(char ch[], int indeks) {
    int nastepny = nastepny_indeks(ch, indeks);
    return nastepny == -1 || ch[nastepny] == '-' || ch[nastepny] == '+';
}

bool cyfra(char ch) {
    return ch >= '0' && ch <= '9';
}

Duzo parsuj_duzo(char ch[], int indeks) {
    if (cyfra(ch[indeks])) {
        int liczba = ch[indeks] - '0';
        int nast = nastepny_indeks(ch, indeks);
        while (cyfra(ch[nast])) {
            liczba = liczba * 10 + (ch[nast] - '0');
            nast = nastepny_indeks(ch, nast);
        }
        return duz(liczba, nast);
    }
    return duz(1, indeks);
}

Jednomian parsuj_jednomian_wewn(char ch[], int indeks, int mnoznik) {
    if (ch[indeks] == '1' && koniec_jednomianu(ch, indeks)) {
        return jed(1, 0, nastepny_indeks(ch, indeks));
    }
    Duzo duzo = parsuj_duzo(ch, indeks);
    int curr = duzo.indeks;
    if (curr == -1) {
        return jed(mnoznik * duzo.liczba, 0, -1);
    }
    if (ch[curr] != 'x' && koniec_jednomianu(ch, curr)) {
        return jed(mnoznik * duzo.liczba, 0, nastepny_indeks(ch, curr));
    }
    if (ch[curr] == 'x' && koniec_jednomianu(ch, curr)) {
        return jed(mnoznik * duzo.liczba, 1, nastepny_indeks(ch, curr));
    }
    // przechodzimy nad "x"
    curr = nastepny_indeks(ch, curr);
    // przechodzimy nad "^"
    curr = nastepny_indeks(ch, curr);
    Duzo duzo2 = parsuj_duzo(ch, curr);
    return jed(mnoznik * duzo.liczba, duzo2.liczba, duzo2.indeks);
}

Jednomian parsuj_jednomian(char ch[], int indeks) {
    int curr = indeks;
    int mnoznik = 1;
    if (ch[curr] == '-') {
        mnoznik = -1;
        curr = nastepny_indeks(ch, curr);
    }
    if (ch[curr] == '+') {
        curr = nastepny_indeks(ch, curr);
    }
    return parsuj_jednomian_wewn(ch, curr, mnoznik);
}

Wielomian parsuj_wielomian(char ch[]) {
    int indeks = nastepny_indeks(ch, 0);
    if (ch[indeks] == '0' && nastepny_indeks(ch, indeks) == -1) {
        return zerowy_wielomian();
    }
    Wielomian wielomian = zerowy_wielomian();
    while (indeks != -1) {
        Jednomian jednomian = parsuj_jednomian(ch, indeks);
        wielomian.t[jednomian.stopien] = jednomian.wspolczynnik;
        indeks = jednomian.indeks;
    }
    return wielomian;
}

int main() {
    char ch[] = "+4x^5-6x^4-x^2+2";
    char ch2[] = "*-x^3 + 2x - 6";
    char ch3[] = "+ -  3   x    ^     4    ";
    char ch4[] = "*0";
    _drukuj_wielomian(parsuj_wielomian(ch4));
}
