#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int head;
    int tail;
    unsigned int *elements;
    unsigned int capacity;
} queue;

queue *queue_new(unsigned int capacity);

void queue_enqueue(queue *queue, unsigned int element);

unsigned int queue_dequeue(queue *queue);

#endif