#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include "queue.h"

typedef struct {
    unsigned int collisions;
    unsigned int table_size;
    unsigned int seed;
    unsigned int value;
    unsigned int *table;
    list *entries;
} hashmap_intermediate_entry;

typedef struct {
    unsigned int initial_capacity;
    unsigned int capacity;
    queue *indexes;
    hashmap_intermediate_entry *intermediate_table;
} hashmap;

hashmap *hashmap_new(unsigned int capacity);

void hashmap_put(hashmap *hashmap, char *key, const unsigned int value);

unsigned int hashmap_get(const hashmap *hashmap, const char *key);

#endif
