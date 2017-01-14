#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professionals_map.h"

#define BUFFER_SIZE_DEFAULT (1 << 20)

professionals_map *professionals_map_new(const char *filename)
{
    professionals_map *this = malloc(sizeof(professionals_map));

    char **reverse;

    FILE *file;
    file = fopen(filename, "r");
    char buffer[BUFFER_SIZE_DEFAULT];
    char *b = buffer;
    size_t bufsize = BUFFER_SIZE_DEFAULT;
    char *token;

    getline(&b,&bufsize,file);
    token = strtok(buffer, ",");

    register unsigned int token_count = 0;
    while (token != NULL)
    {
        token = strtok(NULL, ": ,\n");
        token_count++;
    }

    const unsigned int professionals_count = token_count - 2;
    reverse = malloc(professionals_count*sizeof(char*));
    hashmap *forward = hashmap_new(professionals_count);
    this->size = professionals_count;

    getline(&b,&bufsize,file);
    token = strtok(buffer, ",");

    register unsigned int professional_index = 0;
    for(professional_index = 0; professional_index < professionals_count + 2; professional_index++)
    {
        if (professional_index != 0 && professional_index != 1)
        {
            hashmap_put(forward, token, professional_index - 2);
            reverse[professional_index-2] = malloc(strlen(token) + 1);
            strcpy(reverse[professional_index-2], token);
        }
        token = strtok(NULL, ": ,\n");
    }

    hashmap_finalize(forward);

    fclose(file);

    this->forward = forward;
    this->reverse = reverse;

    return this;
}
