#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "professional.h"
#include "professionals_map.h"
#include "professionals_pool.h"
#include "company.h"
#include "companies_map.h"
#include "companies_pool.h"
#include "circular_array.h"
#include "priority_queue.h"

typedef struct {
    companies_map *companies_map;
    professionals_map *professionals_map;
    companies_pool *companies_pool;
    professionals_pool *professionals_pool;
} algorithm;

algorithm* algorithm_new(companies_map *companies_map, professionals_map *professionals_map, companies_pool *companies_pool, professionals_pool *professionals_pool);

void algorithm_run(algorithm* algorithm);

#endif