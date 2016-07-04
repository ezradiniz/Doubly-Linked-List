#include <stdlib.h>
#include "node.h"

node_t *node_create(void *data)
{
	node_t *this;

	this = malloc(sizeof(node_t));
	
	if (this != NULL) {
		this->data = data;
		this->next = NULL;
		this->prev = NULL;
	}

	return this;
}

node_t *node_next(node_t *this)
{
	return (node_is_empty(this)) ? NULL : this->next;
}

node_t *node_prev(node_t *this)
{
	return (node_is_empty(this)) ? NULL : this->prev;
}

int node_is_empty(node_t *this)
{
	return (this == NULL) ? 1 : 0;
}

int node_compare(node_t *n1, node_t *n2)
{
	return (n1 == n2) ? 1 : 0;
}