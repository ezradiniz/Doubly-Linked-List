#include <stdlib.h>

#include "list.h"

//static function
static list_t *__list_add(list_t *this, node_t *no, void *data);
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
	return __list_add(this, this->head, data);
}

list_t *list_add_tail(list_t *this, void *data)
{	
	return __list_add(this, this->tail, data);
}

node_t *list_find(list_t *this, void *data, int (*node_compare_data)(void *a, void *b))
{
	node_t *node;

	LIST_FOR_EACH_NEXT(node, this) {
		if (node_compare_data(node->data, data))
			return node;
	}

	return NULL;
}

void list_clear(list_t *this)
{
	node_t *node;

	LIST_FOR_EACH_NEXT(node, this) {
		node_clear(node);
	}
}

void list_remove_node(list_t *this, node_t *no)
{
	node_t *node;

	LIST_FOR_EACH_NEXT(node, this) {
		if (node_compare(node, no)) {
			__list_remove(this, node);
			break;
		}
	}
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

	LIST_FOR_EACH_HEAD(node, this) {
		__list_remove(this, node);
	}

	free(this);
}

static list_t *__list_add(list_t *this, node_t *no, void *data)
{	
	node_t *node;

	node = node_create(data);

	if (node_is_empty(this->head)){
		//add node
		this->head = node;
		this->tail = node;
	} else if (node_compare(this->head, no)) {
		//add node in head
		node->next = this->head;
		this->head->prev = node;
		this->head = node;
	} else {
		//add node in tail
		node->prev = this->tail;
		this->tail->next = node;
		this->tail = node;
	}

	this->length++;

	return this;
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