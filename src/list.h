#ifndef LIST_H
#define LIST_H

#include "node.h"

typedef struct list list_t;

struct list
{
	unsigned int length;

	struct node *head;
	struct node *tail;
};

list_t *list_new();
list_t *list_add_head(list_t *this, void *data);
list_t *list_add_tail(list_t *this, void *data);

node_t *list_find(list_t *this, void *data, int (*node_compare_data)(void *a, void *b));

void list_clear(list_t *this);

void list_remove_node(list_t *this, node_t *no);
void list_remove_head(list_t *this);
void list_remove_tail(list_t *this);
void list_destroy(list_t *this);

#define LIST_FOR_EACH_NEXT(node, list) \
	for (node = list->head; !node_is_empty(node); node = node_next(node))

#define LIST_FOR_EACH_PREV(node, list) \
	for (node = list->tail; !node_is_empty(node); node = node_prev(node))

#endif