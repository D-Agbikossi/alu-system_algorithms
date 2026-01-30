#include "heap.h"

/**
 * sift_down - restores heap property from a given node
 * @node: pointer to the node to sift down
 * @heap: pointer to the heap
 */
static void sift_down(binary_tree_node_t *node, heap_t *heap)
{
	binary_tree_node_t *smallest;
	void *tmp;

	if (!node || !heap)
		return;

	while (node->left)
	{
		smallest = node->left;

		if (node->right &&
		    heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (heap->data_cmp(node->data, smallest->data) <= 0)
			break;

		tmp = node->data;
		node->data = smallest->data;
		smallest->data = tmp;

		node = smallest;
	}
}

/**
 * heap_extract - extracts the root value of a heap
 * @heap: pointer to the heap
 *
 * Return: pointer to extracted data, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	last = binary_tree_last_node(heap->root);
	if (!last)
		return (NULL);

	if (last == heap->root)
	{
		binary_tree_delete(heap->root);
		heap->root = NULL;
		return (data);
	}

	heap->root->data = last->data;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	binary_tree_delete(last);

	sift_down(heap->root, heap);

	return (data);
}
