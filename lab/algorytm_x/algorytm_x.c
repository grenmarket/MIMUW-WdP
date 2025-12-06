/**
 * Autor: Sławomir Blicharz
 *
 * The program is a simplified implementation of Knuth's Algorithm X
 * computing solutions of the exact cover problem.
 * It assumes that the data size will not exceed max values.
 * Additionally, it filters the output using the provided mask.
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Max number of subsets.
 */
#define MAX_N 200
/**
 * Max line length (domain size).
 */
#define MAX_D 300
/**
 * Encodes absence of a subset element.
 */
#define EMPTY '_'
/**
 * Encodes that the element should not be filtered out.
 */
#define PLUS '+'

/**
 * Helper struct to store a solution.
 */
typedef struct Node {
    bool *solution;
    struct Node *next;
} Node;

/**
 * Helper struct to store solutions.
 */
typedef struct {
    Node *head;
    Node *tail;
} List;

/**
 * Helper struct to maintain and reverse state during
 * recursive calls.
 */
typedef struct {
    bool incl_row[MAX_N];
    bool incl_col[MAX_D];
    int  col_count[MAX_D];
} CoverState;

/**
 * Initializes an empty solution list.
 */
void list_init(List *list) {
    if (!list) return;
    list->head = NULL;
    list->tail = NULL;
}

/**
 * Allocates a new solution node and copies into it
 * the solution array.
 */
Node* node_create(bool solution[], int subset_count) {
    Node *n = malloc(sizeof(Node));
    n->solution = calloc((size_t)subset_count, sizeof(bool));
    memcpy(n->solution, solution, (size_t)subset_count * sizeof(bool));
    n->next = NULL;
    return n;
}

/**
 * Adds a new solution to the solution list.
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
 * Prints the solution list, filtering the subset elements
 * using the provided mask.
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
 * Cleans up the solution list and its nodes.
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
 * Helper function to copy the current algorithm state
 * from one recursion layer to the next.
 */
void copy_state(CoverState *to, const CoverState *from,
                int subset_cnt, int domain_cnt) {
    memcpy(to->incl_row,  from->incl_row,  (size_t)subset_cnt * sizeof(bool));
    memcpy(to->incl_col,  from->incl_col,  (size_t)domain_cnt * sizeof(bool));
    memcpy(to->col_count, from->col_count, (size_t)domain_cnt * sizeof(int));
}

/**
 * Initializes the input data matrix and the filter array.
 * After reading the data, it sets the values of
 * subset_count and domain_count.
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
 * Finds the index of the column with the smallest number
 * of subsets containing its element (as suggested by Knuth).
 * If there are columns such that no subset contains its element,
 * it sets the value of empty to true.
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
 * The function first copies the state from one recursive layer above,
 * then removes from consideration certain rows and columns,
 * finally decrements the column count.
 *
 * @param to Algorithm state after this row is selected.
 * @param from Source algorith state (from one recursive layer above).
 * @param matrix The input data matrix.
 * @param chosen_row The index of the row chosen for the partial solution.
 * @param subset_count How many subsets there are.
 * @param domain_count How many domain elements there are.
 */
void apply_row(CoverState *to, CoverState *from, char matrix[MAX_N][MAX_D],
               int chosen_row, int subset_count, int domain_count) {
    copy_state(to, from, subset_count, domain_count);

    for (int col = 0; col < domain_count; col++) {
        // remove each remaining column that has an element in the chosen row
        if (to->incl_col[col] && matrix[chosen_row][col] != EMPTY) {
            to->incl_col[col] = false;
            for (int row = 0; row < subset_count; row++) {
                // remove all rows with an element in this column
                if (to->incl_row[row]) {
                    if (matrix[row][col] != EMPTY) {
                        to->incl_row[row] = false;
                        // update the column count
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
 * The main recursive function. Retrieves the current algorithm state from
 * the stack at the appropriate depth, checks if a solution has been found
 * or if the current algorithm branch is unsuccessful.
 * Then calls itself recursively for each potential solution row.
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
        // solution has been found
        list_append(solutions, solution, subset_count);
        return;
    }

    bool empty = false;
    int col = min_column(state, domain_count, &empty);
    if (empty) {
        // this branch cannot succeed
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
 * Initialize all data structures, computes the solutions
 * and prints the results.
 * Cleans up the memory afterward.
 */
int main() {
    // initialize input data
    int height, width;
    char matrix[MAX_N][MAX_D];
    bool filter[MAX_D];
    init(matrix, filter, &height, &width);
    // initialize solution list
    bool solution[MAX_N];
    memset(solution, 0, sizeof(solution));
    List* solutions = malloc(sizeof(List));
    list_init(solutions);
    // initialize state stack
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