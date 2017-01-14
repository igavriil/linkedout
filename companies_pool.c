#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "companies_pool.h"

#define BUFFER_SIZE_DEFAULT (1 << 20)

companies_pool *companies_pool_new(const companies_map* companies_map, const professionals_map* professionals_map, const char *filename)
{
    companies_pool *this = malloc(sizeof(companies_pool));
    const unsigned int companies_size = companies_map->size;

    company **companies = malloc(companies_size*sizeof(company*));

    FILE *file;
    file = fopen(filename, "r");
    char buffer[BUFFER_SIZE_DEFAULT];
    char *b = buffer;
    size_t bufsize = BUFFER_SIZE_DEFAULT;

    register company *company;
    register unsigned int i;

    for (i = companies_size; i--;) {
        getline(&b,&bufsize,file);
        company = company_new(companies_map, professionals_map, buffer);
        companies[company->identifier] = company;
    }
    fclose(file);

    this->companies = companies;
    return this;
}
