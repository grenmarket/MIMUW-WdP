// LISTY

#include <stddef.h>

void remove_x(Node **head, int x) {
    Node **pp = head;            // pointer to pointer to current node
    while (*pp) {
        if ((*pp)->val == x) {
            Node *dead = *pp;
            *pp = dead->next;           // bypass
            // free(dead);              // if needed
        } else {
            pp = &(*pp)->next;          // advance pp to "next field"
        }
    }
}

Node* mid_split(Node *head) {
    Node *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (prev) prev->next = NULL;  // cut: head..prev and slow..end
    return slow;                  // start of second half
}

Node* reverse_between(Node *head, int m, int n) {
    Node dummy = {.next = head};
    Node *pre = &dummy;
    for (int i = 1; i < m; i++) pre = pre->next;

    Node *cur = pre->next;
    for (int i = 0; i < n - m; i++) {
        Node *move = cur->next;
        cur->next = move->next;
        move->next = pre->next;
        pre->next = move;
    }
    return dummy.next;
}

Node* cycle_entry(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (!fast || !fast->next) return NULL;
    slow = head;
    while (slow != fast) { slow = slow->next; fast = fast->next; }
    return slow;
}

// BINARY SEARCH

int lower_bound(int *a, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo)/2;
        if (a[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int upper_bound(int *a, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo)/2;
        if (a[mid] > x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// OTHER

struct Info { int h; int ok; };

struct Info dfs(struct Node *x){
    if (!x) return (struct Info){0, 1};
    struct Info L = dfs(x->l), R = dfs(x->r);
    int ok = L.ok && R.ok && (L.h - R.h <= 1) && (R.h - L.h <= 1);
    int h = 1 + (L.h > R.h ? L.h : R.h);
    return (struct Info){h, ok};
}

typedef struct {
    int a[1024];
    int head, tail, cap;
} Q;

int emptyQ(Q *q){ return q->head == q->tail; }
int fullQ(Q *q){ return (q->tail + 1) % q->cap == q->head; }

//DRZEWA

void postorder_two_stacks(Node *root) {
    if (!root) return;

    Stack s1 = {.top = 0};
    Stack s2 = {.top = 0};

    push(&s1, root);

    while (!empty(&s1)) {
        Node *x = pop(&s1);
        push(&s2, x);

        // IMPORTANT: push left then right
        // so that right is processed before left in s1,
        // and then s2 reverses it back to left-right-root.
        if (x->l) push(&s1, x->l);
        if (x->r) push(&s1, x->r);
    }

    while (!empty(&s2)) {
        Node *x = pop(&s2);
        // "visit" x in postorder
        // e.g., printf("%d ", x->val);
    }
}
