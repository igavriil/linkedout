#ifndef PROFESSIONAL_FACTORY_H
#define PROFESSIONAL_FACTORY_H

#include "professional.h"
#include "professionals_map.h"
#include "companies_map.h"

professional *professional_new(const companies_map* companies_map, const professionals_map* professionals_map, char* line);

#endif