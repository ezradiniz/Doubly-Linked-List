#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"


static void print_list(list_t *list) 
{
	node_t *node;

	LIST_FOR_EACH_NEXT(node, list) {
		printf("%s ", (char *)node->data);
	}
	printf("\n");
}

static void print_list_rev(list_t *list)
{
	node_t *node;

	LIST_FOR_EACH_PREV(node, list) {
		printf("%s ", (char *)node->data);
	}
	printf("\n");
}

static int compare(void *a, void *b)
{
	return (strcmp((char*)a, (char*)b) == 0) ? 1 : 0;
}

int main(void)
{

	list_t *list = list_new();
	//list_t *copy_list = NULL;

	node_t * node = NULL;

	list_add_head(list, "1");
	list_add_head(list, "2");
	list_add_head(list, "3");
	list_add_head(list, "4");

	list_add_tail(list, "5");
	list_add_tail(list, "6");
	list_add_tail(list, "7");

	// copy_list = list_add_tail(list, "5");

	// list_add_tail(copy_list, "6");
	// list_add_tail(copy_list, "7");


	print_list(list);
	print_list_rev(list);

	list_remove_head(list);
	list_remove_tail(list);
	// list_remove_head(list);
	// list_remove_head(list);

	//list_destroy(list);

	
	node = list_find(list, "5", compare);

	if (node != NULL) 
		printf("FIND: %s\n", (char*)node->data); 


	list_remove_node(list, node);

	print_list(list);

	printf("COUNT: %d\n", list->length);

	list_destroy(list);

	return 0;
}