#include <stdlib.h>
#include "heap.h"

static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;

	a->data = b->data;
	b->data = tmp;
}

static void sift_up(binary_tree_node_t *node, heap_t *heap)
{
	while (node->parent &&
	       heap->data_cmp(node->data, node->parent->data) < 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}
}

static binary_tree_node_t *get_parent(heap_t *heap)
{
	size_t path, mask;
	binary_tree_node_t *node = heap->root;

	path = heap->size + 1;
	mask = 1UL << (sizeof(size_t) * 8 - 2);

	while (!(mask & path))
		mask >>= 1;
	mask >>= 1;

	while (mask > 1)
	{
		node = (path & mask) ? node->right : node->left;
		mask >>= 1;
	}
	return (node);
}

binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *parent;

	if (!heap || !data)
		return (NULL);

	if (!heap->root)
	{
		heap->root = binary_tree_node(NULL, data);
		heap->size = 1;
		return (heap->root);
	}

	parent = get_parent(heap);
	node = binary_tree_node(parent, data);
	if (!node)
		return (NULL);

	if (!parent->left)
		parent->left = node;
	else
		parent->right = node;

	heap->size++;
	sift_up(node, heap);

	return (node);
}
