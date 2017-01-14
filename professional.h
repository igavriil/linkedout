#ifndef PROFESSIONAL_H
#define PROFESSIONAL_H

#include "queue.h"

typedef struct {
    unsigned int identifier;
    queue *preferences;
} professional;

#endif