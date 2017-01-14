#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include "professional.h"

typedef struct {
    int head;
    int tail;
    unsigned int capacity;
    professional **professionals;
} circular_array;

circular_array *circular_array_new(unsigned int capacity);

void circular_array_put(circular_array *circular_array, professional *professional);

professional *circular_array_get(circular_array *circular_array);

unsigned int circular_array_empty(const circular_array *circular_array);

#endif