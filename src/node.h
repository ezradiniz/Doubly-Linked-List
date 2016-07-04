#ifndef NODE_H
#define NODE_H

typedef struct node node_t;

struct node
{
	void *data;
	struct node *next;
	struct node *prev;
};

node_t *node_create(void *data);
node_t *node_next(node_t *this);
node_t *node_prev(node_t *this);

void node_clear(node_t *this);

int node_is_empty(node_t *this);
int node_compare(node_t *n1, node_t *n2);

#endif