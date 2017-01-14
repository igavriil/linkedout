#ifndef COMPANIES_MAP_H
#define COMPANIES_MAP_H

#include "hashmap.h"

typedef struct {
    hashmap *forward;
    char **reverse ;
    unsigned int size;
} companies_map;

companies_map *companies_map_new(const char *filename);

#endif