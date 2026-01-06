#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CollosalNumber {
    struct CollosalNumber **children;
    size_t child_count;
    size_t child_capacity;
} CollosalNumber;

typedef struct {
    CollosalNumber **numbers;
    size_t size;
    size_t capacity;
} Stack;

void* h_malloc(size_t n) {
    void* p = malloc(n);
    if (!p) {
        exit(1);
    }
    return p;
}

void* h_realloc(void* p, size_t n) {
    p = realloc(p, n);
    if (!p) {
        exit(1);
    }
    return p;
}

void stack_init(Stack *s) {
    s->numbers = NULL;
    s->size = 0;
    s->capacity = 0;
}

void stack_push(Stack *s, CollosalNumber *n) {
    if (s->size == s->capacity) {
        s->capacity = s->capacity ? s->capacity * 2 : 4;
        s->numbers = h_realloc(s->numbers, s->capacity * sizeof(CollosalNumber *));
    }
    s->numbers[s->size++] = n;
}

CollosalNumber *stack_pop(Stack *s) {
    return s->numbers[--s->size];
}

void stack_free(Stack *s) {
    free(s->numbers);
}

CollosalNumber *create_col_num() {
    CollosalNumber *n = h_malloc(sizeof(CollosalNumber));
    n->children = NULL;
    n->child_count = 0;
    n->child_capacity = 0;
    return n;
}

void add_col_nums(CollosalNumber *a, CollosalNumber *b) {
    if (a->child_count == a->child_capacity) {
        a->child_capacity = a->child_capacity ? a->child_capacity * 2 : 4;
        a->children = h_realloc(a->children,
                               a->child_capacity * sizeof(CollosalNumber *));
    }
    a->children[a->child_count++] = b;
}

CollosalNumber *copy_col_num(const CollosalNumber *n) {
    CollosalNumber *r = create_col_num();
    for (size_t i = 0; i < n->child_count; i++)
        add_col_nums(r, copy_col_num(n->children[i]));
    return r;
}

void free_col_num(CollosalNumber *n) {
    for (size_t i = 0; i < n->child_count; i++)
        free_col_num(n->children[i]);
    free(n->children);
    free(n);
}

int compare_col_nums(const CollosalNumber *a, const CollosalNumber *b) {
    size_t i = 0;

    while (i < a->child_count && i < b->child_count) {
        int c = compare_col_nums(a->children[i], b->children[i]);
        if (c != 0)
            return c;
        i++;
    }

    /* All common prefixes equal → longer is larger */
    if (a->child_count > b->child_count)
        return 1;
    if (a->child_count < b->child_count)
        return -1;
    return 0;
}

int equal_col_nums(const CollosalNumber *a, const CollosalNumber *b) {
    if (a->child_count != b->child_count)
        return 0;

    for (size_t i = 0; i < a->child_count; i++)
        if (!equal_col_nums(a->children[i], b->children[i]))
            return 0;

    return 1;
}

int comparator_desc(const void *pa, const void *pb) {
    const CollosalNumber *a = *(const CollosalNumber **)pa;
    const CollosalNumber *b = *(const CollosalNumber **)pb;
    return -compare_col_nums(a, b);
}

CollosalNumber* increment_col_num(const CollosalNumber *exp) {
    CollosalNumber *r = create_col_num();

    /* Copy children */
    for (size_t i = 0; i < exp->child_count; i++)
        add_col_nums(r, copy_col_num(exp->children[i]));

    /* If empty, this is 0 + 1 = {0} */
    if (r->child_count == 0) {
        add_col_nums(r, create_col_num());
        return r;
    }

    /* Check smallest exponent (last child) */
    CollosalNumber *smallest = r->children[r->child_count - 1];

    /* Is it zero? */
    if (smallest->child_count != 0) {
        /* No zero → just add 0 */
        add_col_nums(r, create_col_num());
        qsort(r->children, r->child_count, sizeof(CollosalNumber *), comparator_desc);
        return r;
    }

    /* Carry case: remove 0 */
    free_col_num(smallest);
    r->child_count--;

    /* increment 0 → 1 */
    CollosalNumber* carry = create_col_num();
    add_col_nums(carry, create_col_num());

    /* Insert carry */
    add_col_nums(r, carry);

    /* Normalize only for this carry chain */
    int complete = 0;
    while (!complete) {
        int merged = 0;
        for (size_t i = 0; i + 1 < r->child_count; i++) {
            if (!merged && equal_col_nums(r->children[i], r->children[i + 1])) {
                CollosalNumber *next = increment_col_num(r->children[i]);

                free_col_num(r->children[i]);
                free_col_num(r->children[i + 1]);

                r->children[i] = next;
                r->children[i + 1] = r->children[r->child_count - 1];
                r->child_count--;

                merged = 1;
            }
        }
        if (!merged)
            complete = 1;
    }

    qsort(r->children, r->child_count, sizeof(CollosalNumber *), comparator_desc);
    return r;
}


void normalize_col_num(CollosalNumber *n) {
    int changed = 1;

    while (changed) {
        changed = 0;

        for (size_t i = 0; i < n->child_count && !changed; i++) {
            for (size_t j = i + 1; j < n->child_count; j++) {
                if (equal_col_nums(n->children[i], n->children[j])) {
                    /* create carry before freeing */
                    CollosalNumber *carry = increment_col_num(n->children[i]);

                    /* free both duplicates */
                    free_col_num(n->children[i]);
                    free_col_num(n->children[j]);

                    /* remove higher index first */
                    size_t last = n->child_count - 1;
                    if (j != last)
                        n->children[j] = n->children[last];
                    n->child_count--;

                    /* remove lower index */
                    last = n->child_count - 1;
                    if (i != last)
                        n->children[i] = n->children[last];
                    n->child_count--;

                    /* add carry */
                    add_col_nums(n, carry);

                    changed = 1;
                    break;
                }
            }
        }
    }

    qsort(n->children, n->child_count, sizeof(CollosalNumber *), comparator_desc);
}

/* =========================
 * Arithmetic
 * ========================= */

CollosalNumber *node_add(const CollosalNumber *a, const CollosalNumber *b) {
    CollosalNumber *r = create_col_num();
    for (size_t i = 0; i < a->child_count; i++)
        add_col_nums(r, copy_col_num(a->children[i]));
    for (size_t i = 0; i < b->child_count; i++)
        add_col_nums(r, copy_col_num(b->children[i]));
    normalize_col_num(r);
    return r;
}

CollosalNumber *node_multiply(const CollosalNumber *a, const CollosalNumber *b) {
    CollosalNumber *r = create_col_num();

    for (size_t i = 0; i < a->child_count; i++) {
        for (size_t j = 0; j < b->child_count; j++) {
            CollosalNumber *sum = node_add(a->children[i], b->children[j]);
            add_col_nums(r, sum);
        }
    }

    normalize_col_num(r);
    return r;
}

CollosalNumber *node_exponentiate(const CollosalNumber *exp) {
    CollosalNumber *r = create_col_num();
    add_col_nums(r, copy_col_num(exp));
    normalize_col_num(r);
    return r;
}

/* =========================
 * Parsing & Printing
 * ========================= */

CollosalNumber *parse_number(const char **p) {
    CollosalNumber *n = create_col_num();

    while (**p == '1') {
        (*p)++;
        add_col_nums(n, parse_number(p));
    }

    (*p)++; /* consume '0' */
    normalize_col_num(n);
    return n;
}

void print_number(const CollosalNumber *n) {
    for (size_t i = 0; i < n->child_count; i++) {
        putchar('1');
        print_number(n->children[i]);
    }
    putchar('0');
}

int main(void) {
    Stack stack;
    stack_init(&stack);

    char line[4096];

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 1 && line[0] != '0' && line[0] != '1') {
            char op = line[0];

            if (op == '.') {
                CollosalNumber *n = stack_pop(&stack);
                print_number(n);
                putchar('\n');
                free_col_num(n);
            } else if (op == ':') {
                CollosalNumber *n = stack_pop(&stack);
                stack_push(&stack, copy_col_num(n));
                stack_push(&stack, n);
            } else if (op == '^') {
                CollosalNumber *n = stack_pop(&stack);
                CollosalNumber *r = node_exponentiate(n);
                free_col_num(n);
                stack_push(&stack, r);
            } else if (op == '+') {
                CollosalNumber *b = stack_pop(&stack);
                CollosalNumber *a = stack_pop(&stack);
                CollosalNumber *r = node_add(a, b);
                free_col_num(a);
                free_col_num(b);
                stack_push(&stack, r);
            } else if (op == '*') {
                CollosalNumber *b = stack_pop(&stack);
                CollosalNumber *a = stack_pop(&stack);
                CollosalNumber *r = node_multiply(a, b);
                free_col_num(a);
                free_col_num(b);
                stack_push(&stack, r);
            }
        } else {
            const char *p = line;
            CollosalNumber *n = parse_number(&p);
            stack_push(&stack, n);
        }
    }

    stack_free(&stack);
    return 0;
}
