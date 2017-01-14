#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professionals_pool.h"

#define BUFFER_SIZE_DEFAULT (1 << 20)

professionals_pool *professionals_pool_new(const companies_map* companies_map, const professionals_map* professionals_map, const char *filename)
{
    professionals_pool *this = malloc(sizeof(professionals_pool));

    const unsigned int professionals_size = professionals_map->size;
    circular_array *professionals = circular_array_new(professionals_size);
    professional **professionals_array;
    professionals_array = malloc((professionals_size)*sizeof(professional*));

    FILE *file;
    file = fopen(filename, "r");
    char buffer[BUFFER_SIZE_DEFAULT];
    char *b = buffer;
    size_t bufsize = BUFFER_SIZE_DEFAULT;

    register professional *professional;
    register unsigned int i;

    for(i = professionals_size; i--; ) {
        getline(&b,&bufsize,file);
        professional = professional_new(companies_map, professionals_map, buffer);
        circular_array_put(professionals, professional);
        professionals_array[professional->identifier] = professional;
    }
    fclose(file);

    this->professionals = professionals;
    this->professionals_array = professionals_array;
    return this;
}
