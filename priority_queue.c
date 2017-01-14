#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"

#define LEFT_CHILD(i)   ((i<<1)+1)
#define RIGHT_CHILD(i)  ((i<<1)+2)
#define PARENT_ENTRY(i) ((i-1)>>1)

priority_queue *priority_queue_new(unsigned int capacity)
{
    priority_queue *this = malloc(sizeof(priority_queue));

    this->entries = malloc((capacity)*sizeof(priority_queue_entry*));
    this->count = 0;
    this->capacity = capacity;

    return this;
}

static inline void swap_entries(priority_queue *pq, unsigned int first_index, unsigned int second_index)
{
    priority_queue_entry *tmp = pq->entries[first_index];
    pq->entries[first_index] = pq->entries[second_index];
    pq->entries[second_index] = tmp;
}

static inline void sift_down(priority_queue *pq, unsigned int current_index)
{
    unsigned int left_child_index = LEFT_CHILD(current_index);
    unsigned int right_child_index = RIGHT_CHILD(current_index);
    unsigned int largest_index = current_index;

    if (left_child_index < pq->count && pq->entries[largest_index]->priority < pq->entries[left_child_index]->priority)
    {
        largest_index = left_child_index;
    }
    if (right_child_index < pq->count && pq->entries[largest_index]->priority < pq->entries[right_child_index]->priority)
    {
        largest_index = right_child_index;
    }
    if (largest_index != current_index)
    {
        swap_entries(pq, current_index, largest_index);
        sift_down(pq, largest_index);
    }
}

static inline void sift_up(priority_queue *pq, unsigned int current_index)
{
    if (current_index != 0)
    {
        unsigned int parent_child_index = PARENT_ENTRY(current_index);
        while(pq->entries[current_index]->priority > pq->entries[parent_child_index]->priority)
        {
            swap_entries(pq, current_index, parent_child_index);
            if (parent_child_index == 0)
                break;
            current_index = parent_child_index;
            parent_child_index = PARENT_ENTRY(current_index);
        }
    }
}

static inline void heapify(priority_queue *pq)
{
    unsigned int index;
    for (index = (pq->count / 2); index >= 0; index--)
    {
        sift_down(pq, index);
    }
}

void priority_queue_insert(priority_queue *pq, unsigned int value, unsigned int priority)
{
    priority_queue_entry *entry = malloc(sizeof(priority_queue_entry));
    entry->value = value;
    entry->priority = priority;

    pq->entries[pq->count] = entry;
    sift_up(pq, pq->count);

    pq->count++;
}

unsigned int priority_queue_max(priority_queue *pq)
{
    return pq->entries[0]->value;
}

unsigned int priority_queue_delmax(priority_queue *pq)
{
    unsigned int value;
    if(pq->count == 1)
    {
        value = pq->entries[0]->value;
        pq->count--;
    }
    else
    {
        value = pq->entries[0]->value;
        priority_queue_entry *last_entry = pq->entries[pq->count-1];
        pq->count--;
        pq->entries[0] = last_entry;
        sift_down(pq, 0);
    }
    return value;
}
