#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "company_factory.h"

company *company_new(const companies_map* companies_map, const professionals_map* professionals_map, char* line)
{
    company *that = malloc(sizeof(company));

    unsigned int *positions;     // given a professional return how much is prefered
    unsigned int identifier;
    unsigned int capacity;

    positions = malloc((professionals_map->size)*sizeof(unsigned int));

    register unsigned int index = 0;

    char *token = strtok(line, ",");
    for(index = 0; index < professionals_map->size+2; index++)
    {
        if (index)
        {
            if (index == 1)
            {
                identifier = hashmap_get(companies_map->forward, token);
            }
            else
            {
                positions[hashmap_get(professionals_map->forward, token)] = index-2;
            }
        }
        else
        {
            capacity = atoi(token);
        }
        token = strtok(NULL, ": ,\n");
    }

    that->applications = priority_queue_new(capacity + 1);
    that->positions = positions;
    that->identifier = identifier;
    that->capacity = capacity;
    that->applications_count = 0;

    return that;
}
