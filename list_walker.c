#include "list.h"

list_walker *list_walker_new(list_node *list_node, list_direction direction)
{
    list_walker *this;
    if (!(this = malloc(sizeof(list_walker))))
        return NULL;
    this->next = list_node;
    this->direction = direction;
    return this;
}

void list_walker_destroy(list_walker *list_walker)
{
    free(list_walker);
    list_walker = NULL;
}

list_node *list_walker_next(list_walker *list_walker)
{
    list_node *list_node = list_walker->next;
    if (list_node)
    {
        list_walker->next = list_walker->direction == HEAD
            ? list_node->previous
            : list_node->next;
    }
    return list_node;
}