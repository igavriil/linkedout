#include <stdlib.h>
#include "circular_array.h"

#define CIRCULAR_ARRAY_PUT_INDEX(circular_array) (circular_array->head)
#define CIRCULAR_ARRAY_GET_INDEX(circular_array) (circular_array->tail)

circular_array *circular_array_new(unsigned int capacity)
{
    circular_array *this = malloc(sizeof(circular_array));

    this->head = 0;
    this->tail = 0;
    this->capacity = capacity + 1;
    this->professionals = malloc((capacity)*sizeof(professional*));
    return this;
}

void circular_array_put(circular_array *circular_array, professional *professional)
{
    circular_array->professionals[CIRCULAR_ARRAY_PUT_INDEX(circular_array)] = professional;
    circular_array->head = (circular_array->head + 1) % circular_array->capacity;
}

professional *circular_array_get(circular_array *circular_array)
{
    professional *professional = circular_array->professionals[CIRCULAR_ARRAY_GET_INDEX(circular_array)];
    circular_array->tail = (circular_array->tail + 1) % circular_array->capacity;
    return professional;
}

unsigned int circular_array_empty(const circular_array *circular_array)
{
    return (circular_array->head == circular_array->tail);
}