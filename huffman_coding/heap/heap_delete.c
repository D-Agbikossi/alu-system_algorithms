#include <stdlib.h>
#include "heap.h"

static void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	free_tree(node->left, free_data);
	free_tree(node->right, free_data);

	if (free_data)
		free_data(node->data);

	free(node);
}

void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	free_tree(heap->root, free_data);
	free(heap);
}
