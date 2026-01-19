#include "queue.h"
#include <stdlib.h>

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, Node *value) {
    QNode *newNode = malloc(sizeof(QNode));
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

Node* dequeue(Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }

    QNode *temp = q->front;
    Node *value = temp->data;

    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}