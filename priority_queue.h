#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

typedef struct priority_queue_entry {
    unsigned int value;
    unsigned int priority;
} priority_queue_entry;


typedef struct priority_queue {
    priority_queue_entry** entries;
    unsigned int count;
    unsigned int capacity;
} priority_queue;

priority_queue *priority_queue_new(unsigned int capacity);

void priority_queue_insert(priority_queue *pq, unsigned int value, unsigned int priority);

unsigned int priority_queue_max(priority_queue* h);

unsigned int priority_queue_delmax(priority_queue* h);

void priority_queue_destroy(priority_queue* h);

#endif
