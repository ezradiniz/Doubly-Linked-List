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

void list_remove_head(list_t *this);
void list_remove_tail(list_t *this);
void list_destroy(list_t *this);

void list_iterator_next(list_t *this, void (*print)(void *));
void list_iterator_prev(list_t *this, void (*print)(void *));

#endif