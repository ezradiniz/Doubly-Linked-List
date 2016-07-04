#include <stdlib.h>
#include <stdio.h>

#include "list.h"

//static function
static void __list_remove(list_t *this, node_t *node);

list_t *list_new() 
{
	list_t *this;

	this = malloc(sizeof(list_t));

	if (this != NULL) {
		this->length = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	return this;
}

list_t *list_add_head(list_t *this, void *data)
{
	node_t *node;;

	node = node_create(data);

	if (node_is_empty(this->head)) {
		this->tail = node;
	} else {
		node->next = this->head;
		this->head->prev = node;
	}

	this->head = node;
	this->length++;

	return this;
}

list_t *list_add_tail(list_t *this, void *data)
{
	node_t *node;

	node = node_create(data);

	if (node_is_empty(this->head)) {
		this->head = node;
	} else {
		node->prev = this->tail;
		this->tail->next = node;
	}

	this->tail = node;
	this->length++;

	return this;
}

node_t *list_find(list_t *this, void *data, int (*node_compare_data)(void *a, void *b))
{
	node_t *node;

	for (node = this->head; !node_is_empty(node); node = node_next(node)) {
		if (node_compare_data(node->data, data))
			return node;
	}

	return NULL;
}

void list_remove_head(list_t *this)
{	
	if (!node_is_empty(this->head))
		__list_remove(this, this->head);	
}

void list_remove_tail(list_t *this)
{
	if (!node_is_empty(this->tail))
		__list_remove(this, this->tail);
}

void list_destroy(list_t *this)
{	
	node_t *node;

	for (node = this->head; !node_is_empty(node); node = node_next(node))
		__list_remove(this, node);
}

void list_iterator_next(list_t *this, void (*print)(void *))
{
	node_t *node = this->head;

	while (!node_is_empty(node)) {
		print(node->data);
		node = node_next(node);
	}
}

void list_iterator_prev(list_t *this, void (*print)(void *))
{
	node_t *node = this->tail;

	while (!node_is_empty(node)) {
		print(node->data);
		node = node_prev(node);
	}
}

static void __list_remove(list_t *this, node_t *node)
{
	if (node_compare(this->head, node) && node_compare(this->tail, node)) {
		this->head = NULL;
		this->tail = NULL;
	} else if (node_compare(this->head, node)) {
		this->head = node->next;
		if (!node_compare(this->head, NULL)) this->head->prev = NULL;

	} else if (node_compare(this->tail, node)) {
		this->tail = node->prev;
		if (!node_compare(this->tail, NULL)) this->tail->next = NULL;
	
	} else {
		node_t *next = node->next;
		node_t *prev = node->prev;
		next->prev = prev;
		prev->next = next;
	}

	this->length--;

	free(node);
}