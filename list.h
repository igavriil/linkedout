#ifndef LIST_H
#define LIST_H

#include<stdlib.h>

typedef struct list_node {
    struct list_node *previous;
    struct list_node *next;
    char *key;
    unsigned int value;
} list_node;

typedef struct {
    list_node *head;
    list_node *tail;
    unsigned int length;
} list;

typedef enum {
    HEAD,
    TAIL
} list_direction;

typedef struct {
    list_node *next;
    list_direction direction;
} list_walker;

list_node *list_node_new(char *key, const unsigned int value);

list *list_new();

void list_destroy(list *list);

list_node *list_head_push(list *list, list_node *list_node);

list_node *list_tail_push(list *list, list_node *list_node);

list_node *list_head_pop(list *list);

list_node *list_tail_pop(list *list);

list_walker *list_walker_new(list_node *list_node, list_direction direction);

void list_walker_destroy(list_walker *list_walker);

list_node *list_walker_next(list_walker *list_walker);

#endif