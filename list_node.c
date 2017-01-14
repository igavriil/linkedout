#include "list.h"

list_node *list_node_new(char *key, const unsigned int value)
{
    list_node *this;
    if (!(this = malloc(sizeof(list_node))))
        return NULL;
    this->previous = NULL;
    this->next = NULL;
    this->key = key;
    this->value = value;
    return this;
}