#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "companies_map.h"
#include "companies_pool.h"
#include "professionals_map.h"
#include "professionals_pool.h"
#include "algorithm.h"

int main(int argc, char **argv)
{
    char *companies_file = argv[1];
    char *professionals_file = argv[2];
    char *results_file = argv[3];

    companies_map *companies_map = companies_map_new(professionals_file);
    professionals_map *professionals_map = professionals_map_new(companies_file);
    companies_pool *companies_pool = companies_pool_new(companies_map, professionals_map, companies_file);
    professionals_pool *professionals_pool = professionals_pool_new(companies_map, professionals_map, professionals_file);

    algorithm *algorithm = algorithm_new(companies_map, professionals_map, companies_pool, professionals_pool);
    algorithm_run(algorithm);

    company *company;

    FILE *fptr;
    fptr = fopen(results_file, "w");
    unsigned int professional_index;
    unsigned int company_index;
    unsigned int applications_count;

    for(company_index = companies_map->size; company_index--; )
    {
        company = companies_pool->companies[company_index];
        fprintf(fptr,"%s:", companies_map->reverse[company->identifier]);
        applications_count = company->applications->count;
        for(professional_index = 0; professional_index < company->applications->count; professional_index++)
        {
            if(professional_index)
            {
                fprintf(fptr,", %s", professionals_map->reverse[company->applications->entries[professional_index]->value]);
            }
            else
            {
                fprintf(fptr," %s", professionals_map->reverse[company->applications->entries[professional_index]->value]);
            }
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);

    return 0;
}
