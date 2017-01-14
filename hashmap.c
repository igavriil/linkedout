#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "hashmap.h"

#define HASHMAP_SIZE_MOD(value, capacity) ((value) & (capacity - 1))

static inline u_int64_t first_level_hash(const char *str)
{
    register size_t hash = 4;

    while (*str++)
        hash = ((hash << 4) + hash) ^ *str;

    return hash;
}

static inline uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed) {
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  uint32_t r1 = 15;
  uint32_t r2 = 13;
  uint32_t m = 5;
  uint32_t n = 0xe6546b64;
  uint32_t h = 0;
  uint32_t k = 0;
  uint8_t *d = (uint8_t *) key;
  const uint32_t *chunks = NULL;
  const uint8_t *tail = NULL;
  int i = 0;
  int l = len / 4;

  h = seed;

  chunks = (const uint32_t *) (d + l * 4);
  tail = (const uint8_t *) (d + l * 4);

  for (i = -l; i != 0; ++i) {
    k = chunks[i];

    k *= c1;
    k = (k << r1) | (k >> (32 - r1));
    k *= c2;

    h ^= k;
    h = (h << r2) | (h >> (32 - r2));
    h = h * m + n;
  }

  k = 0;

  switch (len & 3)
  {
    case 3: k ^= (tail[2] << 16);
    case 2: k ^= (tail[1] << 8);

    case 1:
      k ^= tail[0];
      k *= c1;
      k = (k << r1) | (k >> (32 - r1));
      k *= c2;
      h ^= k;
  }

  h ^= len;

  h ^= (h >> 16);
  h *= 0x85ebca6b;
  h ^= (h >> 13);
  h *= 0xc2b2ae35;
  h ^= (h >> 16);

  return h;
}


static inline u_int32_t second_level_hash(const size_t seed, const char *str)
{
    return murmurhash(str, (uint32_t) strlen(str), seed);
}

static inline unsigned int _upper_power_of_two(unsigned int value)
{
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value++;
    return value;
}

hashmap *hashmap_new(unsigned int capacity)
{
    hashmap *this = malloc(sizeof(hashmap));
    this->indexes = queue_new(capacity);
    this->initial_capacity = capacity;
    this->capacity = _upper_power_of_two(capacity << 4);
    this->intermediate_table = malloc((this->capacity)*sizeof(hashmap_intermediate_entry));
    return this;
}

static inline unsigned int _hashmap_calculate_intermediate_index(const hashmap *hashmap, const char *key)
{
    return HASHMAP_SIZE_MOD(first_level_hash(key), hashmap->capacity);
}

static inline hashmap_intermediate_entry *_hashmap_intermediate_entry_find(const hashmap *hashmap, const char *key)
{
    return &hashmap->intermediate_table[_hashmap_calculate_intermediate_index(hashmap, key)];
}

void hashmap_put(hashmap *hashmap, char *key, const unsigned int value)
{
    const unsigned int index = _hashmap_calculate_intermediate_index(hashmap, key);
    hashmap_intermediate_entry *entry = &hashmap->intermediate_table[index];

    if (!entry->collisions)
    {
        queue_enqueue(hashmap->indexes, index);
        entry->entries = list_new();
    }
    list_tail_push(entry->entries, list_node_new(key, value));
    entry->collisions++;
}

unsigned int hashmap_get(const hashmap *hashmap, const char *key)
{
    const hashmap_intermediate_entry *entry = _hashmap_intermediate_entry_find(hashmap, key);

    if (entry->collisions == 1)
    {
        return entry->value;
    }
    else
    {
        return entry->table[HASHMAP_SIZE_MOD(second_level_hash(entry->seed, key), entry->table_size)];
    }
}

static inline unsigned int _hashmap_calculate_seed(const unsigned int collisions, const unsigned int table_size, list *entries)
{
    unsigned int seed = 0;
    unsigned int entry_index;
    unsigned int table_index;
    unsigned int collisions_flag;

    do
    {
        unsigned int *collisions_table = calloc(table_size, sizeof(unsigned int));
        list_walker *walker = list_walker_new(entries->head, TAIL);
        collisions_flag = 0;

        for(entry_index = collisions; entry_index--;)
        {
            list_node *node = list_walker_next(walker);
            table_index = HASHMAP_SIZE_MOD(second_level_hash(seed, node->key), table_size);
            if (collisions_table[table_index])
            {
                collisions_flag = 1;
                seed++;
                break;
            }
            else
            {
                collisions_table[table_index] = 1;
            }
        }
        list_walker_destroy(walker);
        free(collisions_table);

    } while (collisions_flag);

    return seed;
}

static inline void _hashmap_resolve_collisions(hashmap *hashmap, const unsigned int index)
{
    hashmap_intermediate_entry *entry = &hashmap->intermediate_table[index];
    const unsigned int collisions = entry->collisions;

    if (collisions == 1)
    {
        entry->value = entry->entries->head->value;
    }
    else if (collisions > 1)
    {
        const unsigned int table_size = _upper_power_of_two(collisions << 4);
        unsigned int table_index;
        unsigned int entry_index;

        entry->table = malloc(table_size * sizeof(unsigned int));
        entry->table_size = table_size;

        const unsigned int seed = _hashmap_calculate_seed(collisions, entry->table_size, entry->entries);

        entry->seed = seed;
        list_walker *walker = list_walker_new(entry->entries->head, TAIL);
        for(entry_index = collisions; entry_index--;)
        {
            list_node *node = list_walker_next(walker);
            table_index = HASHMAP_SIZE_MOD(second_level_hash(seed, node->key), table_size);

            entry->table[table_index] = node->value;
        }
    }
}

void hashmap_finalize(hashmap *hashmap)
{
    unsigned int index;
    for (index = hashmap->initial_capacity; index--;)
    {
        _hashmap_resolve_collisions(hashmap, queue_dequeue(hashmap->indexes));
    }
}
