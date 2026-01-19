#ifndef WDP_QUEUE_H
#define WDP_QUEUE_H
#include "tree.h"

typedef struct QNode {
    Node *data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
} Queue;

void initQueue(Queue *q);
void enqueue(Queue *q, Node *value);
Node* dequeue(Queue *q);
int isEmpty(Queue *q);

#endif