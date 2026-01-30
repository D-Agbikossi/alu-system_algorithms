#include <stdlib.h>
#include "heap.h"

static binary_tree_node_t *get_last(heap_t *heap)
{
	size_t path, mask;
	binary_tree_node_t *node = heap->root;

	path = heap->size;
	mask = 1UL << (sizeof(size_t) * 8 - 2);

	while (!(mask & path))
		mask >>= 1;
	mask >>= 1;

	while (mask)
	{
		node = (path & mask) ? node->right : node->left;
		mask >>= 1;
	}
	return (node);
}

static void sift_down(binary_tree_node_t *node, heap_t *heap)
{
	binary_tree_node_t *smallest;

	while (node->left)
	{
		smallest = node->left;
		if (node->right &&
		    heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (heap->data_cmp(node->data, smallest->data) <= 0)
			break;

		void *tmp = node->data;
		node->data = smallest->data;
		smallest->data = tmp;

		node = smallest;
	}
}

void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last;

	if (!heap || heap->size == 0)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last = get_last(heap);
	heap->root->data = last->data;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	free(last);
	heap->size--;
	sift_down(heap->root, heap);

	return (data);
}
