/**
 * Autor: Sławomir Blicharz
 *
 * Program jest uproszczoną implementacją algorytmu X Donalda Knutha.
 * Zakładamy że dane wejściowe nie przekroczą maksymalnych rozmiarów.
 * Rozwiązania wypisywane są z użyciem maski (filtra).
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Maksymalna liczba podzbiorów.
 */
#define MAX_N 200
/**
 * Maksymalna długość linii (liczność instancji/domeny).
 */
#define MAX_D 300
/**
 * Koduje nieobecność elementu instancji/domeny.
 */
#define EMPTY '_'
/**
 * Koduje brak filtrowania danego elementu.
 */
#define PLUS '+'

/**
 * Pomocniczna struktura do przechowywania rozwiązania.
 */
typedef struct Node {
    bool *solution;
    struct Node *next;
} Node;

/**
 * Pomocnicza struktura do przechowywania rozwiązań.
 */
typedef struct {
    Node *head;
    Node *tail;
} List;

/**
 * Pomocnicza struktura do przechowywania stanu pomiędzy
 * poziomami rekursji.
 */
typedef struct {
    bool incl_row[MAX_N];
    bool incl_col[MAX_D];
    int  col_count[MAX_D];
} CoverState;

/**
 * Inicjalizuje pustą listę rozwiązań.
 */
void list_init(List *list) {
    if (!list) return;
    list->head = NULL;
    list->tail = NULL;
}

/**
 * Tworzy nowy element listy rozwiązań i kopiuje do niego
 * tablicę z rozwiązaniem.
 */
Node* node_create(bool solution[], int subset_count) {
    Node *n = malloc(sizeof(Node));
    n->solution = calloc((size_t)subset_count, sizeof(bool));
    memcpy(n->solution, solution, (size_t)subset_count * sizeof(bool));
    n->next = NULL;
    return n;
}

/**
 * Dodaje nowe rozwiązanie do listy rozwiązań.
 */
void list_append(List *list, bool solution[], int subset_count) {
    if (!list) return;
    Node *n = node_create(solution, subset_count);
    if (list->head == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        list->tail->next = n;
        list->tail = n;
    }
}

/**
 * Drukuje rozwiązania, używając podanego filtra (maski).
 */
void print_solutions(char matrix[MAX_N][MAX_D], List *list, bool *filter,
                     int subset_count, int domain_count) {
    if (!list) return;
    const Node *curr = list->head;
    while (curr) {
        for (int i = 0; i < domain_count; i++) {
            if (filter[i]) {
                for (int j = 0; j < subset_count; j++) {
                    if (curr->solution[j] && matrix[j][i] != EMPTY) {
                        printf("%c", matrix[j][i]);
                    }
                }
            }
        }
        printf("\n");
        curr = curr->next;
    }
}

/**
 * Uwalnia pamięć listy rozwiązań i jej elementów.
 */
void list_destroy(List *list) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        Node *next = curr->next;
        free(curr->solution);
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Funkcja pomocnicza kopiująca stan algorytmu pomiędzy kolejnymi
 * poziomami rekursji.
 */
void copy_state(CoverState *to, const CoverState *from,
                int subset_cnt, int domain_cnt) {
    memcpy(to->incl_row,  from->incl_row,  (size_t)subset_cnt * sizeof(bool));
    memcpy(to->incl_col,  from->incl_col,  (size_t)domain_cnt * sizeof(bool));
    memcpy(to->col_count, from->col_count, (size_t)domain_cnt * sizeof(int));
}

/**
 * Inicjalizuje macierz danych wejściowych i tablicę filtra/maski.
 * Po wczytaniu danych ustawia wartość subset_count i domain_count.
 */
void init(char matrix[][MAX_D], bool filter[],
          int *subset_count, int *domain_count) {
    int d_index = 0;
    int s_index = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        filter[d_index++] = (char)ch == PLUS ? true : false;
    }

    bool finished = false;
    while (!finished && s_index < MAX_N) {
        int col = 0;
        while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
            if (col < d_index) {
                matrix[s_index][col] = (char)ch;
            }
            col++;
        }
        if (ch == EOF && col == 0)
            finished = true;
        else
            s_index++;
    }

    *subset_count = s_index;
    *domain_count = d_index;
}

/**
 * Znajduje indeks kolumny z najmniejszą liczbą podzbiorów zawierających
 * jej element (sugestia Knutha).
 * Jeśli są takie kolumny, że żaden podzbiór nie zawiera ich elementu,
 * ustawia wartość empty na true.
 */
int min_column(CoverState *state, int domain_count, bool *empty) {
    int min_col = -1;
    int best = INT_MAX;
    for (int col = 0; col < domain_count; col++) {
        if (state->incl_col[col]) {
            int count = state->col_count[col];
            if (count < best) {
                best = count;
                min_col = col;
            }
        }
    }
    *empty = (best == 0);
    return min_col;
}

/**
 * Funkcja najpierw kopiuje stan algorytmu z wyższego poziomu rekursji,
 * następnie zaznacza pewne rzędy i kolumny jako usunięte,
 * następnie aktualizuje liczbę elementów w kolumnach.
 */
void apply_row(CoverState *to, CoverState *from, char matrix[MAX_N][MAX_D],
               int chosen_row, int subset_count, int domain_count) {
    copy_state(to, from, subset_count, domain_count);

    for (int col = 0; col < domain_count; col++) {
        // usuwa każdą pozostałą kolumnę która ma element w wybranym wierszu
        if (to->incl_col[col] && matrix[chosen_row][col] != EMPTY) {
            to->incl_col[col] = false;
            for (int row = 0; row < subset_count; row++) {
                // usuwa wszystkie rzędy które mają elementy w tej kolumnie
                if (to->incl_row[row]) {
                    if (matrix[row][col] != EMPTY) {
                        to->incl_row[row] = false;
                        // aktualizuje liczbę elementów
                        for (int x = 0; x < domain_count; x++) {
                            if (to->incl_col[x] && matrix[row][x] != EMPTY) {
                                to->col_count[x]--;
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Główna funkcja rekurencyjna. Pobiera stan algorytmu na odpowiedniej
 * głębokości rekursji, sprawdza czy zostało znalezione rozwiązanie
 * albo czy aktualne odgałęzienie drzewa przeszukiwania nie może doprowadzić
 * do rozwiązania.
 * Następnie wywołuje samą siebie dla każdego potencjalnego rzędu, który
 * może być zawarty w rozwiązaniu.
 */
void cover(char matrix[MAX_N][MAX_D], bool solution[MAX_N], int subset_count,
           int domain_count, int depth, CoverState *state_stack, List *solutions) {
    CoverState *state = &state_stack[depth];
    bool has_column_left = false;
    int i = 0;
    while (!has_column_left && i < domain_count) {
        if (state->incl_col[i]) {
            has_column_left = true;
        }
        i++;
    }
    if (!has_column_left) {
        // znaleźliśmy rozwiązanie
        list_append(solutions, solution, subset_count);
        return;
    }

    bool empty = false;
    int col = min_column(state, domain_count, &empty);
    if (empty) {
        // to odgałęzienie nie może doprowadzić do rozwiązania
        return;
    }
    for (int row = 0; row < subset_count; row++) {
        if (state->incl_row[row] && matrix[row][col] != EMPTY) {
            solution[row] = true;
            CoverState *next = &state_stack[depth + 1];
            apply_row(next, state, matrix, row, subset_count, domain_count);
            cover(matrix, solution, subset_count, domain_count, depth + 1, state_stack, solutions);
            solution[row] = false;
        }
    }
}

/**
 * Inicjalizuje wszystkie struktury danych, oblicza rozwiązania
 * i wypisuje wyniki. Następnie uwalnia pamięć.
 */
int main() {
    // inicjalizuje dane wejściowe
    int height, width;
    char matrix[MAX_N][MAX_D];
    bool filter[MAX_D];
    init(matrix, filter, &height, &width);
    // inicjalizuje listę rozwiązań
    bool solution[MAX_N];
    memset(solution, 0, sizeof(solution));
    List* solutions = malloc(sizeof(List));
    list_init(solutions);
    // inicjalizuje stos stanów algorytmu
    CoverState state_stack[MAX_N];
    CoverState *state = &state_stack[0];
    for (int i = 0; i < height; i++)
        state->incl_row[i] = true;
    for (int j = 0; j < width; j++) {
        state->incl_col[j] = true;
        int count = 0;
        for (int r = 0; r < height; r++) {
            if (matrix[r][j] != EMPTY)
                count++;
        }
        state->col_count[j] = count;
    }

    cover(matrix, solution, height, width, 0, state, solutions);
    print_solutions(matrix, solutions, filter, height, width);
    list_destroy(solutions);
}