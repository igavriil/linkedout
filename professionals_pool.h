#ifndef PROFESSIONALS_POOL_H
#define PROFESSIONALS_POOL_H

#include "companies_map.h"
#include "professionals_map.h"
#include "circular_array.h"
#include "professional.h"
#include "professional_factory.h"

typedef struct {
    circular_array *professionals;
    professional **professionals_array;
} professionals_pool;

professionals_pool *professionals_pool_new(const companies_map* companies_map, const professionals_map* professionals_map, const char *filename);

#endif