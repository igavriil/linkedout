#ifndef COMPANIES_POOL_H
#define COMPANIES_POOL_H

#include "companies_map.h"
#include "professionals_map.h"
#include "company_factory.h"
#include "company.h"

typedef struct {
    company **companies;
} companies_pool;

companies_pool *companies_pool_new(const companies_map* companies_map, const professionals_map* professionals_map, const char *filename);

#endif