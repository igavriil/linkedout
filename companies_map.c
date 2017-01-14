#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "companies_map.h"

#define BUFFER_SIZE_DEFAULT (1 << 20)

companies_map *companies_map_new(const char *filename)
{
    companies_map *this = malloc(sizeof(companies_map));

    char **reverse;

    FILE *file;
    file = fopen(filename, "r");
    char buffer[BUFFER_SIZE_DEFAULT];
    char *b = buffer;
    size_t bufsize = BUFFER_SIZE_DEFAULT;
    char *token;

    getline(&b,&bufsize,file);
    token = strtok(buffer, ":");

    register unsigned int token_count = 0;
    while (token != NULL)
    {
        token = strtok(NULL, ": ,\n");
        token_count++;
    }

    const unsigned int companies_count = token_count - 1;
    reverse = malloc(companies_count * sizeof(char*));
    hashmap *forward = hashmap_new(companies_count);
    this->size = companies_count;

    getline(&b,&bufsize,file);
    token = strtok(buffer, ":");

    register unsigned int company_index = 0;
    for(company_index = 0; company_index < companies_count + 1; company_index++)
    {
        if (company_index != 0)
        {
            hashmap_put(forward, token, company_index - 1);
            reverse[company_index-1] = malloc(strlen(token) + 1);
            strcpy(reverse[company_index-1], token);
        }
        token = strtok(NULL, ": ,\n");
    }

    hashmap_finalize(forward);

    fclose(file);

    this->forward = forward;
    this->reverse = reverse;

    return this;
}
