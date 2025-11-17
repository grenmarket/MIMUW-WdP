/**
 * Autor: Sławomir Blicharz
 *
 * Program jest implementacją kalkulatora wielomianów.
 * Czyta zdefiniowane reprezentacje wielomianów o współczynnikach całkowitych wraz z operacjami ze standardowego
 * wejścia i wypisuje znormalizowane reprezentacje wyników na standardowe wyjście.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Maksymalny stopień wielomianów + 1 (wyraz wolny).
 */
#define ROZMIAR 11

/**
 * Maksymalna długość wiersza danych.
 */
#define DLUGOSC 1001

/**
 * Znak symbolu zmiennej.
 */
#define X 'x'

/**
 * Znak końca danych.
 */
#define KONIEC '.'

/**
 * Znak operacji 'dodaj'.
 */
#define PLUS '+'

/**
 * Znak operacji 'odejmij'
 */
#define MINUS '-'

/**
 * Koduje koniec danych w wierszu.
 */
#define PUSTE -1

/**
 * Reprezentacja wielomianu.
 */
typedef struct {
    int t[ROZMIAR];
} Wielomian;

/**
 * Reprezentacja jednomianu w wierszu danych.
 */
typedef struct {
    int wspolczynnik;
    int stopien;
    int indeks;
} Jednomian;

/**
 * Reprezentacja <dużo> w wierszu danych.
 * <dużo> ::= "1" <cyfra> { <cyfra> } | <cyfra od 2 do 9> { <cyfra> }
 */
typedef struct {
    int liczba;
    int indeks;
} Duzo;

/**
 * Pomocnicza reprezentacja wiersza danych ze zdefiniowaną długością napisu.
 */
typedef struct {
    int dlugosc;
    char *napis;
} Wiersz;

/**
 * Wypisuje "główną" część jednomianu (np. 1 albo x^5).
 */
void pisz_x(int wspolczynnik, int stopien) {
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

/**
 * Wypisuje pierwszy jednomian wielomianu.
 */
void pisz_pierwszy_jednomian(int wspolczynnik, int stopien) {
    if (wspolczynnik == -1) {
        putchar(MINUS);
    } else if (wspolczynnik != 1) {
        printf("%d", wspolczynnik);
    }
    pisz_x(wspolczynnik, stopien);
}

/**
 * Wypisuje kolejny jednomian w wielomianie.
 */
void pisz_kolejny_wielomian(int wspolczynnik, int stopien) {
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
    pisz_x(wspolczynnik, stopien);
}

/**
 * Wypisuje jednomian.
 */
void pisz_jednomian(int wspolczynnik, int stopien, bool pierwszy) {
    if (pierwszy) {
        pisz_pierwszy_jednomian(wspolczynnik, stopien);
    } else {
        pisz_kolejny_wielomian(wspolczynnik, stopien);
    }
}

/**
 * Wypisuje wielomian.
 */
void pisz(Wielomian w) {
    bool pierwszy = true;
    for (int i = ROZMIAR - 1; i > 0; i--) {
        if (w.t[i] != 0) {
            pisz_jednomian(w.t[i], i, pierwszy);
            pierwszy = false;
        }
    }
    // zero trzeba wypisać jeśli jest wartością jedynego jednomianu
    if (w.t[0] != 0 || pierwszy) {
        pisz_jednomian(w.t[0], 0, pierwszy);
    }
    printf("\n");
}

/**
 * Tworzy i przekazuje pusty (zerowy) wielomian.
 */
Wielomian zerowy_wielomian() {
    Wielomian wielomian;
    for (int i = 0; i < ROZMIAR; i++) {
        wielomian.t[i] = 0;
    }
    return wielomian;
}

/**
 * Dodaje dwa wielomiany i przekazuje wynik.
 */
Wielomian dodaj(Wielomian w1, Wielomian w2) {
    Wielomian suma = zerowy_wielomian();
    for (int i = 0; i < ROZMIAR; i++) {
        suma.t[i] = w1.t[i] + w2.t[i];
    }
    return suma;
}

/**
 * Mnoży dwa wielomiany i przekazuje wynik.
 */
Wielomian pomnoz(Wielomian w1, Wielomian w2) {
    Wielomian iloczyn = zerowy_wielomian();
    for (int i = 0; i < ROZMIAR; i++) {
        for (int j = 0; j < ROZMIAR; j++) {
            if (w1.t[i] != 0 && w2.t[j] != 0) {
                // zakładamy że wynikowy wielomian ma stopień mniejszy lub równy 10
                iloczyn.t[i + j] += w1.t[i] * w2.t[j];
            }
        }
    }
    return iloczyn;
}

/**
 * Tworzy i przekazuje reprezentację jednomianu w wierszu danych o danym współczynniku, stopniu oraz pozycji w napisie.
 */
Jednomian jed(int wspolczynnik, int stopien, int indeks) {
    Jednomian jednomian;
    jednomian.wspolczynnik = wspolczynnik;
    jednomian.stopien = stopien;
    jednomian.indeks = indeks;
    return jednomian;
}

/**
 * Tworzy i przekazuje reprezentację <dużo> w wierszu danych na danej pozycji.
 */
Duzo duz(int liczba, int indeks) {
    Duzo duzo;
    duzo.liczba = liczba;
    duzo.indeks = indeks;
    return duzo;
}

/**
 * Przekazuje następny indeks znaku w danym wierszu danych, który nie jest spacją albo końcem napisu, w przeciwnym razie -1.
 */
int nastepny_indeks(Wiersz wiersz, int i) {
    const char *ch = wiersz.napis;
    for (int j = i + 1; j < wiersz.dlugosc; j++) {
        if (ch[j] != ' ' && ch[j] != '\n' && ch[j] != '\0') {
            return j;
        }
    }
    return PUSTE;
}

/**
 * Przekazuje czy reprezentacja jednomianu w wierszu danych kończy się na danej pozycji.
 */
bool koniec_jednomianu(Wiersz wiersz, int indeks) {
    int nastepny = nastepny_indeks(wiersz, indeks);
    return nastepny == PUSTE || wiersz.napis[nastepny] == MINUS || wiersz.napis[nastepny] == PLUS;
}

/**
 * Przekazuje czy znak jest cyfrą.
 */
bool cyfra(const char ch) {
    return ch >= '0' && ch <= '9';
}

/**
 * Czyta <duzo> od danej pozycji w wierszu danych i przekazuje jego reprezentację.
 */
Duzo parsuj_duzo(Wiersz wiersz, int indeks) {
    const char *ch = wiersz.napis;
    if (cyfra(ch[indeks])) {
        int liczba = ch[indeks] - '0';
        int nast = nastepny_indeks(wiersz, indeks);
        while (nast != PUSTE && cyfra(ch[nast])) {
            liczba = liczba * 10 + (ch[nast] - '0');
            nast = nastepny_indeks(wiersz, nast);
        }
        return duz(liczba, nast);
    }
    return duz(1, indeks);
}

/**
 * Czyta główną część jednomianu (bez znaku) od danej pozycji w wierszu danych i przekazuje jego reprezentację.
 */
Jednomian parsuj_jednomian_wewn(Wiersz wiersz, int indeks, int mnoznik) {
    const char *ch = wiersz.napis;
    if (ch[indeks] == '1' && koniec_jednomianu(wiersz, indeks)) {
        return jed(1 * mnoznik, 0, nastepny_indeks(wiersz, indeks));
    }
    Duzo duzo = parsuj_duzo(wiersz, indeks);
    int curr = duzo.indeks;
    if (curr == PUSTE) {
        return jed(mnoznik * duzo.liczba, 0, PUSTE);
    }
    if (ch[curr] != X && koniec_jednomianu(wiersz, curr)) {
        return jed(mnoznik * duzo.liczba, 0, nastepny_indeks(wiersz, curr));
    }
    if (ch[curr] == X && koniec_jednomianu(wiersz, curr)) {
        return jed(mnoznik * duzo.liczba, 1, nastepny_indeks(wiersz, curr));
    }
    // przechodzimy nad "x"
    curr = nastepny_indeks(wiersz, curr);
    // przechodzimy nad "^"
    curr = nastepny_indeks(wiersz, curr);
    Duzo duzo2 = parsuj_duzo(wiersz, curr);
    return jed(mnoznik * duzo.liczba, duzo2.liczba, duzo2.indeks);
}

/**
 * Czyta jednomian od danej pozycji w wierszu danych i przekazuje jego reprezentację.
 */
Jednomian parsuj_jednomian(Wiersz wiersz, int indeks) {
    int curr = indeks;
    int mnoznik = 1;
    const char *ch = wiersz.napis;
    if (ch[curr] == MINUS) {
        mnoznik = -1;
        curr = nastepny_indeks(wiersz, curr);
    }
    if (ch[curr] == PLUS) {
        curr = nastepny_indeks(wiersz, curr);
    }
    return parsuj_jednomian_wewn(wiersz, curr, mnoznik);
}

/**
 * Czyta wielomian z danego wiersza danych.
 */
Wielomian parsuj_wielomian(Wiersz wiersz) {
    int indeks = nastepny_indeks(wiersz, 0);
    const char *ch = wiersz.napis;
    if (ch[indeks] == '0' && nastepny_indeks(wiersz, indeks) == PUSTE) {
        return zerowy_wielomian();
    }
    Wielomian wielomian = zerowy_wielomian();
    while (indeks != PUSTE) {
        Jednomian jednomian = parsuj_jednomian(wiersz, indeks);
        wielomian.t[jednomian.stopien] = jednomian.wspolczynnik;
        indeks = jednomian.indeks;
    }
    return wielomian;
}

/**
 * Czyta wielomian z danego wiersza danych, wykonuje operację w nim zakodowaną na nim oraz drugim danym wielomianie.
 */
Wielomian oblicz(Wielomian w1, Wiersz wielomian2) {
    const char *w2 = wielomian2.napis;
    if (w2[0] == PLUS) {
        return dodaj(w1, parsuj_wielomian(wielomian2));
    }
    return pomnoz(w1, parsuj_wielomian(wielomian2));
}

/**
 * Główna funkcja programu. Czyta wielomiany z wejścia, wykonuje na nich operacje i wypisuje wyniki aż do sczytania
 * znaku końca danych.
 */
void kalkulator() {
    char ch[DLUGOSC];
    Wielomian wielomian = zerowy_wielomian();
    bool finished = false;
    fgets(ch, sizeof ch, stdin);
    while (!finished) {
        int dlugosc = (int) strlen(ch);
        Wiersz wiersz;
        wiersz.napis = ch;
        wiersz.dlugosc = dlugosc;
        wielomian = oblicz(wielomian, wiersz);
        pisz(wielomian);
        fgets(ch, sizeof ch, stdin);
        if (ch[0] == KONIEC) {
            finished = true;
        }
    }
}

int main() {
    kalkulator();
    return 0;
}
