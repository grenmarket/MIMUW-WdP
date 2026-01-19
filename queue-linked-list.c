#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) return;

    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }

    Node *temp = q->front;
    int value = temp->data;

    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));

    return 0;
}
