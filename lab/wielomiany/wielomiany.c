#define ROZMIAR 11
#define X 'x'

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

void drukuj_jednomian(int wspolczynnik, int stopien, bool pierwszy) {
    if (pierwszy) {
        if (wspolczynnik == -1) {
            printf("-");
        } else if (wspolczynnik != 1) {
            printf("%d", wspolczynnik);
        }
        if (stopien == 0 && (wspolczynnik == 1 || wspolczynnik == -1)) {
            printf("1");
        }
        if (stopien > 0) {
            putchar(X);
        }
        if (stopien > 1) {
            printf("^%d", stopien);
        }
    } else {
        if (wspolczynnik < 0) {
            if (wspolczynnik == -1) {
                printf(" - ");
            } else {
                printf(" - %d", -wspolczynnik);
            }
        } else {
            if (wspolczynnik == 1) {
                printf(" + ");
            } else {
                printf(" + %d", wspolczynnik);
            }
        }
        if (stopien == 0 && (wspolczynnik == 1 || wspolczynnik == -1)) {
            printf("1");
        }
        if (stopien > 0) {
            putchar(X);
        }
        if (stopien > 1) {
            printf("^%d", stopien);
        }
    }
}

void drukuj(Wielomian w) {
    bool pierwszy = true;
    for (int i = 10; i > 0; i--) {
        if (w.t[i] != 0) {
            drukuj_jednomian(w.t[i], i, pierwszy);
            pierwszy = false;
        }
    }
    if (w.t[0] != 0 || pierwszy) {
        drukuj_jednomian(w.t[0], 0, pierwszy);
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

Wielomian dodaj(Wielomian w1, Wielomian w2) {
    Wielomian suma = zerowy_wielomian();
    for (int i = 0; i < ROZMIAR; i++) {
        suma.t[i] = w1.t[i] + w2.t[i];
    }
    return suma;
}

Wielomian pomnoz(Wielomian w1, Wielomian w2) {
    Wielomian iloczyn = zerowy_wielomian();
    for (int i = 0; i < ROZMIAR; i++) {
        for (int j = 0; j < ROZMIAR; j++) {
            if (w1.t[i] != 0 && w2.t[j] != 0) {
                iloczyn.t[i+j] += w1.t[i] * w2.t[j];
            }
        }
    }
    return iloczyn;
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
    int d = (int) strlen(ch);
    for (int j = i + 1; j < d; j++) {
        if (ch[j] != ' ' && ch[j] != '\n') {
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
        while (nast != -1 && cyfra(ch[nast])) {
            liczba = liczba * 10 + (ch[nast] - '0');
            nast = nastepny_indeks(ch, nast);
        }
        return duz(liczba, nast);
    }
    return duz(1, indeks);
}

Jednomian parsuj_jednomian_wewn(char ch[], int indeks, int mnoznik) {
    if (ch[indeks] == '1' && koniec_jednomianu(ch, indeks)) {
        return jed(1 * mnoznik, 0, nastepny_indeks(ch, indeks));
    }
    Duzo duzo = parsuj_duzo(ch, indeks);
    int curr = duzo.indeks;
    if (curr == -1) {
        return jed(mnoznik * duzo.liczba, 0, -1);
    }
    if (ch[curr] != X && koniec_jednomianu(ch, curr)) {
        return jed(mnoznik * duzo.liczba, 0, nastepny_indeks(ch, curr));
    }
    if (ch[curr] == X && koniec_jednomianu(ch, curr)) {
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

Wielomian oblicz(Wielomian w1, char w2[]) {
    if (w2[0] == '+') {
        return dodaj(w1, parsuj_wielomian(w2));
    }
    return pomnoz(w1, parsuj_wielomian(w2));
}

void kalkulator() {
    char napis[1000];
    Wielomian w = zerowy_wielomian();
    bool finished = false;
    fgets(napis, sizeof napis, stdin);
    while (!finished) {
        w = oblicz(w, napis);
        drukuj(w);
        fgets(napis, sizeof napis, stdin);
        if (napis[0] == '.') {
            finished = true;
        }
    }
}

int main() {
    kalkulator();
    return 0;
}
