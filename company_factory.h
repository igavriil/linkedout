#ifndef COMPANY_FACTORY_H
#define COMPANY_FACTORY_H

#include "company.h"
#include "companies_map.h"
#include "professionals_map.h"
#include "queue.h"

company *company_new(const companies_map* companies_map, const professionals_map* professionals_map, char* line);

#endif