#include <stdio.h>
#include "list.h"

list *list_new()
{
    list *this;
    if (!(this = malloc(sizeof(list))))
        return NULL;
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
    return this;
}

list_node *list_head_push(list *list, list_node *list_node)
{
    if (!list_node) return NULL;

    if (list->length)
    {
        list_node->next = list->head;
        list_node->previous = NULL;
        list->head->previous = list_node;
        list->head = list_node;
    }
    else {
        list->head = list->tail = list_node;
        list_node->previous = list_node->next = NULL;
    }
    ++list->length;
    return list_node;
}

list_node *list_tail_push(list *list, list_node *list_node)
{
    if (!list_node) return NULL;

    if (list->length)
    {
        list_node->previous = list->tail;
        list_node->next = NULL;
        list->tail->next = list_node;
        list->tail = list_node;
    }
    else {
        list->head = list->tail = list_node;
        list_node->previous = list_node->next = NULL;
    }
    ++list->length;
    return list_node;
}

list_node *list_head_pop(list *list)
{
    if(!list->length) return NULL;

    list_node *list_node = list->head;

    if (--list->length)
    {
        (list->head = list_node->next)->previous = NULL;
    }
    else {
        list->head = list->tail = NULL;
    }

    list_node->next = list_node->previous = NULL;
    return list_node;
}

list_node *list_tail_pop(list *list)
{
    if(!list->length) return NULL;

    list_node *list_node = list->tail;

    if(--list->length)
    {
        (list->tail = list_node->previous)->next = NULL;
    }
    else
    {
        list->head = list->tail = NULL;
    }

    list_node->next = list_node->previous = NULL;
    return list_node;
}



void list_destroy(list *list)
{
    unsigned int length = list->length;
    list_node *next;
    list_node *current = list->head;

    while (length--)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
    list = NULL;
}
