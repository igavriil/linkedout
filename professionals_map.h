#ifndef PROFESSIONALS_MAP_H
#define PROFESSIONALS_MAP_H

#include "hashmap.h"

typedef struct {
    hashmap *forward;
    char **reverse ;
    unsigned int size;
} professionals_map;

professionals_map *professionals_map_new(const char *filename);

#endif