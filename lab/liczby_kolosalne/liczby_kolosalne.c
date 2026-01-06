#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A tree structure to represent collosal numbers.
 */
typedef struct CollosalNumber {
    struct CollosalNumber **children;
    size_t child_count;
    size_t child_capacity;
} CollosalNumber;

/**
 * Calculator stack.
 */
typedef struct {
    CollosalNumber **numbers;
    size_t size;
    size_t capacity;
} Stack;

/**
 * Operations on stack:
 */

void stack_init(Stack *s) {
    s->numbers = NULL;
    s->size = 0;
    s->capacity = 0;
}

void stack_push(Stack *s, CollosalNumber *n) {
    if (s->size == s->capacity) {
        s->capacity = s->capacity ? s->capacity * 2 : 4;
        s->numbers = realloc(s->numbers, s->capacity * sizeof(CollosalNumber *));
    }
    s->numbers[s->size++] = n;
}

CollosalNumber *stack_pop(Stack *s) {
    return s->numbers[--s->size];
}

/**
 * Basic operations on collosal numbers:
 */

CollosalNumber *create_col_num() {
    CollosalNumber *n = malloc(sizeof(CollosalNumber));
    n->children = NULL;
    n->child_count = 0;
    n->child_capacity = 0;
    return n;
}

void add_col_nums_helper(CollosalNumber *a, CollosalNumber *b) {
    if (a->child_count == a->child_capacity) {
        a->child_capacity = a->child_capacity ? a->child_capacity * 2 : 4;
        a->children = realloc(a->children,
                               a->child_capacity * sizeof(CollosalNumber *));
    }
    a->children[a->child_count++] = b;
}

CollosalNumber *copy_col_num(CollosalNumber *n) {
    CollosalNumber *r = create_col_num();
    for (size_t i = 0; i < n->child_count; i++) {
        add_col_nums_helper(r, copy_col_num(n->children[i]));
    }
    return r;
}

void free_col_num(CollosalNumber *n) {
    for (size_t i = 0; i < n->child_count; i++) {
        free_col_num(n->children[i]);
    }
    free(n->children);
    free(n);
}

/**
 * Frees the memory allocated for the stack and its items.
 */
void stack_free(Stack *s) {
    while (s->size > 0) {
        free_col_num(stack_pop(s));
    }
    free(s->numbers);
}

/**
 *
 * Comparing methods:
 */

int compare_col_nums(CollosalNumber *a, CollosalNumber *b) {
    size_t i = 0;

    while (i < a->child_count && i < b->child_count) {
        int c = compare_col_nums(a->children[i], b->children[i]);
        if (c != 0) {
            // one has a larger term
            return c;
        }
        i++;
    }

    if (a->child_count > b->child_count) {
        // number a has more terms
        return 1;
    }
    if (a->child_count < b->child_count) {
        return -1;
    }
    return 0;
}

int equal_col_nums(CollosalNumber *a, CollosalNumber *b) {
    if (a->child_count != b->child_count) {
        return 0;
    }

    for (size_t i = 0; i < a->child_count; i++) {
        if (!equal_col_nums(a->children[i], b->children[i])) {
            return 0;
        }
    }

    return 1;
}

/**
 * Comparator for convenient sorting.
 */
int comparator_desc(const void *pa, const void *pb) {
    CollosalNumber *a = *(CollosalNumber **)pa;
    CollosalNumber *b = *(CollosalNumber **)pb;
    return -compare_col_nums(a, b);
}

CollosalNumber* increment_col_num(CollosalNumber *exp);

void add_term_col_num(CollosalNumber *n, CollosalNumber *term) {
    for (size_t i = 0; i < n->child_count; i++) {
        if (equal_col_nums(n->children[i], term)) {
            // merge equal terms
            CollosalNumber *next_exp = increment_col_num(term);
            free_col_num(n->children[i]);
            free_col_num(term);

            if (i != n->child_count - 1) {
                n->children[i] = n->children[n->child_count - 1];
            }
            n->child_count--;

            add_term_col_num(n, next_exp);
            return;
        }
    }

    // just append
    add_col_nums_helper(n, term);
    qsort(n->children, n->child_count,
        sizeof(CollosalNumber *), comparator_desc);
}

/**
 * Returns an incremented collosal number.
 * @param exp collosal number
 * @return exp + 1
 */
CollosalNumber* increment_col_num(CollosalNumber *exp) {
    CollosalNumber *r = copy_col_num(exp);
    CollosalNumber *zero_exp = create_col_num();
    add_term_col_num(r, zero_exp);

    return r;
}

/**
 * Normalizes the tree that encodes this collosal number.
 */
void normalize_col_num(CollosalNumber *n) {
    if (!n || !n->children) {
        return;
    }
    qsort(n->children, n->child_count,
        sizeof(CollosalNumber *), comparator_desc);

    for (size_t i = 0; i + 1 < n->child_count; i++) {
        if (equal_col_nums(n->children[i], n->children[i + 1])) {
            CollosalNumber *carry = increment_col_num(n->children[i]);

            free_col_num(n->children[i]);
            free_col_num(n->children[i + 1]);

            // shift array left
            size_t tail = n->child_count - (i + 2);
            if (tail > 0) {
                memmove(&n->children[i], &n->children[i + 2],
                    tail * sizeof(CollosalNumber *));
            }
            n->child_count -= 2;

            add_term_col_num(n, carry);

            normalize_col_num(n);
            return;
        }
    }
}

/**
 * Arithmetic operations on collosal numbers (normalized):
 */

/**
 * Adds and returns two collosal numbers.
 */
CollosalNumber *add_col_num(const CollosalNumber *a, const CollosalNumber *b) {
    CollosalNumber *r = create_col_num();
    for (size_t i = 0; i < a->child_count; i++) {
        add_col_nums_helper(r, copy_col_num(a->children[i]));
    }
    for (size_t i = 0; i < b->child_count; i++) {
        add_col_nums_helper(r, copy_col_num(b->children[i]));
    }
    normalize_col_num(r);
    return r;
}

/**
 * Multiplies and returns two collosal numbers.
 */
CollosalNumber *multiply_col_num(CollosalNumber *a, CollosalNumber *b) {
    CollosalNumber *r = create_col_num();

    for (size_t i = 0; i < a->child_count; i++) {
        for (size_t j = 0; j < b->child_count; j++) {
            CollosalNumber *sum = add_col_num(a->children[i], b->children[j]);
            add_col_nums_helper(r, sum);
        }
    }

    normalize_col_num(r);
    return r;
}

/**
 * Returns two to the power of the argument.
 * @param exp collosal number
 * @return collosal number of value 2^exp
 */
CollosalNumber *exp_col_num(CollosalNumber *exp) {
    CollosalNumber *r = create_col_num();
    add_col_nums_helper(r, copy_col_num(exp));
    normalize_col_num(r);
    return r;
}

/**
 * Parsing and printing methods:
 */

CollosalNumber *parse_col_num(char **p) {
    CollosalNumber *n = create_col_num();

    while (**p == '1') {
        (*p)++;
        add_col_nums_helper(n, parse_col_num(p));
    }

    (*p)++; // last '0'
    normalize_col_num(n);
    return n;
}

void print_col_num(CollosalNumber *n) {
    for (size_t i = 0; i < n->child_count; i++) {
        putchar('1');
        print_col_num(n->children[i]);
    }
    putchar('0');
}

/**
 * Main function of the program. Runs in a loop until there are
 * collosal numbers to be processed. Frees the stack memory
 * at the end.
 */
int main() {
    Stack stack;
    stack_init(&stack);

    char line[4096];

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 1 && line[0] != '0' && line[0] != '1') {
            char op = line[0];

            if (op == '.') {
                CollosalNumber *n = stack_pop(&stack);
                print_col_num(n);
                putchar('\n');
                free_col_num(n);
            } else if (op == ':') {
                CollosalNumber *n = stack_pop(&stack);
                stack_push(&stack, copy_col_num(n));
                stack_push(&stack, n);
            } else if (op == '^') {
                CollosalNumber *n = stack_pop(&stack);
                CollosalNumber *r = exp_col_num(n);
                free_col_num(n);
                stack_push(&stack, r);
            } else if (op == '+') {
                CollosalNumber *b = stack_pop(&stack);
                CollosalNumber *a = stack_pop(&stack);
                CollosalNumber *r = add_col_num(a, b);
                free_col_num(a);
                free_col_num(b);
                stack_push(&stack, r);
            } else if (op == '*') {
                CollosalNumber *b = stack_pop(&stack);
                CollosalNumber *a = stack_pop(&stack);
                CollosalNumber *r = multiply_col_num(a, b);
                free_col_num(a);
                free_col_num(b);
                stack_push(&stack, r);
            }
        } else {
            char *p = line;
            CollosalNumber *n = parse_col_num(&p);
            stack_push(&stack, n);
        }
    }

    stack_free(&stack);
    return 0;
}
