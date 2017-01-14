#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "professional_factory.h"


professional *professional_new(const companies_map* companies_map, const professionals_map* professionals_map, char* line)
{
    professional *that = malloc(sizeof(professional));

    unsigned int identifier;
    queue *preferences = queue_new(companies_map->size);

    register unsigned int index = 0;

    char *token = strtok(line, ":");
    for(index = 0; index < companies_map->size + 1; index++)
    {
        if(index)
        {
            queue_enqueue(preferences, hashmap_get(companies_map->forward, token));
        }
        else
        {
            identifier = hashmap_get(professionals_map->forward, token);
        }
        token = strtok(NULL, " ,\n");
    }

    that->preferences = preferences;
    that->identifier = identifier;
    return that;
}
