#include <stdlib.h>
#include "queue.h"

#define QUEUE_ENQUEUE_INDEX(queue) (queue->tail % queue->capacity)
#define QUEUE_DEQUEUE_INDEX(queue) (queue->head % queue->capacity)

queue *queue_new(unsigned int capacity)
{
    queue *this = malloc(sizeof(queue));
    this->head = -1;
    this->tail = -1;
    this->capacity = capacity;
    this->elements = malloc((capacity)*sizeof(unsigned int));
    return this;
}

void queue_enqueue(queue *queue, unsigned int element)
{
    queue->tail++;
    queue->elements[QUEUE_ENQUEUE_INDEX(queue)] = element;
}

unsigned int queue_dequeue(queue *queue)
{
    queue->head++;
    return queue->elements[QUEUE_DEQUEUE_INDEX(queue)];
}
