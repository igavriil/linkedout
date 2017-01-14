#ifndef COMPANY_H
#define COMPANY_H

#include "priority_queue.h"

typedef struct {
    priority_queue *applications;
    unsigned int *positions;
    unsigned int identifier;
    unsigned int capacity;
    unsigned int applications_count;
} company;

#endif